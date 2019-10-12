package aeroplane;

import java.util.NoSuchElementException;
import java.util.Objects;

public class Seat {

  private int row;
  private char letter;
  private int[] emergencyrows = {1, 10, 30};
  private final int endRow = 50;
  private final char endLetter = 'F';

  public Seat(int row, char letter) {
    this.row = row;
    this.letter = letter;
  }

  @Override
  public String toString() {
    return "" + row + letter;
  }

  boolean isEmergencyExit() {
    for (int i = 0; i < emergencyrows.length; i++) {
      if (emergencyrows[i] == row) {
        return true;
      }
    }
    return false;
  }

  boolean hasNext() {
    return row != endRow || letter != endLetter;
  }

  Seat next() throws java.util.NoSuchElementException {
    if (!hasNext()) {
      throw new NoSuchElementException();
    }
    if (letter == endLetter) {
      return new Seat(row + 1, 'A');
    }
    return new Seat(row, (char) (letter + 1));
  }

  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Seat)) {
      return false;
    }
    Seat seat = (Seat) obj;
    return seat.row == row && seat.letter == letter;
  }

  @Override
  public int hashCode() {
    return Objects.hash(row, letter);
  }
}
