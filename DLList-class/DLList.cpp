// implementation of the DLList class
// V. Rivera Casanova
// CSCE 221
// Leyk 199


# include <stdexcept>
# include <iostream>
# include <cmath>
using namespace std;

#include "DLList.h"


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
DLList::DLList(const DLList& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DLListNode* index = dll.first_node();
  while (index != dll.after_last_node()) {
    insert_last(index->obj);
    index = index->next;
  }

}
// move constructor
DLList::DLList(DLList&& dll)
{
  // shallow copy of paramter
  header = dll.header;
  trailer = dll.trailer;
  dll.header.next = &trailer;
  dll.trailer.prev = &header;
}

// copy assignment operator
DLList& DLList::operator=(const DLList& dll)  // need to do this
{
  if (this == &dll) {
    return *this;
  } else {
    DLListNode *current= first_node();
    DLListNode *temp = first_node();
    while (temp!= after_last_node()) {
      current = temp;
      temp = temp->next;
      delete current;
    }
    
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode *toAdd = dll.first_node();
    while (toAdd != dll.after_last_node()) {
      insert_last(toAdd->obj);
      toAdd = toAdd->next;
    }
  }

  return *this;
}

// move assignment operator
DLList& DLList::operator=(DLList&& dll)  // ned to finish this
{
  if (this == &dll) {
    return *this;
  } else {
    DLListNode *current= first_node();
    DLListNode *temp = first_node();
    while (temp != after_last_node()) {
      current = temp;
      temp = temp->next;
      delete current;
    }

    header = dll.header;
    trailer = dll.trailer;

    dll.header.next = &trailer;
    dll.trailer.prev = &header;
  }

  return *this;
}

// destructor
DLList::~DLList()
{
  DLListNode *previous = header.next;
  DLListNode *current = header.next;

  while (current !=  &trailer) {
    previous = current;
    current = current->next;
    delete previous;
  }
  //definition of empty list 
  header.next = &trailer;
  trailer.prev = &header;
}

// insert a new object as the first one
void DLList::insert_first(int obj)
{ 
  DLListNode *toAdd = new DLListNode(obj, &header, header.next);
  header.next->prev = toAdd;
  header.next = toAdd;
}

// insert a new object as the last one
void DLList::insert_last(int obj)
{
  DLListNode *toAdd = new DLListNode(obj, trailer.prev, &trailer);
  trailer.prev->next = toAdd;
  trailer.prev = toAdd;
}

// remove the first node from the list
int DLList::remove_first()
{
  if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    DLListNode* temp = header.next;
    temp->next->prev = &header;
    header.next = temp->next;
    int obj = temp->obj;
    delete temp;  //temp is old header
    return obj;
  }

}

// remove the last node from the list
int DLList::remove_last()
{
  if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    DLListNode* temp = trailer.prev;
    temp->prev->next = &trailer;
    trailer.prev = temp->prev;
    int obj = temp->obj;
    delete temp;  //temp is old header
    return obj;
  }
}

// return the first object (do not remove)
int DLList::first() const
{ 
   if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    return header.next->obj;
  }
}

// return the last object (do not remove)
int DLList::last() const
{
  if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    return trailer.prev->obj;
  }
}

// insert a new node after the node p
void DLList::insert_after(DLListNode &p, int obj)
{
  // if at the end
	DLListNode *toAdd = new DLListNode(obj, &p, p.next);
	p.next->prev = toAdd;
	p.next = toAdd;
}
// insert a new node before the node p
void DLList::insert_before(DLListNode &p, int obj)
{
  //check if previous is "head"
	DLListNode *toAdd = new DLListNode(obj, p.prev, &p);
	p.prev->next = toAdd;
	p.prev = toAdd;
}

// remove the node after the node p
int DLList::remove_after(DLListNode &p)
{
	if (is_empty()) {
    throw EmptyDLList("List is empty!");
  }
	DLListNode *node = p.next;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	int obj = node->obj;
	delete node;
	return obj;
}

// remove the node before the node p
int DLList::remove_before(DLListNode &p)
{
	if (is_empty()) {
    throw EmptyDLList("List is empty!");
  }
	DLListNode *node = p.prev;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	int obj = node->obj;
	delete node;
	return obj;
}
// output operator
ostream& operator<<(ostream& out, const DLList& dll)
{  
  DLListNode* temp = dll.first_node();
  int nodeNum = 0;
  cout << endl;
  while (temp != dll.after_last_node()) {
    out << "Node: " << nodeNum << " -- " << temp->obj << endl;
    temp = temp->next;
    nodeNum++;
  }
  return out;
}
