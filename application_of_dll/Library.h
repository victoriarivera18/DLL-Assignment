#ifndef LIBRARY_H
#define LIBRARY_H

# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <string.h>
using namespace std;

vector<DLList<Record>> library;

bool sortRecord(int index, Record& book){
    bool inserted = false;
    DLList<Record>* tempList = &(library.at(index)); // get the dll at index
    DLListNode<Record>* node;
    if (tempList->is_empty()) {
        //cout << "hello"<< endl;
        tempList->insert_first(book);
        //cout << tempList->first().getTitle() << endl;
        inserted = true;
        //cout << "record inserted first " <<  index << endl;
    }

    node = tempList->first_node();

    //cout << strcmp(node->obj.getTitle().c_str(), book.getTitle().c_str()) << " ";
    //cout << strcmp(node->obj.getAuthor().c_str(), book.getAuthor().c_str()) << " ";
    //cout << strcmp(node->obj.getISBN().c_str(), book.getISBN().c_str()) << " " << endl;
    if (node->obj > book){
        //cout << "first" << endl;
        //cout << node->obj.getTitle().c_str()<< "--" << book.getTitle().c_str() << endl;
        //cout << node->obj.getAuthor().c_str()<< "--" << book.getAuthor().c_str() << endl;
        //cout << node->obj.getISBN().c_str()<< "--" << book.getISBN().c_str() << endl;
        tempList->insert_before((*node), book);
        //cout << book.getTitle() << endl;
        inserted = true;
    }else{
        //cout << "testing"<< endl;

        node = tempList->first_node();
        if (node->obj == book) {
            //cout << "record already exists" << endl; // if records are the same do not enter into system
            inserted = true;
        }

        while(node->next != tempList->after_last_node() && !inserted){   
            cout << endl;
                
                if (node->obj == book){ //overloaded operator
                    //cout << "record already exists" << endl; // if records are the same do not enter into system
                    inserted = true;

                } else if (node->obj > book) {
                    tempList->insert_before((*node), book);
                    //cout << node->obj.getTitle() << endl;
                   // cout << " node inserted before" << endl;
                    inserted = true;

                } else {
                    //cout << "next node ";
                    node = node->next;
                }
        }
    }
        if (!inserted && (node->obj > book)) {
            tempList->insert_before((*node), book); 
            //cout << " record inserted before last: ";
            //cout << tempList->last().getTitle() << endl;
           inserted = true;

        } else if (!inserted && !(node->obj == book)){
            tempList->insert_last(book); 
            //cout << tempList->last().getTitle() << endl;
            //cout << " record last" << endl;
           inserted = true;

        } else {
            //cout << "record exists";
            inserted = true;
        }

        /*DLList<Record> list = library.at(index);
        DLListNode<Record>* nodet = list.first_node();
        while (nodet != list.after_last_node()){
        cout << nodet->obj;
        cout << endl;
        nodet = nodet->next;
    }*/
        //cout << list.last().getTitle();
        //cout << "this is the last";
        return inserted;
}


void enterNewBook(string name, DLList<Record>& list) {
    string author;
    string isbn;
    string edition;
    string year;

    cout << "Enter the author of the book: ";
    getline(cin ,author);
    cout << "Enter the ISBN number of the book: ";
    getline(cin, isbn);
    cout << "Enter the publishing year of the book: ";
    getline(cin, year);
    cout << "Enter the edition of the book: ";
    getline(cin, edition);

    int yearInt = stoi(year);
    int start = -65;
    int index;
    char letter;
    letter = name.at(0);
    index = start + int(toupper(letter));

    Record* newEntry = new Record(name, author, isbn, yearInt, edition);
    if (sortRecord(index, (*newEntry))) {
        cout << "Book entered into library database!" << endl;
        DLList<Record> list = library.at(index);
        DLListNode<Record>* node = list.first_node();
        while (node != list.after_last_node()){
            cout << node->obj;
            cout << endl;
            node = node->next;
        }
    } else {
        cout << "Could not enter book :(" << endl;
    }

}

void chooseOne(int startingIndex, int numbooks, DLList<Record>& list) {
    //check author name also
    //cout << "Printing list  of books: " << endl;
    DLListNode<Record>* node = list.first_node();
    int traversal = 0;
    int chosen;
    int ind = numbooks;
    int count2 = 1;
    bool printed = false;
    //cout << "count: " << count << "startingIndex: " << startingIndex << "count2: " << count2;
    while (node != list.after_last_node()){ 
        if (numbooks > 0 && traversal >= startingIndex){
            cout << node->obj;
            cout << endl;
            numbooks--;
        } 
        traversal++;
        node = node->next;
    }
    //cout << "count: " << count << "startingIndex: " << startingIndex << "count2: " << count2;

    cout << "Enter which version of the book you want (1, 2, ...): ";
    cin >> chosen;
    while (chosen > ind || chosen < 1) { // O(n)
        cout << "Number entered is invalid!" << endl;
        cout << "Enter which version of the book you want (1, 2, ...): ";
        cin >> chosen;
    }

    traversal = 0;
    node = list.first_node();
    //cout << "count: " << count << "startingIndex: " << startingIndex << "count2: " << count2;
    while (node != list.after_last_node() || printed == false){ 

        if (traversal >= startingIndex){
            if (count2 == chosen){
                cout << node->obj;
                cout << endl;
                printed = true;
            }
            count2++;
        } 
        traversal++;
        node = node->next;
    }

}


void bookSearch(string name){
    int start = -65;
    int books = 0;
    // int startIndex = 0;
    int index = 0;
    int count = 0;
    char firstLetter = toupper(name.at(0));
    index = start + int(firstLetter);
    cout << "Entering library database "<< index << endl;
    Record temp;
    Record found_book;
    //bool bookFound = false;
    DLList<Record>* tempList = &(library.at(index));

    //DLList<Record> list = library.at(7);
    DLListNode<Record>* node = tempList->first_node();
    while (node != tempList->after_last_node()){
        //cout << node->obj;
        cout << endl;
        temp = node->obj;
        //cout << node->obj;
        if(node->obj.getTitle() == name) {
            // count++;
            //cout << node->obj;
            books++; // indicates how many entries found
            // bookFound = true;
            found_book = temp;
            // cout << books << endl;
        }
        node = node->next;
        if (books < 1) {
            count++;
        }
    }

    if (books == 1) {
        cout << "Book found!" << endl;
        cout << found_book;
    } else if (books > 1) {
        cout << "Multiple entries with same name found." << endl;
        // cout << count << " " << books;
        chooseOne(count, books, (*tempList));
    } else {
        cout << "No books of that title found! Enter new book into library database:"<< endl;
        cout << endl;
        enterNewBook(name, (*tempList));
    }
}
#endif
// searching and sorting 