package aeroplane;

public class EconomyPassenger extends Passenger {
  private int age;

  public EconomyPassenger(String firstName, String surname, int age) {
    this.firstName = firstName;
    this.surname = surname;
    this.age = age;
  }

  @Override
  boolean isAdult() {
    return age >= 18;
  }

  @Override
  public String toString() {
    return "Economy" + super.toString() + age;
  }
}
