// testing the templated class DLList

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

#include "TemplatedDLList.h"

using namespace std;

int main ()
{
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DLList<string> dll;
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10; i<=100; i+=10) {
    stringstream ss;
    ss << i;
    dll.insert_last(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10; i<=100; i+=10) {
    stringstream ss;
    ss << i;
    dll.insert_first(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Copy to a new list" << endl;
  DLList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  cout << "Assign to another new list" << endl;
  DLList<string> dll3;
  dll3 = dll;
  cout << "list3: " << dll3 << endl << endl;
  
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0; i<10; i++) {
    dll.remove_last();
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0; i<10; i++) {
    dll.remove_first();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  // more testing...
  // add tests for insert_after, insert_before
  // add tests for remove_after, remove_before
  dll2.insert_after((*dll2.first_node()), "HELLO");
  dll2.insert_before((*dll2.after_last_node()->prev), "BYE");

  cout << "My Own Tests::" << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;
  
  string  remove1 = dll2.remove_after((*dll3.first_node()));
  string remove2 = dll2.remove_before((*dll3.after_last_node()->prev));

  
  cout << "My Own Tests 2::" << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  cout << remove1 << " "<< remove2 << endl;
  
  return 0;
}
