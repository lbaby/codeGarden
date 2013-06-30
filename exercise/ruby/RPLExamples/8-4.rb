# Call the trace method of any object to obtain a new object that
# behaves just like the original, but which traces all method calls
# on that object. If tracing more than one object, specify a name to
# appear in the output. By default, messages will be sent to STDERR, 
# but you can specify any stream (or any object that accepts strings
# as arguments to <<).
class Object
  def trace(name="", stream=STDERR)
    # Return a TracedObject that traces and delegates everything else to us.
    TracedObject.new(self, name, stream)
  end
end

# This class uses method_missing to trace method invocations and
# then delegate them to some other object. It deletes most of its own
# instance methods so that they don't get in the way of method_missing.
# Note that only methods invoked through the TracedObject will be traced.
# If the delegate object calls methods on itself, those invocations
# will not be traced.
class TracedObject
  # Undefine all of our noncritical public instance methods.
  # Note the use of Module.instance_methods and Module.undef_method.
  instance_methods.each do |m|
    m = m.to_sym  # Ruby 1.8 returns strings, instead of symbols
    next if m == :object_id || m == :__id__ || m == :__send__
    undef_method m
  end

  # Initialize this TracedObject instance.
  def initialize(o, name, stream)
    @o = o            # The object we delegate to
    @n = name         # The object name to appear in tracing messages
    @trace = stream   # Where those tracing messages are sent
  end

  # This is the key method of TracedObject. It is invoked for just
  # about any method invocation on a TracedObject.
  def method_missing(*args, &block)
    m = args.shift         # First arg is the name of the method
    begin
      # Trace the invocation of the method.
      arglist = args.map {|a| a.inspect}.join(', ')
      @trace << "Invoking: #{@n}.#{m}(#{arglist}) at #{caller[0]}\n"
      # Invoke the method on our delegate object and get the return value.
      r = @o.send m, *args, &block
      # Trace a normal return of the method.
      @trace << "Returning: #{r.inspect} from #{@n}.#{m} to #{caller[0]}\n"
      # Return whatever value the delegate object returned.
      r
    rescue Exception => e
      # Trace an abnormal return from the method.
      @trace << "Raising: #{e.class}:#{e} from #{@n}.#{m}\n"
      # And re-raise whatever exception the delegate object raised.
      raise
    end
  end

  # Return the object we delegate to.
  def __delegate
    @o
  end
end
