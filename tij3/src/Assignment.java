//: c03:Assignment.java
// Assignment with objects is a bit tricky.
import com.bruceeckel.simpletest.*;

class Number {
  int i;
}

public class Assignment {
  static Test monitor = new Test();
  public static void main(String[] args) {
    Number n1 = new Number();
    Number n2 = new Number();
    n1.i = 9;
    n2.i = 47;
    System.out.println("1: n1.i: " + n1.i +
      ", n2.i: " + n2.i);
    n1 = n2;
    System.out.println("2: n1.i: " + n1.i +
      ", n2.i: " + n2.i);
    n1.i = 27;
    System.out.println("3: n1.i: " + n1.i +
      ", n2.i: " + n2.i);
    monitor.expect(new String[] {
      "1: n1.i: 9, n2.i: 47",
      "2: n1.i: 47, n2.i: 47",
      "3: n1.i: 27, n2.i: 27"
    });
  }
} ///:~
