/**
 * Fact
 */
public class Fact {

  public static int fact(int n) {
    if (n != 0) {
      return fact(n - 1, n);
    } else {
      return 1;
    }
  }

  public static int fact(int n, int count) {
    if (n != 0) {
      return fact(n - 1, n * count);
    } else {
      return count;
    }
  }

  public static void main(String[] args) {
    for (String arg : args) {
      System.out.format("%s! = %d\n", arg, fact(Integer.parseInt(arg)));
    }
  }
}