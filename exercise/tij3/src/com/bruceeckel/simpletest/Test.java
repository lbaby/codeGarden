//: com:bruceeckel:simpletest:Test.java
// Simple utility for testing program output. Intercepts
// System.out to print both to the console and a buffer.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.simpletest;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Test {
  // Bit-shifted so they can be added together:
  public static final int
    EXACT = 1 << 0, // Lines must match exactly
    AT_LEAST = 1 << 1, // Must be at least these lines
    IGNORE_ORDER = 1 << 2, // Ignore line order
    WAIT = 1 << 3; // Delay until all lines are output
  private String className;
  private TestStream testStream;
  public Test() {
    // Discover the name of the class this
    // object was created within:
    className =
      new Throwable().getStackTrace()[1].getClassName();
    testStream = new TestStream(className);
  }
  public static List fileToList(String fname) {
    ArrayList list = new ArrayList();
    try {
      BufferedReader in =
        new BufferedReader(new FileReader(fname));
      try {
        String line;
        while((line = in.readLine()) != null) {
          if(fname.endsWith(".txt"))
            list.add(line);
          else
            list.add(new TestExpression(line));
        }
      } finally {
        in.close();
      }
    } catch (IOException e) {
      throw new RuntimeException(e);
    }
    return list;
  }
  public static List arrayToList(Object[] array) {
    List l = new ArrayList();
    for(int i = 0; i < array.length; i++) {
      if(array[i] instanceof TestExpression) {
        TestExpression re = (TestExpression)array[i];
        for(int j = 0; j < re.getNumber(); j++)
          l.add(re);
      } else {
        l.add(new TestExpression(array[i].toString()));
      }
    }
    return l;
  }
  public void expect(Object[] exp, int flags) {
    if((flags & WAIT) != 0)
      while(testStream.numOfLines < exp.length) {
        try {
          Thread.sleep(1000);
        } catch (InterruptedException e) {
          throw new RuntimeException(e);
        }
      }
      List output = fileToList(className + "Output.txt");
      if((flags & IGNORE_ORDER) == IGNORE_ORDER)
        OutputVerifier.verifyIgnoreOrder(output, exp);
      else if((flags & AT_LEAST) == AT_LEAST)
        OutputVerifier.verifyAtLeast(output,
          arrayToList(exp));
      else
        OutputVerifier.verify(output, arrayToList(exp));
    // Clean up the output file - see c06:Detergent.java
    testStream.openOutputFile();
  }
  public void expect(Object[] expected) {
    expect(expected, EXACT);
  }
  public void expect(Object[] expectFirst,
    String fname, int flags) {
    List expected = fileToList(fname);
    for(int i = 0; i < expectFirst.length; i++)
      expected.add(i, expectFirst[i]);
    expect(expected.toArray(), flags);
  }
  public void expect(Object[] expectFirst, String fname) {
    expect(expectFirst, fname, EXACT);
  }
  public void expect(String fname) {
    expect(new Object[] {}, fname, EXACT);
  }
} ///:~
