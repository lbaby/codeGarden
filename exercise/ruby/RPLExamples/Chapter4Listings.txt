2                  # A numeric literal
x                  # A local variable reference
Math.sqrt(2)       # A method invocation
x = Math.sqrt(2)   # Assignment
x*x                # Multiplication with the * operator
---------------------------
one = 1.0     # This is an assignment expression
one           # This variable reference expression evaluates to 1.0
---------------------------
a = 0.0 if false    # This assignment is never executed
print a             # Prints nil: the variable exists but is not assigned
print b             # NameError: no variable or method named b exists
---------------------------
CM_PER_INCH = 2.54  # Define a constant.
CM_PER_INCH         # Refer to the constant. Evaluates to 2.54.
---------------------------
Conversions::CM_PER_INCH # Constant defined in the Conversions module
modules[0]::NAME         # Constant defined by an element of an array
---------------------------
Conversions::Area::HECTARES_PER_ACRE
---------------------------
::ARGV      # The global constant ARGV
---------------------------
puts "hello world"  # "puts" invoked on self, with one string arg
Math.sqrt(2)        # "sqrt" invoked on object Math with one arg
message.length      # "length" invoked on object message; no args
a.each {|x| p x }   # "each" invoked on object a, with an associated block
---------------------------
puts "hello world"
---------------------------
message.length=(3)    # Traditional method invocation
message.length = 3    # Method invocation masquerading as assignment
---------------------------
a[0]
---------------------------
a.[](0)
---------------------------
x
---------------------------
x = 1     # Set the lvalue x to the value 1
---------------------------
x += 1    # Set the lvalue x to the value x + 1
---------------------------
x,y,z = 1,2,3   # Set x to 1, y to 2 and z to 3
---------------------------
x = y = 0   # Set x and y to 0
---------------------------
x + y
Math.sqrt(2)
---------------------------
x = 1       # Affects the value of other expressions that use x
x += 1      # Returns a different value each time it is evaluated
---------------------------
point.x, point.y = 1, 2
---------------------------
class Ambiguous
  def x; 1; end # A method named "x". Always returns 1

  def test
    puts x      # No variable has been seen; refers to method above: prints 1

    # The line below is never evaluated, because of the "if false" clause. But
    # the parser sees it and treats x as a variable for the rest of the method.
    x = 0 if false

    puts x    # x is a variable, but has never been assigned to: prints nil

    x = 2     # This assignment does get evaluated
    puts x    # So now this line prints 2
  end
end
---------------------------
N = 100 if false
---------------------------
o.m = v
---------------------------
o.m=(v)  # If we omit the parens and add a space, this looks like assignment!
---------------------------
o.[]=(x,y)
---------------------------
o[x,y] = z
o.[]=(x,y,z)
---------------------------
x += 1
---------------------------
x = x + 1
---------------------------
o.m += 1
o.m=(o.m()+1)
---------------------------
o[x] -= 2
o.[]=(x, o.[](x) - 2)
---------------------------
results ||= []
---------------------------
results = results || []
---------------------------
x, y, z = 1, 2, 3   # x=1; y=2; z=3
---------------------------
x,y = y,x     # Parallel: swap the value of two variables
x = y; y = x  # Sequential: both variables have same value
---------------------------
x = 1, 2, 3      # x = [1,2,3]
---------------------------
x, = 1, 2, 3     # x = 1; other values are discarded
---------------------------
x, y, z = [1, 2, 3]  # Same as x,y,z = 1,2,3
---------------------------
x = [1,2]    # x becomes [1,2]: this is not parallel assignment
x, = [1,2]   # x becomes 1: the trailing comma makes it parallel
---------------------------
x, y, z = 1, 2  # x=1; y=2; z=nil
---------------------------
x, y = 1, 2, 3 # x=1; y=2; 3 is not assigned anywhere
---------------------------
x, y, z = 1, *[2,3]  # Same as x,y,z = 1,2,3
---------------------------
x,y = **[[1,2]]   # SyntaxError!
---------------------------
x,*y = 1, 2, 3  # x=1; y=[2,3]
x,*y = 1, 2     # x=1; y=[2]
x,*y = 1        # x=1; y=[]
---------------------------
# Ruby 1.9 only
*x,y = 1, 2, 3  # x=[1,2]; y=3
*x,y = 1, 2     # x=[1]; y=2
*x,y = 1        # x=[]; y=1
---------------------------
x, y, *z = 1, *[2,3,4]  # x=1; y=2; z=[3,4].
---------------------------
x,(y,z) = a, b
---------------------------
x = a
y,z = b
---------------------------
x,y,z = 1,[2,3]             # No parens: x=1;y=[2,3];z=nil
x,(y,z) = 1,[2,3]           # Parens: x=1;y=2;z=3

