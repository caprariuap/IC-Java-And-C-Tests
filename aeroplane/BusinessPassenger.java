package aeroplane;

public class BusinessPassenger extends Passenger {
  private int age;
  Luxury luxury;

  public BusinessPassenger(String firstName, String surname, int age, Luxury luxury) {
    this.firstName = firstName;
    this.surname = surname;
    this.age = age;
    this.luxury = luxury;
  }

  @Override
  boolean isAdult() {
    return age >= 18;
  }

  @Override
  public String toString() {
    return "Business" + super.toString() + age + luxury;
  }
}
