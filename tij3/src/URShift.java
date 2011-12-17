import com.bruceeckel.simpletest.*;

public class URShift {
  static Test monitor = new Test();
  public static void main(String[] args) {
    int i = -1;
    System.out.println(i >>>= 10);
    long l = -1;
    System.out.println(l >>>= 10);
    short s = -1;
    System.out.println(s >>>= 10);
    byte b = -1;
    System.out.println(b >>>= 10);
    b = -1;
    System.out.println(b>>>10);
    monitor.expect(new String[] {
      "4194303",
      "18014398509481983",
      "-1",
      "-1",
      "4194303"
    });
  }
} ///:~
