//: appendixa:Alias2.java
// Method calls implicitly alias their arguments.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import com.bruceeckel.simpletest.*;

public class Alias2 {
  private static Test monitor = new Test();
  private int i;
  public Alias2(int ii) { i = ii; }
  public static void f(Alias2 reference) { reference.i++; }
  public static void main(String[] args) {
    Alias2 x = new Alias2(7);
    System.out.println("x: " + x.i);
    System.out.println("Calling f(x)");
    f(x);
    System.out.println("x: " + x.i);
    monitor.expect(new String[] {
      "x: 7",
      "Calling f(x)",
      "x: 8"
    });
  }
} ///:~
