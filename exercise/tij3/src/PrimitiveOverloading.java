//: c04:PrimitiveOverloading.java
// Promotion of primitives and overloading.
import com.bruceeckel.simpletest.*;

public class PrimitiveOverloading {
  static Test monitor = new Test();
  void f1(char x) { System.out.println("f1(char)"); }
  void f1(byte x) { System.out.println("f1(byte)"); }
  void f1(short x) { System.out.println("f1(short)"); }
  void f1(int x) { System.out.println("f1(int)"); }
  void f1(long x) { System.out.println("f1(long)"); }
  void f1(float x) { System.out.println("f1(float)"); }
  void f1(double x) { System.out.println("f1(double)"); }

  void f2(byte x) { System.out.println("f2(byte)"); }
  void f2(short x) { System.out.println("f2(short)"); }
  void f2(int x) { System.out.println("f2(int)"); }
  void f2(long x) { System.out.println("f2(long)"); }
  void f2(float x) { System.out.println("f2(float)"); }
  void f2(double x) { System.out.println("f2(double)"); }

  void f3(short x) { System.out.println("f3(short)"); }
  void f3(int x) { System.out.println("f3(int)"); }
  void f3(long x) { System.out.println("f3(long)"); }
  void f3(float x) { System.out.println("f3(float)"); }
  void f3(double x) { System.out.println("f3(double)"); }

  void f4(int x) { System.out.println("f4(int)"); }
  void f4(long x) { System.out.println("f4(long)"); }
  void f4(float x) { System.out.println("f4(float)"); }
  void f4(double x) { System.out.println("f4(double)"); }

  void f5(long x) { System.out.println("f5(long)"); }
  void f5(float x) { System.out.println("f5(float)"); }
  void f5(double x) { System.out.println("f5(double)"); }

  void f6(float x) { System.out.println("f6(float)"); }
  void f6(double x) { System.out.println("f6(double)"); }

  void f7(double x) { System.out.println("f7(double)"); }

  void testConstVal() {
    System.out.println("Testing with 5");
    f1(5);f2(5);f3(5);f4(5);f5(5);f6(5);f7(5);
  }
  void testChar() {
    char x = 'x';
    System.out.println("char argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  void testByte() {
    byte x = 0;
    System.out.println("byte argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  void testShort() {
    short x = 0;
    System.out.println("short argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  void testInt() {
    int x = 0;
    System.out.println("int argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  void testLong() {
    long x = 0;
    System.out.println("long argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  void testFloat() {
    float x = 0;
    System.out.println("float argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  void testDouble() {
    double x = 0;
    System.out.println("double argument:");
    f1(x);f2(x);f3(x);f4(x);f5(x);f6(x);f7(x);
  }
  public static void main(String[] args) {
    PrimitiveOverloading p =
      new PrimitiveOverloading();
    p.testConstVal();
    p.testChar();
    p.testByte();
    p.testShort();
    p.testInt();
    p.testLong();
    p.testFloat();
    p.testDouble();
    monitor.expect(new String[] {
      "Testing with 5",
      "f1(int)",
      "f2(int)",
      "f3(int)",
      "f4(int)",
      "f5(long)",
      "f6(float)",
      "f7(double)",
      "char argument:",
      "f1(char)",
      "f2(int)",
      "f3(int)",
      "f4(int)",
      "f5(long)",
      "f6(float)",
      "f7(double)",
      "byte argument:",
      "f1(byte)",
      "f2(byte)",
      "f3(short)",
      "f4(int)",
      "f5(long)",
      "f6(float)",
      "f7(double)",
      "short argument:",
      "f1(short)",
      "f2(short)",
      "f3(short)",
      "f4(int)",
      "f5(long)",
      "f6(float)",
      "f7(double)",
      "int argument:",
      "f1(int)",
      "f2(int)",
      "f3(int)",
      "f4(int)",
      "f5(long)",
      "f6(float)",
      "f7(double)",
      "long argument:",
      "f1(long)",
      "f2(long)",
      "f3(long)",
      "f4(long)",
      "f5(long)",
      "f6(float)",
      "f7(double)",
      "float argument:",
      "f1(float)",
      "f2(float)",
      "f3(float)",
      "f4(float)",
      "f5(float)",
      "f6(float)",
      "f7(double)",
      "double argument:",
      "f1(double)",
      "f2(double)",
      "f3(double)",
      "f4(double)",
      "f5(double)",
      "f6(double)",
      "f7(double)"
    });
  }
} ///:~
