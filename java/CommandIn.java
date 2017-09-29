import java.util.Scanner;
import  java.text.MessageFormat;
public class CommandIn {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    System.out.print("test command input: ");
    String test = MessageFormat.format("get input word: {1}", in.nextLine());
    // String test = String.format("get input word: %s", in.nextLine());
    System.out.println(test);
  }
}