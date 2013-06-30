//: c04:TerminationCondition.java
// Using finalize() to detect an object that
// hasn't been properly cleaned up.
import com.bruceeckel.simpletest.*;

class Book {
  boolean checkedOut = false;
  Book(boolean checkOut) {
    checkedOut = checkOut;
  }
  void checkIn() {
    checkedOut = false;
  }
  public void finalize() {
    if(checkedOut)
      System.out.println("Error: checked out");
  }
}

public class TerminationCondition {
  static Test monitor = new Test();
  public static void main(String[] args) {
    Book novel = new Book(true);
//    Book ab[] = 
//    for(int i =0; i < 10000000; i++){
//    	ab[i]=new Book(true);
//    }
//    // Proper cleanup:
    novel.checkIn();
    // Drop the reference, forget to clean up:
    new Book(true);
    // Force garbage collection & finalization:
    System.gc();
    monitor.expect(new String[] {
      "Error: checked out"}, Test.WAIT);
  }
} ///:~
