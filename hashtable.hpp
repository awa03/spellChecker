

template<typename T>
cop4530::HashTable<T>::HashTable(size_t size){
  int newSize = prime_below(size);
  theLists.resize(newSize); // Resize the vector to the size of the prime number
  tableSize = newSize; // set tableSize to the newSize
  currentSize = 0; // set currentSize to 0
}

template<typename T>
cop4530::HashTable<T>::~HashTable(){
  currentSize = 0; // set currentSize to 0
}

template<typename T>
bool cop4530::HashTable<T>::contains(const T &x) const {
  auto& whichList = theLists[myhash(x)]; // get the list where x should be
  return find(begin(whichList), end(whichList), x) != end(whichList); // check if x is in the list
}

template<typename T>
bool cop4530::HashTable<T>::insert(const T &x){
  auto& whichList = theLists[myhash(x)]; // get the list where x should be
  auto result = std::find(begin(whichList), end(whichList), x);

  if (result != end(whichList)) { // if x is in the list
      return false;
  }

  whichList.push_back(x); // insert x into the list
  if (++currentSize > tableSize) // if the currentSize is greater than the size of the vector
  {
      rehash(); // rehash
  }
  return true;
}

template<typename T>
bool cop4530::HashTable<T>::insert(T &&x){
    auto& whichList = theLists[myhash(x)]; // get the list where x should be
    auto itr = find(begin(whichList), end(whichList), x);
    if(itr != end(whichList)){ // if x is in the list
        return false;
    }
    whichList.push_back(std::move(x)); // insert x into the list using move
    if (++currentSize > tableSize) // if the currentSize is greater than the size of the vector
    {
        rehash(); // rehash
    }
    return true;
}

template<typename T>
bool cop4530::HashTable<T>::remove(const T &x){
  auto& whichList = theLists[myhash(x)]; // get the list where x should be
  auto itr = find(begin(whichList), end(whichList), x); // get the iterator to x
  if(itr == end(whichList)){ // if x is in the list
    return false;
  }
  whichList.erase(itr); // erase x from the list
  --currentSize; // decrement currentSize
  return true;
}

template<typename T>
void cop4530::HashTable<T>::clear(){
  makeEmpty(); // call makeEmpty
}

template<typename T>
bool cop4530::HashTable<T>::load(const char *filename){
  // load the content of the file with name filename into the hash table. In the file, each line contains a single value to be inserted to the hash table
  ifstream inFile(filename); // open the file
  if(!inFile){ // if the file cannot be opened
    return false;
  }
  string line; // create a string to hold the line
  while(getline(inFile, line)){ // while there are lines to read
    insert(line); // insert the line into the hash table
  }
  inFile.close(); // close the file
  return true;
}



template<typename T>
void cop4530::HashTable<T>::dump(){
  // display all entries in the hash table. Elements in one entry of the hash table (linked list) are separated by the tab character ("\t") (see the provided executable for more detailed on the output format).
  for(int i = 0; i < tableSize; i++){ // for each list in the vector
    cout << i << ": "; // print the index of the list
    for(auto & x : theLists[i]){ // for each element in the list
      cout << x << "\t"; // print the element
    }
    cout << endl; // print a new line
  }
}

template<typename T>
void cop4530::HashTable<T>::write_to_file(const char *filename){
  //     write all elements in the hash table into a file with name filename. Each element occupies one line.
  ofstream outFile(filename); // open the file
  if(!outFile){ // if the file cannot be opened
    return;
  }
  for(int i = 0; i < tableSize; i++){ // for each list in the vector
    for(auto & x : theLists[i]){ // for each element in the list
      outFile << x << endl; // write the element to the file
    }
  }
  outFile.close(); // close the file
}

template<typename T>
int cop4530::HashTable<T>::size(){
  // return the number of elements in the hash table
  return currentSize;
}


template<typename T>
void cop4530::HashTable<T>::makeEmpty(){
  for(auto & thisList : theLists){ // for each list in the vector
    thisList.clear(); // clear the list
  }
  currentSize = 0; // set currentSize to 0
}

template<typename T>
void cop4530::HashTable<T>::rehash(){
  vector<list<T> > oldLists = theLists; // create a copy of the vector

  long newSize = prime_below(1 + tableSize);
  tableSize = newSize; // set tableSize to the newSize
  theLists.resize(newSize); // resize the vector to the next prime number
  for (auto &thisList : oldLists) { // for each list in the old vector
      for (auto &x : thisList) { // for each element in the list
          insert(std::move(x)); // insert the element into the new vector
      }
}
}

template<typename T>
size_t cop4530::HashTable<T>::myhash(const T &x) const{
  static hash<T> hashObj; // create a hash object
  return (hashObj(x) % tableSize); // return the hash value of x
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long cop4530::HashTable<T>::prime_below (long n)
{
  if (n > max_prime)
    {
      cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  vector <long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void cop4530::HashTable<T>::setPrimes(vector<long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

