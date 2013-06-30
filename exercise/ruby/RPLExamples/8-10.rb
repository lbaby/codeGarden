# Define a Module.synchronize_method that alias chains instance methods
# so they synchronize on the instance before running.
class Module
  # This is a helper function for alias chaining.
  # Given a method name (as a string or symbol) and a prefix, create
  # a unique alias for the method, and return the name of the alias
  # as a symbol. Any punctuation characters in the original method name
  # will be converted to numbers so that operators can be aliased.
  def create_alias(original, prefix="alias")
    # Stick the prefix on the original name and convert punctuation
    aka = "#{prefix}_#{original}"
    aka.gsub!(/([\=\|\&\+\-\*\/\^\!\?\~\%\<\>\[\]])/) {
      num = $1[0]                       # Ruby 1.8 character -> ordinal
      num = num.ord if num.is_a? String # Ruby 1.9 character -> ordinal
      '_' + num.to_s
    }
    
    # Keep appending underscores until we get a name that is not in use
    aka += "_" while method_defined? aka or private_method_defined? aka

    aka = aka.to_sym            # Convert the alias name to a symbol
    alias_method aka, original  # Actually create the alias
    aka                         # Return the alias name
  end

  # Alias chain the named method to add synchronization
  def synchronize_method(m)
    # First, make an alias for the unsynchronized version of the method.
    aka = create_alias(m, "unsync") 
    # Now redefine the original to invoke the alias in a synchronized block.
    # We want the defined  method to be able to accept blocks, so we
    # can't use define_method, and must instead evaluate a string with 
    # class_eval. Note that everything between %Q{ and the matching } 
    # is a double-quoted string, not a block. 
    class_eval %Q{
      def #{m}(*args, &block)
        synchronized(self) { #{aka}(*args, &block) }
      end
    }
  end
end

# This global synchronized method can now be used in three different ways.
def synchronized(*args)
  # Case 1: with one argument and a block, synchronize on the object
  # and execute the block
  if args.size == 1 && block_given?
    args[0].mutex.synchronize { yield }

  # Case two: with one argument that is not a symbol and no block
  # return a SynchronizedObject wrapper
  elsif args.size == 1 and not args[0].is_a? Symbol and not block_given?
    SynchronizedObject.new(args[0])

  # Case three: when invoked on a module with no block, alias chain the
  # named methods to add synchronization. Or, if there are no arguments, 
  # then alias chain the next method defined.
  elsif self.is_a? Module and not block_given?
    if (args.size > 0) # Synchronize the named methods
      args.each {|m| self.synchronize_method(m) }
    else
      # If no methods are specified synchronize the next method defined
      eigenclass = class<<self; self; end 
      eigenclass.class_eval do # Use eigenclass to define class methods
        # Define method_added for notification when next method is defined
        define_method :method_added do |name|
          # First remove this hook method
          eigenclass.class_eval { remove_method :method_added }
          # Next, synchronize the method that was just added
          self.synchronize_method name
        end
      end
    end

  # Case 4: any other invocation is an error
  else
    raise ArgumentError, "Invalid arguments to synchronize()"
  end
end
