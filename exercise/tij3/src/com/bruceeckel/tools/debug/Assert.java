//: com:bruceeckel:tools:debug:Assert.java
// Assertion tool for debugging.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.tools.debug;

public class Assert {
  private static void perr(String msg) {
    System.err.println(msg);
  }
  public static final void is_true(boolean exp) {
    if(!exp) perr("Assertion failed");
  }
  public static final void is_false(boolean exp) {
    if(exp) perr("Assertion failed");
  }
  public static final void
  is_true(boolean exp, String msg) {
    if(!exp) perr("Assertion failed: " + msg);
  }
  public static final void
  is_false(boolean exp, String msg) {
    if(exp) perr("Assertion failed: " + msg);
  }
} ///:~
