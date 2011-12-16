//: appendixa:Cloning.java
// The clone() operation works for only a few
// items in the standard Java library.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import com.bruceeckel.simpletest.*;
import java.util.*;

class Int {
  private int i;
  public Int(int ii) { i = ii; }
  public void increment() { i++; }
  public String toString() { return Integer.toString(i); }
}

public class Cloning {
  private static Test monitor = new Test();
  public static void main(String[] args) {
    ArrayList v = new ArrayList();
    for(int i = 0; i < 10; i++ )
      v.add(new Int(i));
    System.out.println("v: " + v);
    ArrayList v2 = (ArrayList)v.clone();
    // Increment all v2's elements:
    for(Iterator e = v2.iterator();
        e.hasNext(); )
      ((Int)e.next()).increment();
    // See if it changed v's elements:
    System.out.println("v: " + v);
    monitor.expect(new String[] {
      "v: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]",
      "v: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]"
    });
  }
} ///:~
