#include <iostream>
#include <vector>
#include <string>
#include "table.h"
#include "entry.h"

using namespace std;

Table::Table(unsigned int max_entries)
{
    //initializes an empty array of vectors of entries

    arr = new std::vector<Entry>[max_entries];    
    len = max_entries;
}

Table::Table(unsigned int entries, std::istream& input)
{
    //initializes an array of vectors with entries determined by user

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
    //add a new entry onto the table given the key and data

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
    //adds a copy? of entry e onto the table

    unsigned int e_key = e.get_key();

    for( int i=0; i<arr[ e_key % len ].size(); i++ )
    {
        if( arr[ e_key % len ].at(i).get_key() == e_key )
            return;
    }

    arr[ e_key % len ].push_back( e );
}

std::string Table::get(unsigned int key) const
{
    //returns key with fast average-case run-time, if it exists

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
    //removes key with fast average-case run-time, if it exists

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

void merge_sort(std::vector<Entry>& v1)
{
    std::vector<Entry> v2 = v1;
    merge_sort_helper(v2, 0, v2.size(), v1);
}

void merge_sort_helper(std::vector<Entry>& v2, int merge_start, int merge_end, std::vector<Entry>& v1)
{
    //HELPER FOR MERGE_SORT()
    //if the size of the sub-aray is one element long or shorter, return;

    if( merge_end - merge_start < 2 )
    {
        return;
    }

    //calculates the mid-point of this section

    int merge_mid = (merge_start + merge_end)/2;

    merge_sort_helper(v1, merge_start, merge_mid, v2);
    merge_sort_helper(v1, merge_mid,   merge_end, v2);

    //merges everything back together

    int i = merge_start;
    int j = merge_mid;

    for(int k = merge_start; k < merge_end; k++)
    {
        if ( i<merge_mid && ( j>=merge_end || v1.at(i) <= v1.at(j) ) )
        {
            v2.at(k) = v1.at(i);
            i++;        
        }
        else
        {
            v2.at(k) = v1.at(i);
            j++;
        }
    }

}

std::ostream& operator<< (std::ostream& out, const Table& t)
{
    //First, create a vector of entries (not an array of vectors) and add every entry from the table into it

    std::vector<Entry> tmp;
    for( int i=0; i<t.len; i++)
    {
        for( int j=0; j<t.arr[i].size(); j++)
        {
            tmp.push_back( t.arr[i].at(j) );
        }
    }

    //Next, Mergesort the values

    merge_sort(tmp);

    //Then, print everything in the sorted array

    for( int i=0; i<tmp.size(); i++)
    {
        out << tmp.at(i) << endl;
    }

    return out;
}
