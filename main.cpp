
#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
  struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val, Node* p = nullptr, Node* n = nullptr) {
      data = val;
      prev = p;
      next = n;
    }
  };

  Node* head;
  Node* tail;

public:
  // constructor
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  void push_back(int value) {
    Node* newNode = new Node(value);

    if (!tail)
      head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  void push_front(int value) {
    Node* newNode = new Node(value);

    if (!head)
      head = tail = newNode;
    else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  void insert_after(int value, int position) {
    if (position < 0) {
      cout << "Position must be >= 0." << endl;
      return;
    }

    Node* newNode = new Node(value);

    if (!head) {
      head = tail = newNode;
      return;
    }

    Node* temp = head;

    for (int i = 0; i < position && temp; ++i)
      temp = temp->next;

    if (!temp) {
      cout << "Position exceeds list size. Node not inserted.\n";
      delete newNode;
      return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next)
      temp->next->prev = newNode;
    else
      tail = newNode;

    temp->next = newNode;
  }

  // delete a node by its value
  void delete_val(int value) {
    if (!head)
      return;

    Node* temp = head;

    while (temp && temp->data != value)
      temp = temp->next;

    if (!temp)
      return;

    if (temp->prev)
      temp->prev->next = temp->next;
    else
      head = temp->next;

    if (temp->next)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;

    delete temp;
  }

  // remove the first node
  void pop_front() {
    if (!head)
      return;

    Node* temp = head;
    head = head->next;

    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;

    delete temp;
  }

  // remove the last node
  void pop_back() {
    if (!tail)
      return;

    Node* temp = tail;
    tail = tail->prev;

    if (tail)
      tail->next = nullptr;
    else
      head = nullptr;

    delete temp;
  }

  // delete a node by its position
  void delete_pos(int position) {
    if (position < 0 || !head)
      return;

    Node* temp = head;

    for (int i = 0; i < position && temp; i++)
      temp = temp->next;

    if (!temp)
      return;

    if (temp->prev)
      temp->prev->next = temp->next;
    else
      head = temp->next;

    if (temp->next)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;

    delete temp;
  }

  void print() {
    Node* current = head;

    if (!current) {
      cout << "List is empty" << endl;
      return;
    }

    while (current) {
      cout << current->data << " ";
      current = current->next;
    }

    cout << endl;
  }

  void print_reverse() {
    Node* current = tail;

    if (!current) {
      cout << "List is empty" << endl;
      return;
    }

    while (current) {
      cout << current->data << " ";
      current = current->prev;
    }

    cout << endl;
  }

  // destructor
  ~DoublyLinkedList() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
};

int main() {
  // test deleting by value
  cout << "TEST 1: delete_val()" << endl;

  DoublyLinkedList list1;
  for (int i = 10; i <= 50; i += 10)
    list1.push_back(i);

  cout << "Original: ";
  list1.print();

  list1.delete_val(10);
  cout << "Delete head (10): ";
  list1.print();

  list1.delete_val(30);
  cout << "Delete middle (30): ";
  list1.print();

  list1.delete_val(50);
  cout << "Delete tail (50): ";
  list1.print();

  cout << "Backward: ";
  list1.print_reverse();

  // test deleting by position
  cout << endl << "TEST 2: delete_pos()" << endl;

  DoublyLinkedList list2;
  for (int i = 10; i <= 50; i += 10)
    list2.push_back(i);

  cout << "Original: ";
  list2.print();

  list2.delete_pos(0);
  cout << "Delete position 0 (head): ";
  list2.print();

  list2.delete_pos(1);
  cout << "Delete position 1 (middle): ";
  list2.print();

  list2.delete_pos(2);
  cout << "Delete position 2 (tail): ";
  list2.print();

  list2.delete_pos(-1);
  list2.delete_pos(10);
  cout << "After invalid positions: ";
  list2.print();

  cout << "Backward: ";
  list2.print_reverse();

  // test removing the first node
  cout << endl << "TEST 3: pop_front()" << endl;

  DoublyLinkedList list3;
  list3.push_back(10);
  list3.push_back(20);
  list3.push_back(30);

  cout << "Original: ";
  list3.print();

  list3.pop_front();
  cout << "After pop_front(): ";
  list3.print();

  list3.pop_front();
  list3.pop_front();
  cout << "After removing all nodes: ";
  list3.print();

  list3.pop_front();
  cout << "Pop from empty list: ";
  list3.print();

  // test removing the last node
  cout << endl << "TEST 4: pop_back()" << endl;

  DoublyLinkedList list4;
  list4.push_back(10);
  list4.push_back(20);
  list4.push_back(30);

  cout << "Original: ";
  list4.print();

  list4.pop_back();
  cout << "After pop_back(): ";
  list4.print();

  cout << "Backward: ";
  list4.print_reverse();

  list4.pop_back();
  list4.pop_back();
  cout << "After removing all nodes: ";
  list4.print();

  list4.pop_back();
  cout << "Pop from empty list: ";
  list4.print();

  // test deleting the only node and empty lists
  cout << endl << "TEST 5: Single and Empty Lists" << endl;

  DoublyLinkedList list5;
  list5.push_back(99);
  list5.delete_pos(0);
  cout << "Delete only node by position: ";
  list5.print();

  list5.delete_val(99);
  list5.delete_pos(0);
  cout << "Delete from empty list: ";
  list5.print();

  return 0;
}
