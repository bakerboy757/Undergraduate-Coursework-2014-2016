#include "hashtable.h"
#include "passserver.h"
using namespace std;
using namespace cop4530;
void Menu();

int main() {
    char userChoice;
    string userFilename = "";
    const char * filename = "";
    size_t userCapacity;
    cout << "Enter preferred hash table capacity: ";
    cin >> userCapacity;
    //build hash table
    //cout prime below
    PassServer ps(userCapacity);
    pair<string, string> up;
    string username;
    string password;
    

    do {
        Menu();
        cin >> userChoice;
        switch (userChoice) {
        case 'l':
            cout << "Enter password file name to load from: ";
            cin >> userFilename;
            filename = userFilename.c_str();
            ps.load(filename);
            break;
        case 'a':
            cout << "Enter username: ";
            cin >> up.first;
            cout << "Enter password: ";
            cin >> up.second;
            ps.addUser(up);
            cout << "User " << up.first << " added" << endl;
            break;
        case 'r':
            cout << "Enter username: ";
            cin >> username;
            if (ps.removeUser(username))
                cout << "User " << username << " deleted" << endl;
            else
                cout << "*****Error: User not found.  Could not delete user" << endl;
            break;
        case 'c':
            cout << "Enter username: ";
            cin >> up.first;
            cout << "Enter password: ";
            cin >> up.second;
            cout << "\nEnter new password: ";
            cin >> password;
            if (ps.changePassword(up, password))
                cout << "Pass word changed for user " << username << endl;
            else
                cout << "*****Error: Could not change user password" << endl;
            break;
        case 'f':
            cout << "Enter username: ";
            cin >> username;
            if(ps.find(username))
                cout << "User '" << username << "' found." << endl;
            else 
                cout << "User '" << username << "' not found." << endl;
            break;
        case 'd':
            ps.dump();
            break;
        case 's':
            cout << "Size of hashtable: ";
            cout << ps.size();
            break;
        case 'w':
            cout << "Enter password file name to write to: ";
            cin >> userFilename;
            filename = userFilename.c_str();
            ps.write_to_file(filename);
            break;
        case 'x':
            return(EXIT_SUCCESS);
        default:
            cout << "*****Error: Invalid entry. Try again.";
        
        
        
        }
    } while (userChoice != 'x');
    return 0;

}
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
