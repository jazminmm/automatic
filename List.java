/*

   Doubly Linked List for Auto

   Beware that this is a list of Objects

 ***In progress***

 */

class List {
  private class Node {
    Node prev;
    Node next;
    Object data;

    Node (Object data) {
      prev = null;
      next = null;
      this.data = data;
    }

    public String toString () {
      return data.toString();
    }
  }

  private Node head;
  private Node tail;
  private Node cur;
  private int size; 
  private int pos;  // 0 is head, size - 1 is tail, -1 is undefined,
  //everywhere else is relative to head and tail

  List () {
    head = tail = cur = null;
    size = 0;
    pos = -1;
  }

  int length () {
    return size;
  }

  int position () {
    return pos;
  }

  Object get (int index) throws RuntimeException {
    if (index >= size || index < 0)
      throw new RuntimeException("Attempted to get data at index "
          + index + " in a list of size " + length());
    moveTo(index);
    return cur.data;
  }

  private void moveTo(int index) {
    if (length() <= 0)
      throw new RuntimeException
        ("Attempted to move to a Node in an empty List");
    if (pos < 0) {
      if (length() - index > index) {
        cur = head;
        pos = 0;
      } else {
        cur = tail;
        pos = length() - 1;
      }
    }
    if (pos > index) {
      while (pos != index) {
        if (cur == null)
          throw new RuntimeException
            ("Current Node has fallen off List");
        pos--;
        cur = cur.prev;
      }
    } else {
      while (pos != index) {
        if (cur == null)
          throw new RuntimeException
            ("Current Node has fallen off List");
        pos++;
        cur = cur.next;
      }
    }
  }

  void prepend (Object data) {
    if (size++ <= 0) {
      head = tail = new Node(data);
      return;
    }
    head.prev = new Node(data);
    head.prev.next = head;
    head = head.prev;
    if (cur != null) pos++;
  }

  void append (Object data) {
    if (size++ <= 0) {
      head = tail = new Node(data);
      return;
    }
    tail.next = new Node(data);
    tail.next.prev = tail;
    tail = tail.next;
  }

  void remove (int index) {
    moveTo(index);
    if (pos != 0) cur.prev.next = cur.next;
    else if (pos != length() - 1) cur.next.prev = cur.prev;
    cur = null;
    pos = -1;
  }

  void remove (Object data) {
    moveTo(0);
    // do this
  }
}
