package aeroplane;

public class CrewPassenger extends Passenger {
  public CrewPassenger(String firstName, String surname) {
    this.firstName = firstName;
    this.surname = surname;
  }

    @Override
    public String toString() {
        return "Crew" + super.toString();
    }
}
