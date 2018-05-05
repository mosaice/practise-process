import java.util.Scanner;
/**
 * NumDiff
 */
public class NumDiff {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    System.out.print("请输入第一个数: ");
    int a = s.nextInt();
    System.out.print("\n请输入第二个数: ");
    int b = s.nextInt();
    System.out.print("\n");

    System.out.format("最大公倍数是： %d, 最小公约数是: %d\n", Diff.GCD(a, b), Diff.LCM(a, b));
  }
  
}

class Diff {
  public static int GCD(int a, int b) {
    int t;
    while (b != 0) {
      t = a % b;
      a = b;
      b = t;
    }
    return a;
  }
  public static int LCM(int a, int b) {
    return (a * b) / GCD(a, b);
  }
}