// Simple doubly linked list - implementation

#include <iostream>

using namespace std;

// a list node
struct Node {
  int data;       // each node holds an integer data
  Node* previous; // pointer to the previous node
  Node* next;     // pointer to the next node
  // constructor
  Node(int d=0, Node* p=nullptr, Node* n=nullptr):data(d), previous(p), next(n) {}
  Node* get_previous() const { return previous; }
  Node* get_next() const { return next; }
  Node* insert_before(int d);  // insert d before this nod
                              // return a pointer to the inserted node
  Node* insert_after(int d);  // insert d after this node
                              // return a pointer to the inserted node
  void delete_before(); // delete the node before this node
  void delete_after();  // delete the node after this node
};

// insert d before this node
// return a pointer to the inserted node
Node* Node::insert_before(int d) {
  Node* toAdd = new Node();
  toAdd->data = d;

  //check if previous is "head"
  if(this->get_previous() == nullptr) {
    this->previous = toAdd;
    toAdd->previous = nullptr;
    toAdd->next = this;
  } else {  // if in the middle
    this->previous->next = toAdd; // getting the one before this to point to the new node (it's next)
    toAdd->previous = this->previous;

    this->previous = toAdd;
    toAdd->next = this;
  }

  return toAdd;
}

// insert d after this node
// return a pointer to the inserted node
Node* Node::insert_after(int d) {
  Node* toAdd = new Node();
  toAdd->data = d;

  // if at the end
  if(this->get_next() == nullptr) {
    toAdd->next = nullptr;
    this->next = toAdd;
    toAdd->previous = this;
  } else {  // if in the middle
    this->next->previous = toAdd; // getting the one before this to point to the new node (it's next)
    toAdd->next = this->next;

    this->next = toAdd;
    toAdd->previous = this;

  }
  
  return toAdd;
}

// delete the node before this node
void Node::delete_before() {
  //check if before is head
  Node* node = this->previous;
	node->previous->next = node->next;
	node->next->previous = node->previous;

	delete node;

  
}

// delete the node after this node
void Node::delete_after() {
// check if after is tail
 	Node *node = this->next;
	node->next->previous = node->previous;
	node->previous->next = node->next;

	delete node;
  
}

// Display a doubly linked list
void display_list(Node* header, Node* trailer) {
  Node* p = header->get_next();

  while (p != trailer) {
    cout << p->data << ", ";
    p = p->get_next();
  }
  cout << endl;
}

// Test program
int main() {
  // Construct a doubly linked list with a header & trailer
  cout << "Create a new list" << endl;
  Node *header = new Node(-1);
  Node *trailer = new Node(-2);
  trailer->previous = header;
  header->next = trailer;
  cout << "list: ";
  display_list(header, trailer);
  cout << endl;
  
  // Insert 10 nodes with values 10,20,30,..,100
  cout << "Insert 10 nodes with values 10,20,30,..,100" << endl;
  for (int i = 10; i <= 100; i += 10) { // O(n)
    trailer->insert_before(i);
  }
  cout << "list: ";
  display_list(header,trailer);
  cout << endl;

  // Insert 10 nodes at front with value 100,90,80,..,10
  cout << "Insert 10 nodes at front with value 100,90,80,..,10" << endl;
  for (int i = 10; i <= 100; i += 10) {
    header->insert_after(i);
  }
  cout << "list: ";
  display_list(header, trailer);
  cout << endl;
  
  // Delete the last 5 nodes
  cout << "Delete the last 5 nodes" << endl;
  for (int i = 0; i < 5; i++) {
    trailer->delete_before();
  }
  cout << "list: ";
  display_list(header, trailer);
  cout << endl;
  
  // Delete the first 5 nodes
  cout << "Delete the first 5 nodes" << endl;
  for (int i = 0; i < 5; i++) {
    header->delete_after();
  }
  cout << "list: ";
  display_list(header, trailer);
  
  return 0;
}

