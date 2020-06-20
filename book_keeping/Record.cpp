
// V. Rivera Casanova
// CSCE 221
// Leyk 199

#include "Record.h"

# include <iostream>
# include <fstream>
# include <vector>
# include <string>
using namespace std;

/* input >> 
Arguments 
vector<record>  book_list
ifstream myfile  book.txt
book_list >> myfile
output <<
Arguments
osstream out
record
out << record
*/

ifstream& operator >> (ifstream& ifs, Record& record) {  // O(1)
    // inputs things from txt into vector
    // Record temp >> ifs;
    // bookList.push_back();
    string title, author, isbnNum, year, edition;
    string text;

    getline(ifs, text);
    if (text.empty()) { // should start after the empty line with title 
        getline(ifs, title);
        getline(ifs, author);
        getline(ifs, isbnNum);
        getline(ifs, year);
        getline(ifs, edition);

        record.setTitle(title);
        record.setAuthor(author);
        record.setISBN(isbnNum);
        record.setYear(stoi(year));
        record.setEdition(edition);
    }

    return ifs;
}

ostream& operator << (ostream& os, const Record& r1) { // outputs certain records in stated format
    // O(1)
    os << "Title: " << r1.getTitle() << endl;
    os << "Author: " << r1.getAuthor() << endl;
    os << "ISBN: " << r1.getISBN() << endl;
    os << "Year Published: " << r1.getPubYear() << endl;
    os << "Edition: " << r1.getEdition() << endl;
    return os;
}

bool operator < (const Record& r1, const Record& r2) {
    // compares 2 books based on instructions given
    // O(1)
    if (r1.getTitle() != r2.getTitle()) {
        return false;

    } else if (r1.getAuthor() != r2.getAuthor()) {
        return false;

    } else if (r1.getISBN() != r2.getISBN()) {
        return false;

    } else {
        return true; // if everything is the same then return true
    }
}
