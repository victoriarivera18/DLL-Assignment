// V. Rivera Casanova
// CSCE 221
// Leyk 199

#include "Record.h"

# include <iostream>
# include <sstream>
# include <fstream>
# include <stdexcept>
# include <vector>
using namespace std;

int main() {
    vector<Record> books;
    
    // input stream 
    ifstream ifs("Book.txt");

    // parameters needed

    // loop through file
    // log(n), where n is "n" is the number of lines. 
    int count = 0;
    while (!ifs.eof()) {//while not the end of file 
        Record temp = Record();
        ifs >> temp; //O(n), n is the number of books
        books.push_back(temp);
        count++;
    }
    cout << count << endl;

    // end of file

    // use output operator to output individual records
    // cout << books.at(0);
    for (size_t i = 0; i < books.size(); i++) {  // O(books.size)
        cout << books.at(i);
        cout << endl;
    }

    // test less than operator
    if (books.at(0) < books.at(1)) {
        cout << "Books are the same!" << endl;
    } else {
        cout << "Books are not the same :(" << endl;
    } 

    return 0;   
}
