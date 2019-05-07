#include <iostream>
#include <vector>
#include <string>
#include "table.h"
#include "entry.h"

using namespace std;

Table::Table(unsigned int max_entries)
{
    arr = new std::vector<Entry>[max_entries];    
    len = max_entries;
}

Table::Table(unsigned int entries, std::istream& input)
{
    arr = new std::vector<Entry>[entries];
    len = entries;
    Entry e;

    for(int i = 0; i<entries; i++)
    {
        input >> e;
        put(e);
    }
}

void Table::put(unsigned int key, std::string data)
{
    Entry e(key, data);
    
    for( int i=0; i<arr[ key % len ].size(); i++ )
    {
        if( arr[ key % len ].at(i).get_key() == key )
            return;
    }
    arr[ key % len ].push_back( e );
}

void Table::put(Entry e)
{
    arr[ e.get_key() % len ].push_back( e );
}

std::string Table::get(unsigned int key) const
{
    if( arr[ key % len ].size() > 0 )
    {
        for( int i=0; i<arr[ key % len ].size(); i++)
        {
            if( arr[ key % len].at(i).get_key() == key )
                return arr[ key % len].at(i).get_data();
        }
    }
    return "";
}

bool Table::remove(unsigned int key)
{
    if( arr[ key % len ].size() > 0 )
    {
        for( int i=0; i<arr[ key % len ].size(); i++)
        {
            if( arr[ key % len].at(i).get_key() == key )
                arr[ key % len].erase( arr[ key % len].begin()+i );
                return true;
        }
    }
    return false;
}

std::ostream& operator<< (std::ostream& out, const Table& t)
{
    std::vector<Entry> tmp;
    for( int i=0; i<len; i++)
    {
        for( int j=0; j<arr[i].size(); j++)
        {
            tmp.push_back( arr[i].at(j);
        }
    }

    //Next, Mergesort the values
}
