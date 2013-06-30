//: appendixa:PassReferences.java
// Passing references around.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import com.bruceeckel.simpletest.*;

public class PassReferences {
  private static Test monitor = new Test();
  public static void f(PassReferences h) {
    System.out.println("h inside f(): " + h);
  }
  public static void main(String[] args) {
    PassReferences p = new PassReferences();
    System.out.println("p inside main(): " + p);
    f(p);
    monitor.expect(new String[] {
      "%% p inside main\\(\\): PassReferences@[a-z0-9]+",
      "%% h inside f\\(\\): PassReferences@[a-z0-9]+"
    });
  }
} ///:~
