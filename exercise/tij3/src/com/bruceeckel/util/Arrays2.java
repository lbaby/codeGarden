//: com:bruceeckel:util:Arrays2.java
// A supplement to java.util.Arrays, to provide additional
// useful functionality when working with arrays. Allows
// any array to be converted to a String, and to be filled
// via a user-defined "generator" object.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.util;
import java.util.*;

public class Arrays2 {
  public static String toString(boolean[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(byte[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(char[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(short[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(int[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(long[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(float[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  public static String toString(double[] a) {
    StringBuffer result = new StringBuffer("[");
    for(int i = 0; i < a.length; i++) {
      result.append(a[i]);
      if(i < a.length - 1)
        result.append(", ");
    }
    result.append("]");
    return result.toString();
  }
  // Fill an array using a generator:
  public static void fill(Object[] a, Generator gen) {
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(Object[] a, int from, int to, Generator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void
  fill(boolean[] a, BooleanGenerator gen) {
      fill(a, 0, a.length, gen);
  }
  public static void
  fill(boolean[] a, int from, int to,BooleanGenerator gen){
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(byte[] a, ByteGenerator gen) {
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(byte[] a, int from, int to, ByteGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(char[] a, CharGenerator gen) {
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(char[] a, int from, int to, CharGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(short[] a, ShortGenerator gen) {
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(short[] a, int from, int to, ShortGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(int[] a, IntGenerator gen) {
      fill(a, 0, a.length, gen);
  }
  public static void
  fill(int[] a, int from, int to, IntGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(long[] a, LongGenerator gen) {
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(long[] a, int from, int to, LongGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(float[] a, FloatGenerator gen) {
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(float[] a, int from, int to, FloatGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  public static void fill(double[] a, DoubleGenerator gen){
    fill(a, 0, a.length, gen);
  }
  public static void
  fill(double[] a, int from, int to, DoubleGenerator gen) {
    for(int i = from; i < to; i++)
      a[i] = gen.next();
  }
  private static Random r = new Random();
  public static class
  RandBooleanGenerator implements BooleanGenerator {
    public boolean next() { return r.nextBoolean(); }
  }
  public static class
  RandByteGenerator implements ByteGenerator {
    public byte next() { return (byte)r.nextInt(); }
  }
  private static String ssource =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  private static char[] src = ssource.toCharArray();
  public static class
  RandCharGenerator implements CharGenerator {
    public char next() {
      return src[r.nextInt(src.length)];
    }
  }
  public static class
  RandStringGenerator implements Generator {
    private int len;
    private RandCharGenerator cg = new RandCharGenerator();
    public RandStringGenerator(int length) {
      len = length;
    }
    public Object next() {
      char[] buf = new char[len];
      for(int i = 0; i < len; i++)
        buf[i] = cg.next();
      return new String(buf);
    }
  }
  public static class
  RandShortGenerator implements ShortGenerator {
    public short next() { return (short)r.nextInt(); }
  }
  public static class
  RandIntGenerator implements IntGenerator {
    private int mod = 10000;
    public RandIntGenerator() {}
    public RandIntGenerator(int modulo) { mod = modulo; }
    public int next() { return r.nextInt(mod); }
  }
  public static class
  RandLongGenerator implements LongGenerator {
    public long next() { return r.nextLong(); }
  }
  public static class
  RandFloatGenerator implements FloatGenerator {
    public float next() { return r.nextFloat(); }
  }
  public static class
  RandDoubleGenerator implements DoubleGenerator {
    public double next() {return r.nextDouble();}
  }
} ///:~