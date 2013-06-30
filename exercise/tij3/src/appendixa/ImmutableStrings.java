//: appendixa:ImmutableStrings.java
// Demonstrating StringBuffer.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import com.bruceeckel.simpletest.*;

public class ImmutableStrings {
  private static Test monitor = new Test();
  public static void main(String[] args) {
    String foo = "foo";
    String s = "abc" + foo + "def" + Integer.toString(47);
    System.out.println(s);
    // The "equivalent" using StringBuffer:
    StringBuffer sb =
      new StringBuffer("abc"); // Creates String!
    sb.append(foo);
    sb.append("def"); // Creates String!
    sb.append(Integer.toString(47));
    System.out.println(sb);
    monitor.expect(new String[] {
      "abcfoodef47",
      "abcfoodef47"
    });
  }
} ///:~
