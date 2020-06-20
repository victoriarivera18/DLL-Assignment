// header file for the templated DLList

// V. Rivera Casanova
// CSCE 221
// Leyk 199

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

# include <stdexcept>
# include <iostream>
# include <string>
# include <cmath>
using namespace std;


// class DLList; // class declaration

// doubly linked list node
template<typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e = T(), DLListNode<T> *p = nullptr, DLListNode<T> *n = nullptr):obj(e), prev(p), next(n) {}
};

// doubly linked list class
template<typename T>
class DLList {
  private:
    DLListNode<T> header, trailer;
  public:
    DLList() : header(T()), trailer(T())  { header.next = &trailer; trailer.prev = &header; } // default constructor
    DLList(const DLList<T>& dll); // copy constructor
    DLList(DLList<T>&& dll); // move constructor
    ~DLList(); // destructor
    DLList<T>& operator=(const DLList<T>& dll); // copy assignment operator
    DLList<T>& operator=(DLList<T>&& dll); // move assignment operator
    // return the pointer to the first node
    DLListNode<T> *first_node() const { return header.next; } 
    // return the pointer to the trailer
    const DLListNode<T> *after_last_node() const { return &trailer; }
    // return if the list is empty
    bool is_empty() const { return header.next == &trailer; }
    T first() const; // return the first object
    T last() const; // return the last object
    void insert_first(T obj); // insert to the first node
    T remove_first(); // remove the first node
    void insert_last(T obj); // insert to the last node
    T remove_last(); // remove the last node
    void insert_after(DLListNode<T> &p, T obj);
    void insert_before(DLListNode<T> &p, T obj);
    T remove_after(DLListNode<T> &p);
    T remove_before(DLListNode<T> &p);
};

// output operator
// ostream& operator<<(ostream& out, const DLList& dll);


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
template<typename T>
DLList<T>::DLList(const DLList<T>& dll)  // O(n)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DLListNode<T>* index = dll.first_node();
  while (index != dll.after_last_node()) {
    insert_last(index->obj);
    index = index->next;
  }

}
// move constructor
template<typename T>
DLList<T>::DLList(DLList<T>&& dll) // O(1), only moving the header and trialer pointers
{
  // shallow copy of paramter
  header = dll.header;
  trailer = dll.trailer;
  dll.header.next = &trailer;
  dll.trailer.prev = &header;
}

// copy assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll)// O(n)
{
  if (this == &dll) {
    return *this;
  } else {
    DLListNode<T> *current= first_node();
    DLListNode<T> *temp = first_node();
    while (temp!= after_last_node()) {
      current = temp;
      temp = temp->next;
      delete current;
    }
    
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode<T> *toAdd = dll.first_node();
    while (toAdd != dll.after_last_node()) {
      insert_last(toAdd->obj);
      toAdd = toAdd->next;
    }
  }

  return *this;
}

// move assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll)  // O(n)
{
  if (this == &dll) {
    return *this;
  } else {
    DLListNode<T> *current= first_node();
    DLListNode<T> *temp = first_node();
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
template<typename T>
DLList<T>::~DLList() //O(n)
{
  DLListNode<T> *previous = header.next;
  DLListNode<T> *current = header.next;

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
template<typename T>
void DLList<T>::insert_first(T obj)
{ 
  DLListNode<T> *toAdd = new DLListNode<T>(obj, &header, header.next);
  header.next->prev = toAdd;
  header.next = toAdd;
}

// insert a new object as the last one
template<typename T>
void DLList<T>::insert_last(T obj)
{
  DLListNode<T> *toAdd = new DLListNode<T>(obj, trailer.prev, &trailer);
  trailer.prev->next = toAdd;
  trailer.prev = toAdd;
}

// remove the first node from the list
template <typename T>
T DLList<T>::remove_first()
{
  if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    DLListNode<T>* temp = header.next;
    temp->next->prev = &header;
    header.next = temp->next;
    T obj = temp->obj;
    delete temp;  //temp is old header
    return obj;
  }

}

// remove the last node from the list
template<typename T>
T DLList<T>::remove_last()
{
	if (is_empty()) {
    throw EmptyDLList("List is empty!");
  }
	DLListNode<T> *node = trailer.prev;
	node->prev->next = &trailer;
	trailer.prev = node->prev;
	T obj = node->obj;
	delete node;
	return obj;
}

// return the first object (do not remove)
template<typename T>
T DLList<T>::first() const
{ 
   if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    return header.next->obj;
  }
}

// return the last object (do not remove)
template<typename T>
T DLList<T>::last() const
{
  if (is_empty()){
    throw EmptyDLList("List is empty!");
  } else {
    return trailer.prev->obj;
  }
}

// insert a new node after the node p
template<typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
  // if at the end
  if (p.next == &trailer) {
    insert_last(obj);
  } else {
			DLListNode<T> *toAdd = new DLListNode<T>(obj, &p, p.next);
			p.next->prev = toAdd;
			p.next = toAdd;
  }
}

// insert a new node before the node p
template<typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
  //check if previous is "head"
  if(p.prev == &header) {
    insert_first(obj);
  } else {
			DLListNode<T> *toAdd = new DLListNode<T>(obj, p.prev, &p);
			p.prev->next = toAdd;
			p.prev = toAdd;
    //cout << "Node inserted before ";
  }
}

// remove the node after the node p
template<typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
	if (is_empty()) {
    throw EmptyDLList("List is empty!");
  }
	DLListNode<T> *node = p.next;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	T obj = node->obj;
	delete node;
	return obj;

}

// remove the node before the node p
template<typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
	if (is_empty()) {
    throw EmptyDLList("List is empty!");
  }
	DLListNode<T> *node = p.prev;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	T obj = node->obj;
	delete node;
	return obj;
}

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll) //O(n)
{  
  DLListNode<T>* temp = dll.first_node();
  int nodeNum = 0;
  cout << endl;
  while (temp != dll.after_last_node()) {
    out << "Node: " << nodeNum << " -- " << temp->obj << endl;
    temp = temp->next;
    nodeNum++;
  }
  return out;
}

#endif
