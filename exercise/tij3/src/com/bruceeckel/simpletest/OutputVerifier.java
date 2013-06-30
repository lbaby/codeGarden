//: com:bruceeckel:simpletest:OutputVerifier.java
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.simpletest;
import java.util.*;
import java.io.PrintStream;

public class OutputVerifier {
  private static void verifyLength(
    int output, int expected, int compare) {
    if((compare == Test.EXACT && expected != output)
      || (compare == Test.AT_LEAST && output < expected))
      throw new NumOfLinesException(expected, output);
  }
  public static void verify(List output, List expected) {
    verifyLength(output.size(),expected.size(),Test.EXACT);
    if(!expected.equals(output)) {
      //find the line of mismatch
      ListIterator it1 = expected.listIterator();
      ListIterator it2 = output.listIterator();
      while(it1.hasNext()
        && it2.hasNext()
        && it1.next().equals(it2.next()));
      throw new LineMismatchException(
        it1.nextIndex(), it1.previous().toString(),
        it2.previous().toString());
    }
  }
  public static void
  verifyIgnoreOrder(List output, Object[] expected) {
    verifyLength(expected.length,output.size(),Test.EXACT);
    if(!(expected instanceof String[]))
      throw new RuntimeException(
        "IGNORE_ORDER only works with String objects");
    String[] out = new String[output.size()];
    Iterator it = output.iterator();
    for(int i = 0; i < out.length; i++)
      out[i] = it.next().toString();
    Arrays.sort(out);
    Arrays.sort(expected);
    int i =0;
    if(!Arrays.equals(expected, out)) {
      while(expected[i].equals(out[i])) {i++;}
      throw new SimpleTestException(
        ((String) out[i]).compareTo(expected[i]) < 0
          ? "output: <" + out[i] + ">"
          : "expected: <" + expected[i] + ">");
    }
  }
  public static void
  verifyAtLeast(List output, List expected) {
    verifyLength(output.size(), expected.size(),
      Test.AT_LEAST);
    if(!output.containsAll(expected)) {
      ListIterator it = expected.listIterator();
      while(output.contains(it.next())) {}
      throw new SimpleTestException(
        "expected: <" + it.previous().toString() + ">");
    }
  }
} ///:~
