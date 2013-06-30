//: com:bruceeckel:simpletest:TestExpression.java
// Regular expression for testing program output lines
// From 'Thinking in Java, 3rd ed.' (c) Bruce Eckel 2002
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
package com.bruceeckel.simpletest;
import java.util.regex.*;

public class TestExpression implements Comparable {
  private Pattern p;
  private String expression;
  private boolean isRegEx;
  // Default to only one instance of this expression:
  private int duplicates = 1;
  public TestExpression(String s) {
    this.expression = s;
    if(expression.startsWith("%% ")) {
      this.isRegEx = true;
      expression = expression.substring(3);
      this.p = Pattern.compile(expression);
    }
  }
  // For duplicate instances:
  public TestExpression(String s, int duplicates) {
    this(s);
    this.duplicates = duplicates;
  }
  public String toString() {
    if(isRegEx) return p.pattern();
    return expression;
  }
  public boolean equals(Object obj) {
    if(this == obj) return true;
    if(isRegEx) return (compareTo(obj) == 0);
    return expression.equals(obj.toString());
  }
  public int compareTo(Object obj) {
    if((isRegEx) && (p.matcher(obj.toString()).matches()))
      return 0;
    return
      expression.compareTo(obj.toString());
  }
  public int getNumber() {  return duplicates; }
  public String getExpression() { return expression;}
  public boolean isRegEx() { return isRegEx; }
} ///:~
