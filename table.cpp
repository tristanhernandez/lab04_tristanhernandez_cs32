#include <iostream>
#include <vector>
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
    unsigned int in = 0;

    for(int i = 0; i<entries; i++)
    {
        //input >> in;
        
    }
}

void Table::put(unsigned int key, std::string data)
{
    Entry e(key, data);
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
    //int print_count = 0;
    //int last_key = 0;
    //while(print_count < t.len )
    //{
        for(int i = 0; i<t.len; i++)
        {
           // if(print_count==0)
           // {
           //     i=1;
           // }

            for(int j = 0; j<t.arr[i].size(); j++)
            {
                //if ( t.arr[i].at(j).get_key() > last_key )
                //{
                //    last_key = t.arr[i].at(j).get_key();
                //    print_count++;
                    out << t.arr[i].at(j);
                //    break;
                //}

                cout << j;
            }
            cout << i ;

        }
    //}
    return out;
}
