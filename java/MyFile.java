/**
 * File
 */
import java.util.Scanner;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.*;
public class MyFile {
  public String path;
  public Path file;
  public PrintWriter p;

  public MyFile (String path) {
    this.path = path;
    file = Paths.get(path);
    try {
      p = new PrintWriter(path);

    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public void writeSomething(String txt) {
    p.println(txt);
  }

  public static void main(String[] args) {

    try {
      Scanner s = new Scanner(System.in);
      System.out.printf("输入文件名字： ");
      MyFile f = new MyFile(s.nextLine());
      System.out.printf("开始录入 ");
      String line;
      while (!(line = s.nextLine()).equals("!OVER")) {
        f.writeSomething(line);
      }
      f.p.close();
      System.out.println("输入结束");
      Scanner in = new Scanner(f.file);
      while(in.hasNext()) {
        System.out.println(in.nextLine());
      }
      System.out.println("输出结束");      
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}