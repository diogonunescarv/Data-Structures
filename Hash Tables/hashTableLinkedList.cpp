#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int PRIME_CONSTANT = 7;

class Node {
    friend class LinkedList;
    friend class HashTable;
    private:
        string key;
        char type;
        int value;
        Node* next;
        Node(const string& k = "", const char& t = 'a', const int& v = 0, Node* nxt = NULL):
            key(k), type(t), value(v), next(nxt) { }
};

// A linked list stores all nodes whose keys map to the same hash position.
class LinkedList {
    friend class HashTable;
    private:
        Node* first; // First node in the list
        unsigned short elementCount; // Number of elements in the list
    public:
        
        LinkedList() {
            elementCount = 0;
            first = NULL;
        } // Constructor

        ~LinkedList() {
            Node* aux = first;
            Node* temp;
            
            while (aux != NULL){
                temp = aux;
                aux = aux->next;
                delete temp;
            }
            
            elementCount = 0;
            first = NULL;
        } // Destructor
        
        unsigned short size() { return elementCount; } // Returns size
        
        // Adds a new (key, value) pair to the list
        // Inserts at the beginning to avoid needing a pointer to the end
        void insert(const string& k, const char& t, const int& v) {
            Node* newNode = new Node(k, t, v);
            if (isEmpty()){
                first = newNode;
            } else{
                newNode->next = first;
                first = newNode;
            }
            elementCount++;
        }

        // Removes the node with the given key from the list.
        // If the key does not exist, it returns false.
        bool remove(const string& k) {
            if (isEmpty()) {
                return false; // Empty list, nothing to remove
            }

            Node* current = first;
            Node* previous = NULL;

            // Traverse the list to find the node with the corresponding key
            while (current != NULL && current->key != k) {
                previous = current;
                current = current->next;
            }

            // Check if the key was found
            if (current == NULL) {
                return false; // Key not found
            }

            // Special case: the node to remove is the first
            if (previous == NULL) {
                first = current->next; // Update list start
            } else {
                previous->next = current->next; // Remove node in the middle or end
            }

            delete current; // Free memory
            elementCount--; // Update element count

            return true; // Successful removal
        }
        
        // Checks if the list is empty
        bool isEmpty() {
            return (first == NULL);
        }
        
        // Searches for an element in the list, returns false if not found
        // The value is returned by reference via searchedType and searchedValue
        bool search(const string& k, char& searchedType, int& searchedValue) {
            if (isEmpty()) {
                return false; // Empty list, nothing to search
            }
            Node* aux = first;
            for (int i = 0; i < elementCount; i++){
                if(k == aux->key){
                    searchedType = aux->type;
                    searchedValue = aux->value;
                    return true;
                }
                aux = aux->next;
            }

            return false; 
        }
        
        // Checks if the list already contains an element with a given key
        bool checkOccurrence(const string& k) {
            Node* aux = first;
            for (int i = 0; i < elementCount; i++){
                if(k == aux->key){
                    return true;
                }
                aux = aux->next;
            }
            return false;
        }
        
        // Prints the content of the list (for debugging purposes)
        void print() {
            Node* current = first;
            while (current != NULL) {
                    cout << "[" << current->key << "/"
                         << current->value << "]";
                    current = current->next;
            }
        }
};


class HashTable {
    private:
        LinkedList* table;
        unsigned numberOfPositions;
        unsigned hashFunction(const string& s) {
            return hashFunction(s, numberOfPositions);
        } 
        
        unsigned hashFunction(const string& s, int capacity) {
            unsigned position = 0;
            for (unsigned int i = 0; i < s.size(); ++i)
                position = (PRIME_CONSTANT * position + s[i]) % capacity;
            return position;
        }
    public:
        // Default constructor
        HashTable(unsigned capacity = 100) {
            numberOfPositions = capacity;
            table = new LinkedList[numberOfPositions];
        }

        ~HashTable(){
            delete[] table;
        }
        
        // Inserts a node with the given key and value
        bool insert(const string& k, char& t, const int& v) {
            unsigned position = hashFunction(k);

            table[position].insert(k, t, v);

            cout << "Key '" + k + "' inserted at position " << position << endl;  

            return true;
        }

        // Returns a value associated with a given key
        // If the key does not exist, prints "NOT FOUND!"
        bool value(const string& k, char& searchedType, int& returnValue) {
            unsigned position = hashFunction(k);

            if (!table[position].search(k, searchedType, returnValue)){
                cout << "Element not found!" << endl;
                return false;
            } else {
                return true;
            }
        }

        // Removes a node with a given key from the hash table
        bool remove(const string& k) { 
            unsigned position = hashFunction(k);
            if (!table[position].remove(k)){
                cout << "Element not found!" << endl;
                return false;
            } else {
                return true;
            }
        }

        // Prints the internal content of the hash table (for debugging purposes)
        void print() {
            for (unsigned i = 0; i < numberOfPositions; i++) {
                cout << i << ": ";
                table[i].print();
                cout << endl;
            }
        }
};

int main() {
    int hashTableSize;
    cin >> hashTableSize;
    HashTable hashTable(hashTableSize);
    char command;
    string key;
    char type = 'a';
    int value = -1;    
    do {
        try{
            cin >> command;
            switch (command) {
                case 'i': // insert
                    cin >> key >> type >> value;
                    hashTable.insert(key, type, value);
                    break;
                case 'r': // remove
                    cin >> key;
                    hashTable.remove(key);
                    break;
                case 'l': // lookup
                    cin >> key;
                    if (hashTable.value(key, type, value)){
                        cout << "Type: " << type << " Value: " << value << endl;
                    }
                    break;
                case 'p': // print structure
                    hashTable.print();
                    break;

                case 'f': // finish
                    // checked in do-while
                    break;
                default:
                    cerr << "Invalid command\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (command != 'f'); // finish execution
    hashTable.print();
    cout << endl;
    return 0;
}
