import java.util.Arrays;
import java.util.Comparator;

class Birthday {
  int year, month, date;
  Birthday(int y, int m, int d) {
    year = y;
    month = m;
    date = d;
  }
  @Override
  public String toString() {
    return String.format("%d/%d/%d", year, month, date);
  }
}
enum Sex {
  MALE, FEMALE;
}

class Person {
  String name;
  Sex sex;
  Birthday birthday;
  double weight;
  float height;

  Person(String n, Sex s, Birthday b, double w, float h) {
    name = n;
    sex = s;
    birthday = b;
    weight = w;
    height = h;
  }

  @Override
  public String toString() {
    return String.format("%s is %s, born on %s,weight is %.2f, height is %.1f", name, sex, birthday, weight, height);
  }
}

class MyComparator implements Comparator<Person> {
  @Override
  public int compare(Person o1, Person o2) {
    if (o1.height == o2.height) return 0;
    return o1.height > o2.height ? 1 : -1;
  }
}

/**
 * Test
 */
public class PersonTest {
  public static void main(String[] args) {
    Person[] p = new Person[10];
    for (int i = 0; i < p.length; i++) {
      boolean odd = i % 2 == 1;
      p[i] = new Person(
        "person" + i,
        odd ? Sex.FEMALE : Sex.MALE,
        new Birthday(2000, i + 1, odd ? i + 10 : i + 20 ),
        Math.random() * 40 + 100,
        (float)(Math.random() * 40 + 160)
      );
    }
    Comparator personComparator = new MyComparator();
    Arrays.sort(p, personComparator);

    for (Person pi : p) {
      System.out.println(pi);
    }
  }
  
}
