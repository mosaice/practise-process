
/**
 * Patient
 */
class Patient {
  private String name;
  private char sex;
  private int age;
  private float weight;
  private boolean allergies;

  public void setName(String str) {
    name = str;
  }
  public void setSex(char c) {
    sex = c;
  }
  public void setAge(int i) {
    age = i;
  }
  public void setWeight(float f) {
    weight = f;
  }
  public void setAllergies(Boolean b) {
    allergies = b;
  }

  public String toString() {
    return String.format("name: %s sex: %c age: %d weight: %f allergies: %b", name, sex, age, weight, allergies);
  }
}

/**
 * PatientTest
 */
public class PatientTest {
  public static void main(String[] args) {
    Patient p1 = new Patient();
    Patient p2 = new Patient();

    p1.setName("test");
    p1.setAge(20);
    p1.setSex('M');
    p1.setWeight(100.5f);
    p1.setAllergies(false);

    p2.setName("test2");
    p2.setAge(10);
    p2.setSex('F');
    p2.setWeight(50.5f);
    p2.setAllergies(true);

    System.out.println(p1);
    System.out.println(p2);
  }
  ·
}