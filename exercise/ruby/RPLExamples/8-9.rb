# We define this module to hold the global state we require, so that
# we don't alter the global namespace any more than necessary.
module ClassTrace
  # This array holds our list of files loaded and classes defined.
  # Each element is a subarray holding the class defined or the
  # file loaded and the stack frame where it was defined or loaded.
  T = []  # Array to hold the files loaded

  # Now define the constant OUT to specify where tracing output goes.
  # This defaults to STDERR, but can also come from command-line arguments
  if x = ARGV.index("--traceout")    # If argument exists
    OUT = File.open(ARGV[x+1], "w")  # Open the specified file
    ARGV[x,2] = nil                  # And remove the arguments
  else
    OUT = STDERR                     # Otherwise default to STDERR
  end
end

# Alias chaining step 1: define aliases for the original methods
alias original_require require
alias original_load load

# Alias chaining step 2: define new versions of the methods 
def require(file)
  ClassTrace::T << [file,caller[0]]     # Remember what was loaded where
  original_require(file)                # Invoke the original method
end
def load(*args)
  ClassTrace::T << [args[0],caller[0]]  # Remember what was loaded where
  original_load(*args)                  # Invoke the original method
end

# This hook method is invoked each time a new class is defined
def Object.inherited(c)
  ClassTrace::T << [c,caller[0]]        # Remember what was defined where
end

# Kernel.at_exit registers a block to be run when the program exits
# We use it to report the file and class data we collected
at_exit {
  o = ClassTrace::OUT
  o.puts "="*60
  o.puts "Files Loaded and Classes Defined:"
  o.puts "="*60
  ClassTrace::T.each do |what,where|
    if what.is_a? Class  # Report class (with hierarchy) defined
      o.puts "Defined: #{what.ancestors.join('<-')} at #{where}"
    else                 # Report file loaded
      o.puts "Loaded: #{what} at #{where}"
    end
  end
}
