#include "hashtable.h"

//constructor.Create a hash table, where the size of the vector is set to prime_below(size) 
//(where size is default  to 101), where prime_below() is a private member function of the HashTable and provided to you.
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size = 101) {
    v.resize(prime_below(size));
    cout << prime_below(size);

}
//destructor.Delete all elements in hash table.
template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    makeEmpty();


}
//: check if key k is in the hash table.
template<typename K, typename V>
bool HashTable<K, V>::contains(const K & k) {
    for (const auto& itrList : v)
        for (const auto& itrPair : itrList)
            if (itrPair.first == k)
                return true;
    return false;


}
//: check if key - value pair is in the hash table.
template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
    auto temp = kv.first;
    auto & whichList = v[myhash(temp)];
    return (find(begin(whichList), end(whichList), kv) != end(whichList));
    

}
//: add  the key - value pair kv into the hash table.Don't add if kv is already in the hash table. 
//If the key is the hash table but with a different value, the value should be updated to the new one with kv. 
//Return true if kv is inserted or the value is updated; return false otherwise (i.e., if kv is in the hash table).
template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
    auto & whichList = v[myhash(kv.first)];
    if (find(begin(whichList), end(whichList), kv) != end(whichList))
        return false;
    whichList.push_back(kv);
    if (++size > v.size())
        rehash();
    return true;



}
//: move version of insert.
template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {
    auto & whichList = v[myhash(kv.first)];
    if (find(begin(whichList), end(whichList), kv) != end(whichList))
        return false;
    whichList.push_back(std::move(kv));
    if (++size > v.size())
        rehash();
    return true;


}
//: delete the key k and the corresponding value if it is in the hash table.
//Return true if k is deleted, return false otherwise(i.e., if key k is not in the hash table).
template<typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {

    for (auto & itr : v[myhash(k)]) {
        if (itr.first == k) {
            v[myhash(k)].remove(itr);
            --size;
            return true;
        }		
    }
    return false;
    
}
//: delete all elements in the hash table
template<typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();


}
//: load the content of the file with name filename into the hash table.
//In the file, each line contains a single pair of key and value, separated by a white space.
template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    ifstream file;
    bool flag;
    file.open(filename);
    pair<string, string> kv;
    while (!file.eof()) {
        file >> kv.first >> kv.second;
        flag = insert(kv);

    }

    file.close();
    return flag;


}
//: display all entries in the hash table.If an entry contains multiple key - value pairs, 
//separate them by a semicolon character(:) (see the provided executable for the exact output format).
template<typename K, typename V>
void HashTable<K, V>::dump() {
    int count = 0, pCount = 0;

    for (const auto& itrList : v) {
        cout << "v[" << count << "]: ";
        count++;
        for (const auto & itrPair : itrList) {
            if (pCount != 0)
                cout << ":";
            cout << itrPair.first << " " << itrPair.second;
            pCount++;
        }
        pCount = 0;
        cout << endl;
    }

}
//: write all elements in the hash table into a file with name filename.
//Similar to the file format in the load function, each line contains a pair of key - value pair, separated by a white space.
template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {

    ofstream file;
    file.open(filename);
    if (!file.is_open())
        return false;
    for (const auto& itrList : v)
        for (const auto & itrPair : itrList)
            file << itrPair.first << " " << itrPair.second << "\n";

    file.close();

    return true;

}
//private

//: delete all elements in the hash table.The public interface clear() will call this function.
template<typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    v.erase(v.begin(), v.end());

}
//: Rehash function.Called when the number of elements in the hash table is greater than the size of the vector.
template<typename K, typename V>
void HashTable<K, V>::rehash() {
    auto oldList = v;
    v.resize(prime_below(2 * v.size()));
    for (auto & thisList : v)
        thisList.clear();
    size = 0;
    for (auto & thisList : oldList)
        for (auto & x : thisList)
            insert(std::move(x));

}
template<typename K, typename V>
size_t HashTable<K, V>::getSize() {
    return size;

}
//: return the index of the vector entry where k should be stored.
template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const{
    return k.size() % v.size();



    //size_t i;
    //long unsigned int bigval = k[0];

    //for (i = 1; i < k.size(); ++i)
    //	bigval = ((bigval & 65535) * 18000) // low16 * magic_number 
    //	+ (bigval >> 16) // high16 
    //	+ k[i];

    //bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    //// bigval = low16 * magic_number + high16 
    //return bigval & 65535; // return low16 



}
//: two helpful functions to determine the proper prime numbers used in setting up the vector size.
//Whenever you need to set hash table to a new size "sz", call prime_below(sz) to determine the new proper 
//underlying vector size.These two functions have been provided in HashTable.h and HashTable.hpp.

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
        std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
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
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
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

