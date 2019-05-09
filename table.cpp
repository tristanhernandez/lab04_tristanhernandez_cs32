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
        {
            arr[ key % len ].at(i).set_data( e.get_data() );
            return;
        }
    }
    arr[ key % len ].push_back( e );
}

void Table::put(Entry e)
{
    //adds a copy of entry e onto the table
    
    put(e.get_key(), e.get_data());
}

std::string Table::get(unsigned int key) const
{
    //returns key with fast average-case run-time, if it exists

    //if( arr[ key % len ].size() > 0 )
    //{
        for( int i=0; i<arr[ key % len ].size(); i++)
        {
            if( arr[ key % len ].at(i).get_key() == key )
                return arr[ key % len].at(i).get_data();
        }
    //}
    return "";
}

bool Table::remove(unsigned int key)
{
    //removes key with fast average-case run-time, if it exists
    if( len == 0 )
        return false;

    if( arr[ key % len ].size() > 0 )
    {
        for( int i=0; i<arr[ key % len ].size(); i++)
        {
            if( arr[ key % len ].at(i).get_key() == key )
            {
                arr[ key % len ].erase( arr[ key % len].begin()+i );
                return true;
            }
        }
    }
    return false;
}



void merge_sort(Entry *e, size_t size)
{
    size_t left_size;
    size_t right_size;

    if (size > 1){
        left_size = size/2;
        right_size = size - left_size;

        merge_sort(e, left_size);

        merge_sort( (e+left_size), right_size);
        
        merge(e, left_size, right_size);
    }
}

void merge(Entry *e, size_t left_size, size_t right_size)
{
    //HELPER FOR MERGE_SORT()

    Entry *tmp;
    size_t copied = 0;          //total elements copied to tmp
    size_t left_copied = 0;     //copied elements from left side of array
    size_t right_copied = 0;    //copied elements from right...

    tmp = new Entry[left_size + right_size];

    while( (left_copied<left_size) &&
           (right_copied<right_size) )
    {
        if( e[left_copied].get_key() < ( (e+left_size)[right_copied].get_key() ) )
        {
            tmp[copied++] = e[left_copied++];
        }
        else
        {
            tmp[copied++] = (e+left_size)[right_copied++];
        }
    }

    while(left_copied < left_size)
    {
        tmp[copied++] = e[left_copied++];
    }

    while(right_copied < right_size)
    {
        tmp[copied++] = (e+left_size)[right_copied++];
    }
    
    for (int i = 0; i<left_size+right_size; i++)
    {
        e[i] = tmp[i];
    }

    delete [] tmp;
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

    int tmp_size = tmp.size();
    
    if(tmp_size == 0)
        return out;

    Entry *tmp_arr = new Entry[ tmp_size ];

    for( int i=0; i<t.len; i++)
    {
        tmp_arr[i] = tmp.at(i);
    }

    //Next, Mergesort the values

    merge_sort(tmp_arr, tmp_size);

    //Then, print everything in the sorted array

    for( int i=0; i<tmp_size; i++)
    {
        out << tmp_arr[i] << endl;
    }

    delete [] tmp_arr;

    return out;
}
