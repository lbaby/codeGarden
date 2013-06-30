ruby [<replaceable>options</replaceable>] [--] <replaceable>program</replaceable> [<replaceable>arguments</replaceable>]
---------------------------
require '<replaceable>library</replaceable>'
---------------------------
while gets             # Read a line of input into $_
  $F = split if $-a    # Split $_ into fields if -a was specified
  chop! if $-l         # Chop line ending off $_ if -l was specified
  # Program text here
end
---------------------------
while gets             # Read a line of input into $_
  $F = split if $-a    # Split $_ into fields if -a was specified
  chop! if $-l         # Chop line ending off $_ if -l was specified
  # Program text here
  print                # Output $_ (adding $/ if -l was specified)
end
---------------------------
Comparable      FileTest        Marshal         Precision
Enumerable      GC              Math            Process
Errno           Kernel          ObjectSpace     Signal
---------------------------
Array           File            Method          String
Bignum          Fixnum          Module          Struct
Binding         Float           NilClass        Symbol
Class           Hash            Numeric         Thread
Continuation    IO              Object          ThreadGroup
Data            Integer         Proc            Time
Dir             MatchData       Range           TrueClass
FalseClass      MatchingData    Regexp          UnboundMethod
---------------------------
ArgumentError           NameError               SignalException
EOFError                NoMemoryError           StandardError
Exception               NoMethodError           SyntaxError
FloatDomainError        NotImplementedError     SystemCallError
IOError                 RangeError              SystemExit
IndexError              RegexpError             SystemStackError
Interrupt               RuntimeError            ThreadError
LoadError               ScriptError             TypeError
LocalJumpError          SecurityError           ZeroDivisionError
---------------------------
BasicObject     FiberError      Mutex           VM
Fiber           KeyError        StopIteration
---------------------------
# Print all modules (excluding classes)
puts Module.constants.sort.select {|x| eval(x.to_s).instance_of? Module}

# Print all classes (excluding exceptions)
puts Module.constants.sort.select {|x|
  c = eval(x.to_s)
  c.is_a? Class and not c.ancestors.include? Exception
}

# Print all exceptions
puts Module.constants.sort.select {|x|
  c = eval(x.to_s)
  c.instance_of? Class and c.ancestors.include? Exception
}
---------------------------
ruby -e 'puts Module.constants.sort.reject{|x| eval(x.to_s).is_a? Module}'
---------------------------
ruby -e 'puts global_variables.sort'
---------------------------
ruby -rEnglish -e 'puts global_variables.sort'
---------------------------
block_given?    iterator?       loop            require
callcc          lambda          proc            throw
catch           load            raise
---------------------------
format          print           puts            sprintf
gets            printf          readline
p               putc            readlines
---------------------------
chomp   chop    gsub    scan    sub
chomp!  chop!   gsub!   split   sub!
---------------------------
`       fork    select  system  trap
exec    open    syscall test
---------------------------
abort   at_exit exit    exit!   fail    warn
---------------------------
binding                         set_trace_func
caller                          singleton_method_added
eval                            singleton_method_removed
global_variables                singleton_method_undefined
local_variables                 trace_var
method_missing                  untrace_var
remove_instance_variable
---------------------------
Array   Float   Integer String
---------------------------
autoload                rand                    srand
autoload?               sleep
---------------------------
ruby -n -e 'print if /^A/' datafile
---------------------------
print if $_ =~ /^A/
---------------------------
os = `uname`             # String literal and method invocation in one
os = %x{uname}           # Another quoting syntax
os = Kernel.`("uname")   # Invoke the method explicitly
---------------------------
files = `echo *.xml`
---------------------------
pipe = open("|echo *.xml")
files = pipe.readline
pipe.close
---------------------------
fork {
  puts "Hello from the child process: #$$"
}
puts "Hello from the parent process: #$$"
---------------------------
pid = fork
if (pid)
  puts "Hello from parent process: #$$"
  puts "Created child process #{pid}"   
else
  puts Hello from child process: #$$"
end
---------------------------
open("|-", "r+") do |child|
  if child
    # This is the parent process
    child.puts("Hello child")       # Send to child
    response = child.gets           # Read from child
    puts "Child said: #{response}"
  else
    # This is the child process
    from_parent = gets              # Read from parent
    STDERR.puts "Parent said: #{from_parent}"
    puts("Hi Mom!")                 # Send to parent
  end
end
---------------------------
open("|-", "r") do |child|
  if child
    # This is the parent process
    files = child.readlines   # Read the output of our child
    child.close
  else
    # This is the child process
    exec("/bin/ls", "-l")     # Run another executable
  end
end
---------------------------
trap "SIGINT" {
  puts "Ignoring SIGINT"
}
---------------------------
fail "Unknown option #{switch}"
---------------------------
$SAFE=1                # upgrade the safe level
$SAFE=4                # upgrade the safe level even higher
$SAFE=0                # SecurityError!  you can't do it
---------------------------
Thread.start {     # Create a "sandbox" thread
  $SAFE = 4        # Restrict execution in this thread only
  ...              # Untrusted code can be run here
}
---------------------------
Dir.chdir               File.truncate           Process.egid=
Dir.chroot              File.umask              Process.fork
Dir.mkdir               IO.fctrl                Process.kill
Dir.rmdir               IO.ioctl                Process.setpgid
File.chmod              Kernel.exit!            Process.setpriority
File.chown              Kernel.fork             Process.setsid
File.flock              Kernel.syscall
File.lstat              Kernel.trap
---------------------------
def safe_eval(str)
  Thread.start {            # Start sandbox thread
    $SAFE = 4               # Upgrade safe level
    eval(str)               # Eval in the sandbox
  }.value                   # Retrieve result
end
---------------------------
