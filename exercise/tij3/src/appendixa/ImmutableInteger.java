//: appendixa:ImmutableInteger.java
// The Integer class cannot be changed.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
import java.util.*;

public class ImmutableInteger {
  public static void main(String[] args) {
    List v = new ArrayList();
    for(int i = 0; i < 10; i++)
      v.add(new Integer(i));
    // But how do you change the int inside the Integer?
  }
} ///:~
