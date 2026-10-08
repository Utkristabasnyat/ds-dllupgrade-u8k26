
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
  DoublyLinkedList list;

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);
  list.push_back(50);

  cout << "Original list: ";
  list.print();

  // delete the head by value
  list.delete_val(10);
  cout << "After delete_val(10): ";
  list.print();

  // remove the first node
  list.pop_front();
  cout << "After pop_front(): ";
  list.print();

  cout << "Backward: ";
  list.print_reverse();

  // test a list with one node
  DoublyLinkedList singleList;
  singleList.push_back(99);
  singleList.pop_front();

  cout << "Single-node list after pop_front(): ";
  singleList.print();

  // test an empty list
  singleList.pop_front();
  cout << "Empty list after pop_front(): ";
  singleList.print();

  return 0;
}
