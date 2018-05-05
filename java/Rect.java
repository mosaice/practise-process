/**
 * Rect
 */
public class Rect {
  protected int width, height;
  Rect() {
    this(10, 10);
  }

  Rect(int w, int h) {
    width = w;
    height = h;
  }

  public int area() {
    return width * height;
  }

  public int perimeter() {
    return 2 * (width * height);
  }

  public String toString() {
    return String.format("Rect area: %d, perimeter: %d", area(), perimeter());
  }

  public static void main(String[] args) {
    Rect r = new Rect();
    System.out.println(r);
  }
  
}