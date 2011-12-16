//: com:bruceeckel:simpletest:NumOfLinesException.java
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.simpletest;

public class NumOfLinesException
extends SimpleTestException {
  public NumOfLinesException(int exp, int out) {
    super("Number of lines of output and "
      + "expected output did not match.\n" +
      "expected: <" + exp + ">\n" +
      "output:   <" + out + "> lines)");
  }
} ///:~
