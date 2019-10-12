public class Queue<T> implements QueueInterface<T> {

  private Node<T> first;
  private Node<T> last;

  public boolean isEmpty() {
    return last == null;
  }

  // post: Adds the given item to the queue
  public void enqueue(T item) {
    Node<T> newNode = new Node<>(item);
    if (isEmpty()) {
      first = last = newNode;
      return;
    }
    last.setNext(newNode);
    last = newNode;
  }

  // post: Removes and returns the head of the queue. It throws an
  //      exception if the queue is empty.
  public T dequeue() throws QueueException {
    if (isEmpty()) {
      throw new QueueException("Queue is empty");
    }
    Node<T> head = first;
    if (first.getNext() != null) {
      first = first.getNext();
    } else {
      first = last = null;
    }
    return head.getItem();
  }
}
