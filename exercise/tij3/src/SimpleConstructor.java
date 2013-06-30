//: c04:SimpleConstructor.java
// Demonstration of a simple constructor.
import com.bruceeckel.simpletest.*;

class Rock {
  Rock() { // This is the constructor
    System.out.println("Creating Rock");
  }
}

public class SimpleConstructor {
  static Test monitor = new Test();
  public static void main(String[] args) {
    for(int i = 0; i < 10; i++)
      new Rock();
    monitor.expect(new String[] {
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock",
      "Creating Rock"
    });
  }
} ///:~