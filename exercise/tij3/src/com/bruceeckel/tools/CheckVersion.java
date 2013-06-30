//: com:bruceeckel:tools:CheckVersion.java
// {RunByHand}
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.tools;

public class CheckVersion {
  public static void main(String[] args) {
    String version = System.getProperty("java.version");
    char minor = version.charAt(2);
    char point = version.charAt(4);
    if(minor < '4' || point < '1')
      throw new RuntimeException("JDK 1.4.1 or higher " +
        "is required to run the examples in this book.");
    System.out.println("JDK version "+ version + " found");
  }
} ///:~