a,b,c,d = [1,[2,[3,4]]]     # No parens: a=1;b=[2,[3,4]];c=d=nil
a,(b,(c,d)) = [1,[2,[3,4]]] # Parens: a=1;b=2;c=3;d=4
---------------------------
puts x,y=1,2
---------------------------
puts (x,y=1,2)
---------------------------
puts((x,y=1,2))
---------------------------
2 * Math.sqrt(2) < limit
---------------------------
1 + 2 * 3     # => 7
---------------------------
(1 + 2) * 3   # => 9
---------------------------
ri 'String.*'
---------------------------
=
**= *= /= %= += -=
<<= >>=
&&= &= ||= |= ^=
---------------------------
(0b1011 << 1).to_s(2)   # => "10110"   11 << 1 => 22
(0b10110 >> 2).to_s(2)  # => "101"     22 >> 2 => 5
---------------------------
message = "hello"        # A string
messages = []            # An empty array
message << " world"      # Append to the string
messages << message      # Append message to the array
STDOUT << message        # Print the message to standard output stream
---------------------------
(0b1010 & 0b1100).to_s(2)  # => "1000"
---------------------------
(0b1010 | 0b1100).to_s(2)  # => "1110"
---------------------------
(0b1010 ^ 0b1100).to_s(2)  # => "110"
---------------------------
# Declare class A as a subclass of B
class A < B
end
---------------------------
String < Object        # true: String is more specialized than Object
Object > Numeric       # true: Object is more general than Numeric
Numeric < Integer      # false: Numeric is not more specialized than Integer
String < Numeric       # nil: String and Numeric are not related
---------------------------
x == 0 && y > 1
---------------------------
x && y
---------------------------
x && print(x.to_s)
---------------------------
print(x.to_s) if x </programlisting>
        </footnote></para>

      <para>The <literal>||</literal> operator returns the Boolean OR of its
      operands. It returns a true value if either of its operands is a true
      value. If both operands are false values, then it returns a false value.
      Like <literal>&&</literal>, the <literal>||</literal> operator
      ignores its righthand operand if its value has no impact on the value of
      the operation. The <literal>||</literal> operator works like this:
      first, it evaluates its lefthand operand. If this is any value other
      than <literal>nil</literal> or <literal>false</literal>, it simply
      returns that value. Otherwise, it evaluates its righthand operand and
      returns that value.</para>

      <para><literal>||</literal> can be used as a conjunction to join
      multiple comparison or equality expressions:</para>

      <programlisting>x < 0 || y < 0 || z < 0   # Are any of the coordinates negative?
---------------------------
# If the argument x is nil, then get its value from a hash of user preferences
# or from a constant default value.
x = x || preferences[:x] || Defaults::X
---------------------------
1 || 2 && nil     # => 1
---------------------------
(1 || 2) && nil   # => nil
---------------------------
!(a && b)
---------------------------
!a || !b
---------------------------
if x > 0 and y > 0 and not defined? d then d = Math.sqrt(x*x + y*y) end
---------------------------
if a = f(x) and b = f(y) and c = f(z) then d = g(a,b,c) end
---------------------------
x || y && nil        # && is performed first   => x
x or y and nil       # evaluated left-to-right => nil 
---------------------------
x+1..x*x
---------------------------
Range.new(x,y)
---------------------------
Range.new(x,y,true)
---------------------------
(1..10).each {|x| print x if x==3..x==5 }
---------------------------
# Prints "3". Flips and flops back when x==3
(1..10).each {|x| print x if x==3..x>=3 }  
# Prints "34". Flips when x == 3 and flops when x==4
(1..10).each {|x| print x if x==3...x>=3 } # Prints "34"
---------------------------
ARGF.each do |line|   # For each line of standard in or of named files
  print line if line=~/TODO/..line=~/^$/ # Print lines when flip-flop is true
end
---------------------------
$state = false            # Global storage for flip-flop state
def flipflop(x)           # Test value of x against flip-flop
  if !$state              # If saved state is false
    result = (x == 3)     # Result is value of lefthand operand
    if result             # If that result is true
      $state = !(x == 5)  # Then saved state is not of the righthand operand
    end
    result                # Return result
  else                    # Otherwise, if saved state is true
    $state = !(x == 5)    # Then save the inverse of the righthand operand
    true                  # And return true without testing lefthand
  end
end
---------------------------
(1..10).each {|x| print x if flipflop(x) }
---------------------------
$state2 = false
def flipflop2(x)
  if !$state2
    $state2 = (x == 3)
  else
    $state2 = !(x >= 3)
    true
  end
end

# Now try it out
(1..10).each {|x| print x if x==3...x>=3 }  # Prints "34" 
(1..10).each {|x| print x if flipflop2(x) } # Prints "34" 
---------------------------
"You have #{n} #{n==1 ? 'message' : 'messages'}"
---------------------------
x==3?y:z      # This is legal
3==x?y:z      # Syntax error: x? is interpreted as a method name
(3==x)?y:z    # Okay: parentheses fix the problem
3==x ?y:z     # Spaces also resolve the problem
---------------------------
a ? b : c ? d : e    # This expression...
a ? b : (c ? d : e)  # is evaluated like this..
(a ? b : c) ? d : e  # NOT like this
---------------------------
max = x>y ? x>z ? x : z : y>z ? y : z
max = x>y ? (x>z ? x : z) : (y>z ? y : z)  # With explicit parentheses
---------------------------
x = y = z = 0      # Assign zero to variables x, y, and z
x = (y = (z = 0))  # This equivalent expression shows order of evaluation
---------------------------
# Compute f(x), but only if f and x are both defined
y = f(x) if defined? f(x)
---------------------------
defined? a and defined? b    # This works
defined? a && defined? b     # Evaluated as: defined?((a && defined? b))
---------------------------
print x if x
---------------------------
