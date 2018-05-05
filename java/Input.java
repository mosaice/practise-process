
import java.io.*;




/**
 * Input
 */
public class Input {

  public static void main(String[] args) throws IOException {
    BufferedReader buff = new BufferedReader(new InputStreamReader(System.in));
    char c;
    int count = 0;
    while ((c = (char)(buff.read())) != '#') {
      count++;
    }
    System.out.format("char length: %d", count);
  }
}