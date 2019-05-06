//
//  table.h
//  S19 - Lab04
//
#ifndef table_h
#define table_h

#include "entry.h"
#include <vector>
#include <string>

class Table {

    public:
        Table(unsigned int max_entries = 100);
        Table(unsigned int entries, std::istream& input);
        void put(unsigned int key, std::string data);
        void put(Entry e);
        std::string get(unsigned int key) const;
        bool remove(unsigned int key);
        friend std::ostream& operator<< (std::ostream& out, const Table& t);
    private:
        std::vector<Entry>* arr;
        int len;

};

#endif /* table_h */
