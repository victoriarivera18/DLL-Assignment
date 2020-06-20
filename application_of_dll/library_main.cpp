// V. Rivera Casanova
// CSCE 221
// Leyk 199

#include "Record.h"
#include "TemplatedDLList.h"
#include "Library.h"

# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <string.h>
using namespace std;

//global variable library
//vector<DLList<Record>> library;
//create stl vector of type dll

// inside, each dll is of type Record (use templatede class)

//read in each book entry and place record in appropriate vector index and link to dll
// make sure is in aphabetical order


// do we need to make certain library class for sorting?
    // searching
    // sorting into dll

int main() {
    string name, title, author, isbn, edition;
    int start = -65;
    int index;
    char letter;
    bool sorted;
     // to insert dll lists into vector
    for(int i = 0; i < 26; i++){
        DLList<Record>* tempList = new DLList<Record>();  //initializing each vector position
        library.push_back((*tempList));
        library.at(i).setNum(i);
    } 

    // input stream 
    // put inside input stream record
    ifstream ifs("Book.txt");
    while (!ifs.eof()) {  //O(n), n is the number of Records to add
        Record temp = Record();
        ifs >> temp; // O(n), n is the number of books 
        //cout << temp;

        name = temp.getTitle();
        letter = toupper(name.at(0));
        index = start + int(letter);
    
        //take this number and use it to sort record into DLL at this index
        sorted = sortRecord(index, temp); 
    }
    // user interface 
    // check comparisons
    if (sorted) {
        // cout << endl;
        cout << "Enter a title of a book to search: ";
        getline(cin, title);
        bookSearch(title);
    }

   return 0;
}

        // cout << temp.getTitle() << " was sorted: " << sorted << endl;   
        // count++; 
        //cout << count << endl;

       /*  cout << "UPDATE LIST::" << endl;
        DLList<Record> list = library.at(index);
        DLListNode<Record>* node = list.first_node();
        while (node != list.after_last_node()){
            cout << node->obj;
            cout << endl;
            node = node->next;
        } */
        
    //cout << "-------------------------------------"<< endl;