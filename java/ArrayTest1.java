/**
 * ArrayTest1
 */
public class ArrayTest1 {
  public static void main(String[] args) {
    char[] c = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    char[] cc = new char[7];
    System.out.println(new String(c));
    System.arraycopy(c, 2, cc, 0, 5);
    System.out.println(new String(cc));

    char[][] table = {{'a','b'}, {'c','d'}, {'e','f'}};
    System.out.println(new String(table[0]));
  }
}