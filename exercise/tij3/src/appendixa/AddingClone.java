//: appendixa:AddingClone.java
// You must go through a few gyrations
// to add cloning to your own class.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import com.bruceeckel.simpletest.*;
import java.util.*;

class Int2 implements Cloneable {
  private int i;
  public Int2(int ii) { i = ii; }
  public void increment() { i++; }
  public String toString() { return Integer.toString(i); }
  public Object clone() {
    Object o = null;
    try {
      o = super.clone();
    } catch(CloneNotSupportedException e) {
      System.err.println("Int2 can't clone");
    }
    return o;
  }
}

// Inheritance doesn't remove cloneability:
class Int3 extends Int2 {
  private int j; // Automatically duplicated
  public Int3(int i) { super(i); }
}

public class AddingClone {
  private static Test monitor = new Test();
  public static void main(String[] args) {
    Int2 x = new Int2(10);
    Int2 x2 = (Int2)x.clone();
    x2.increment();
    System.out.println("x = " + x + ", x2 = " + x2);
    // Anything inherited is also cloneable:
    Int3 x3 = new Int3(7);
    x3 = (Int3)x3.clone();
    ArrayList v = new ArrayList();
    for(int i = 0; i < 10; i++ )
      v.add(new Int2(i));
    System.out.println("v: " + v);
    ArrayList v2 = (ArrayList)v.clone();
    // Now clone each element:
    for(int i = 0; i < v.size(); i++)
      v2.set(i, ((Int2)v2.get(i)).clone());
    // Increment all v2's elements:
    for(Iterator e = v2.iterator(); e.hasNext(); )
      ((Int2)e.next()).increment();
    System.out.println("v2: " + v2);
    // See if it changed v's elements:
    System.out.println("v: " + v);
    monitor.expect(new String[] {
      "x = 10, x2 = 11",
      "v: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]",
      "v2: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]",
      "v: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]"
    });
  }
} ///:~