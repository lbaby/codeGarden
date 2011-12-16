//: appendixa:Alias1.java
// Aliasing two references to one object.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import com.bruceeckel.simpletest.*;

public class Alias1 {
  private static Test monitor = new Test();
  private int i;
  public Alias1(int ii) { i = ii; }
  public static void main(String[] args) {
    Alias1 x = new Alias1(7);
    Alias1 y = x; // Assign the reference
    System.out.println("x: " + x.i);
    System.out.println("y: " + y.i);
    System.out.println("Incrementing x");
    x.i++;
    System.out.println("x: " + x.i);
    System.out.println("y: " + y.i);
    monitor.expect(new String[] {
      "x: 7",
      "y: 7",
      "Incrementing x",
      "x: 8",
      "y: 8"
    });
  }
} ///:~
