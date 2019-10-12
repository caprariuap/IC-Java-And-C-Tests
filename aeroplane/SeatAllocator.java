package aeroplane;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class SeatAllocator {

  private Map<Seat, Passenger> allocation;

  private static final String CREW = "crew";
  private static final String BUSINESS = "business";
  private static final String ECONOMY = "economy";

  public SeatAllocator() {
    allocation = new HashMap<Seat, Passenger>();
  }

  @Override
  public String toString() {
    return allocation.toString();
  }

  private void allocateInRange(Passenger passenger, Seat first, Seat last)
      throws AeroplaneFullException {
    for (Seat i = first; !i.equals(last); i = i.next()) {
      if (!allocation.containsKey(i) && (!i.isEmergencyExit() || passenger.isAdult())) {
        allocation.put(i, passenger);
        return;
      }
    }
    if (!allocation.containsKey(last) && (!last.isEmergencyExit() || passenger.isAdult())) {
      allocation.put(last, passenger);
      return;
    }
    throw new AeroplaneFullException();
  }

  private static String readStringValue(BufferedReader br)
      throws MalformedDataException, IOException {

    String result = br.readLine();

    if (result == null) {
      throw new MalformedDataException();
    }

    return result;
  }

  private static int readIntValue(BufferedReader br) throws MalformedDataException, IOException {
    try {
      return Integer.parseInt(readStringValue(br));
    } catch (NumberFormatException e) {
      throw new MalformedDataException();
    }
  }

  private static Luxury readLuxuryValue(BufferedReader br)
      throws MalformedDataException, IOException {
    try {
      return Luxury.valueOf(readStringValue(br));
    } catch (IllegalArgumentException e) {
      throw new MalformedDataException();
    }
  }

  public void allocate(String filename) throws IOException, AeroplaneFullException {

    BufferedReader br = new BufferedReader(new FileReader(filename));

    String line;
    while ((line = br.readLine()) != null) {
      try {
        if (line.equals(CREW)) {
          allocateCrew(br);
        } else if (line.equals(BUSINESS)) {
          allocateBusiness(br);
        } else if (line.equals(ECONOMY)) {
          allocateEconomy(br);
        } else {
          throw new MalformedDataException();
        }
      } catch (MalformedDataException e) {
        System.out.println("Skipping malformed line of input");
      }
    }
  }

  private void allocateCrew(BufferedReader br)
      throws IOException, MalformedDataException, AeroplaneFullException {
    String firstName = readStringValue(br);
    String lastName = readStringValue(br);
    Passenger passenger = new CrewPassenger(firstName, lastName);
    allocateInRange(passenger, new Seat(1, 'A'), new Seat(1, 'F'));
  }

  private void allocateBusiness(BufferedReader br)
      throws IOException, MalformedDataException, AeroplaneFullException {
    String firstName = readStringValue(br);
    String lastName = readStringValue(br);
    int age = readIntValue(br);
    Luxury luxury = readLuxuryValue(br);
    Passenger passenger = new BusinessPassenger(firstName, lastName, age, luxury);
    allocateInRange(passenger, new Seat(2, 'A'), new Seat(15, 'F'));
  }

  private void allocateEconomy(BufferedReader br)
      throws IOException, MalformedDataException, AeroplaneFullException {
    String firstName = readStringValue(br);
    String lastName = readStringValue(br);
    int age = readIntValue(br);
    Passenger passenger = new EconomyPassenger(firstName, lastName, age);
    allocateInRange(passenger, new Seat(16, 'A'), new Seat(50, 'F'));
  }

  void upgrade() {
    Seat firstEconomy = new Seat(16, 'A');
    for (Seat i = firstEconomy; i.hasNext(); i = i.next()) {
      if (allocation.containsKey(i)) {
        for (Seat j = new Seat(2, 'A'); !j.equals(firstEconomy); j = j.next()) {
          if (!allocation.containsKey(j)) {
            Passenger passenger = allocation.get(i);
            allocation.remove(i);
            allocation.put(j, passenger);
            break;
          }
        }
      }
    }
  }
}
