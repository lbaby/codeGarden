# Define trace! and untrace! instance methods for all objects.
# trace! "chains" the named methods by defining singleton methods
# that add tracing functionality and then use super to call the original.
# untrace! deletes the singleton methods to remove tracing.
class Object
  # Trace the specified methods, sending output to STDERR.
  def trace!(*methods)
    @_traced = @_traced || []    # Remember the set of traced methods

    # If no methods were specified, use all public methods defined 
    # directly (not inherited) by the class of this object 
    methods = public_methods(false) if methods.size == 0

    methods.map! {|m| m.to_sym } # Convert any strings to symbols
    methods -= @_traced          # Remove methods that are already traced
    return if methods.empty?     # Return early if there is nothing to do
    @_traced |= methods          # Add methods to set of traced methods

    # Trace the fact that we're starting to trace these methods
    STDERR << "Tracing #{methods.join(', ')} on #{object_id}\n"

    # Singleton methods are defined in the eigenclass
    eigenclass = class << self; self; end

    methods.each do |m|         # For each method m
      # Define a traced singleton version of the method m.
      # Output tracing information and use super to invoke the
      # instance method that it is tracing.
      # We want the defined  methods to be able to accept blocks, so we
      # can't use define_method, and must instead evaluate a string.
      # Note that everything between %Q{ and the matching } is a 
      # double-quoted string, not a block. Also note that there are 
      # two levels of string interpolations here. #{} is interpolated
      # when the singleton method is defined. And \#{} is interpolated 
      # when the singleton method is invoked.
      eigenclass.class_eval %Q{
        def #{m}(*args, &block)
          begin
            STDERR << "Entering: #{m}(\#{args.join(', ')})\n"
            result = super
            STDERR << "Exiting: #{m} with \#{result}\n"
            result
          rescue
            STDERR << "Aborting: #{m}: \#{$!.class}: \#{$!.message}"
            raise
          end
        end
      }
    end
  end

  # Untrace the specified methods or all traced methods
  def untrace!(*methods)
    if methods.size == 0    # If no methods specified untrace
      methods = @_traced    # all currently traced methods
      STDERR << "Untracing all methods on #{object_id}\n"
    else                    # Otherwise, untrace
      methods.map! {|m| m.to_sym }  # Convert string to symbols
      methods &= @_traced   # all specified methods that are traced
      STDERR << "Untracing #{methods.join(', ')} on #{object_id}\n"
    end

    @_traced -= methods     # Remove them from our set of traced methods

    # Remove the traced singleton methods from the eigenclass
    # Note that we class_eval a block here, not a string
    (class << self; self; end).class_eval do
      methods.each do |m|
        remove_method m     # undef_method would not work correctly
      end
    end

    # If no methods are traced anymore, remove our instance var 
    if @_traced.empty?
      remove_instance_variable :@_traced
    end
  end
end
