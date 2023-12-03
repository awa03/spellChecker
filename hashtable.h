#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef> // fix size_t return type error
#include <iostream> 
#include <stdexcept> // for out_of_range
#include <cstring>  // for memcpy
#include <list> // for list
#include <fstream> // for file I/O
#include <vector> // for vector
#include <algorithm> // for find
#include <string> // for string

using namespace std;
namespace cop4530 {
    template<typename T>
    class HashTable {
    /*
        Public Members
    */

        public:
        // Public Member Functions
        HashTable(size_t size = 101);
        ~HashTable();
        bool contains(const T &x) const;
        bool insert(const T &x);
        bool insert(T &&x);
        bool remove(const T &x);
        void clear();
        bool load(const char *filename);
        void dump();
        void write_to_file(const char *filename);
        int size();

    /*
        Private Members
    */
        private:

        // Private Member Functions
        void makeEmpty();
        void rehash();
        size_t myhash(const T &x) const;

        unsigned long prime_below(long);
        void setPrimes(std::vector<long> &vprimes);

        // used when improper size is given (for example
        // size is 0 or negatiave)
        static const unsigned int default_capacity = 11;
        static const unsigned int max_prime = 1301081;

        // Member variables
        std::vector<std::list<T> > theLists; // vector of lists
        int currentSize;
        int tableSize;
    
        
    }; // End of class HashTable
#include "hashtable.hpp"
} // End of namespace cop4530
#endif
