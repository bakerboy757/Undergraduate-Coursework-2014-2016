#include "passserver.h"
#include "hashtable.h"

//: constructor, create a hash table of the specified size.You just need to pass this size parameter
//to the constructor of the HashTable.Therefore, the real hash table size could be different from the 
//parameter size(because prime_below() will be called in the constructor of the HashTable).
PassServer::PassServer(size_t size) {
    ht = new HashTable<string, string>(size);

} 
  //: destructor.You need to decide what you should do based on your design of PassServer
//(how you develop the adaptor class based on the adaptee HashTable).In essence, we do not want to have memory leak.
PassServer::~PassServer() {
    ht->clear();

}
  //: load a password file into the HashTable object.Each line contains a pair of username and encrypted password.
bool PassServer::load(const char *filename) {

    return ht->load(filename);

} 
  //: add a new username and password.The password passed in is in plaintext, it should be encrypted before insertion.

bool PassServer::addUser(std::pair<string, string> & kv) {
    kv.second = encrypt(kv.second);

    return ht->insert(kv);


} 
  //: move version of addUser.

bool PassServer::addUser(std::pair<string, string> && kv) {

    kv.second = encrypt(kv.second);

    return ht->insert(kv);


} 
  //: delete an existing user with username k.

bool PassServer::removeUser(const string & k) {
    return ht->remove(k);



} 
  //: change an existing user's password. Note that both passwords passed in are in plaintext. 
//They should be encrypted before you interact with the hash table. If the user is not in the hash table, return false.
//If p.second does not match the current password, return false. Also return false if the new password and the old password 
//are the same (i.e., we cannot update the password).

bool PassServer::changePassword(pair<string, string> p, const string & newpassword) {
    string tempPass = encrypt(newpassword);
    //newpassword = encrypt(newpassword);
    pair<string, string> tempAccount = p;
    
    if (!ht->match(tempAccount))
        return false;
    if (p.second == tempPass)
        return false;
        
    p.second = tempPass;
    ht->remove(tempAccount.first);
    ht->insert(p);

    return true;


} 
  //: check if a user exists(if user is in the hash table).

bool PassServer::find(const string & user) {

    return ht->contains(user);


} 
  //: show the structure and contents of the HashTable object to the screen.Same format as the dump() 
//function in the HashTable class template.

void PassServer::dump() {

    ht->dump();



} 
  //: return the size of the HashTable(the number of username / password pairs in the table).

size_t PassServer::size() {
    return ht->getSize();
    



} 
  //: save the username and password combination into a file.Same format as the write_to_file() 
//function in the HashTable class template.

bool PassServer::write_to_file(const char *filename) {
    return ht->write_to_file(filename);



} 
  //: encrypt the parameter str and return the encrypted string.

string PassServer::encrypt(const string & str) {

    char salt[] = "$1$########";

    char * password = new char[100];
    strcpy(password, crypt(str.c_str(), salt));
    return password;
    

}

