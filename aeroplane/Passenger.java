package aeroplane;

public abstract class Passenger {
  String firstName, surname;

  boolean isAdult() {
    return true;
  }

    @Override
    public String toString() {
      return firstName + surname;
    }
}
