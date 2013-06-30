#
# Define Kernel methods after and every for deferring blocks of code.
# Examples:
#
#   after 1 { puts "done" }
#   every 60 { redraw_clock }
#
# Both methods return Thread objects. Call kill on the returned objects
# to cancel the execution of the code.
#
# Note that this is a very naive implementation. A more robust
# implementation would use a single global timer thread for all tasks,
# would allow a way to retrieve the value of a deferred block, and would
# provide a way to wait for all pending tasks to complete.
#

# Execute block after sleeping the specified number of seconds.
def after(seconds, &block)  
  Thread.new do     # In a new thread...
    sleep(seconds)  # First sleep 
    block.call      # Then call the block
  end               # Return the Thread object right away
end

# Repeatedly sleep and then execute the block.
# Pass value to the block on the first invocation.  
# On subsequent invocations, pass the value of the previous invocation.
def every(seconds, value=nil, &block)
  Thread.new do                 # In a new thread...
    loop do                     # Loop forever (or until break in block)
      sleep(seconds)            # Sleep
      value = block.call(value) # And invoke block
    end                         # Then repeat..
  end                           # every returns the Thread
end
