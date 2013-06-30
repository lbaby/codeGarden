//: com:bruceeckel:simpletest:TestStream.java
// Simple utility for testing program output. Intercepts
// System.out to print both to the console and a buffer.
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.simpletest;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class TestStream extends PrintStream {
  protected int numOfLines;
  private PrintStream
    console = System.out,
    err = System.err,
    fout;
  // To store lines sent to System.out or err
  private InputStream stdin;
  private String className;
  public TestStream(String className) {
    super(System.out, true); // Autoflush
    System.setOut(this);
    System.setErr(this);
    stdin = System.in; // Save to restore in dispose()
    // Replace the default version with one that
    // automatically produces input on demand:
    System.setIn(new BufferedInputStream(new InputStream(){
      char[] input = ("test\n").toCharArray();
      int index = 0;
      public int read() {
        return
          (int)input[index = (index + 1) % input.length];
      }
    }));
    this.className = className;
    openOutputFile();
  }
  // public PrintStream getConsole() { return console; }
  public void dispose() {
    System.setOut(console);
    System.setErr(err);
    System.setIn(stdin);
  }
  // This will write over an old Output.txt file:
  public void openOutputFile() {
    try {
      fout = new PrintStream(new FileOutputStream(
        new File(className + "Output.txt")));
    } catch (FileNotFoundException e) {
      throw new RuntimeException(e);
    }
  }
  // Override all possible print/println methods to send
  // intercepted console output to both the console and
  // the Output.txt file:
  public void print(boolean x) {
    console.print(x);
    fout.print(x);
  }
  public void println(boolean x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(char x) {
    console.print(x);
    fout.print(x);
  }
  public void println(char x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(int x) {
    console.print(x);
    fout.print(x);
  }
  public void println(int x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(long x) {
    console.print(x);
    fout.print(x);
  }
  public void println(long x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(float x) {
    console.print(x);
    fout.print(x);
  }
  public void println(float x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(double x) {
    console.print(x);
    fout.print(x);
  }
  public void println(double x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(char[] x) {
    console.print(x);
    fout.print(x);
  }
  public void println(char[] x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(String x) {
    console.print(x);
    fout.print(x);
  }
  public void println(String x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void print(Object x) {
    console.print(x);
    fout.print(x);
  }
  public void println(Object x) {
    numOfLines++;
    console.println(x);
    fout.println(x);
  }
  public void println() {
    if(false) console.print("println");
    numOfLines++;
    console.println();
    fout.println();
  }
  public void
  write(byte[] buffer, int offset, int length) {
    console.write(buffer, offset, length);
    fout.write(buffer, offset, length);
  }
  public void write(int b) {
    console.write(b);
    fout.write(b);
  }
} ///:~
