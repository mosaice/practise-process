/**
 * RandomInt
 */
public class RandomInt {
  public static void main(String[] args) {
    int[] arr = new int[100];
    int max = 0, min = 0, count = 0, loop = 100;
    boolean first = true;

    while (loop-- != 0) {
      arr[loop] = (int)(Math.random() * 100);
      if (first) {
        max = min = arr[loop];
        first = false;
      }
      if (arr[loop] > 50) count++;
      if (max < arr[loop]) max = arr[loop];
      if (min > arr[loop]) min = arr[loop];
    }

    System.out.format("max = %d, min = %d, count of > 50 = %d\n", max, min, count);

  }
}