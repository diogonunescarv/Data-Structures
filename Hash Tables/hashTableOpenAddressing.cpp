#include <iostream>
#include <exception>

using namespace std;

struct Data {
    string subject; 
    string interestedName;
    char type;
    int processNumber;
};

// Overloaded operators for comparison
bool operator==(const Data& d1, const Data& d2) {
    return (d1.interestedName == d2.interestedName);
}

bool operator!=(const Data& d1, const Data& d2) {
    return (d1.interestedName != d2.interestedName);
}

const int PRIME = 13;             // Prime number for hashing
const Data EMPTY = {"", "", '1', -1};  // Sentinel for an empty position
const Data REMOVED = {"", "", '2', -2}; // Sentinel for a removed position
const int INVALID_POSITION = -1;

class HashTable {
private:
    // Calculates the storage position of a key using the hash function
    unsigned calculatePosition(const string& key);

    // Searches for the position of a key in the structure
    int searchKey(const string& key);

    // Array to store the data
    Data* dataArray;
    unsigned capacity;
    unsigned size;

public:
    HashTable(unsigned cap = 50); // Default capacity if not provided
    ~HashTable();

    // Prints all positions of the hash table
    void print();

    // Inserts a new item. Does not allow duplicate keys.
    void insert(const string& subject, const string& interested, const char& type, const int& value);

    // Removes an item associated with the given key
    void remove(const string& key);

    // Returns the value associated with a key
    int search(const string& key);
};

HashTable::HashTable(unsigned cap) {
    capacity = cap;
    dataArray = new Data[cap]; 
    for (unsigned i = 0; i < cap; i++) 
        dataArray[i] = EMPTY;
    size = 0;
}

HashTable::~HashTable() {
    delete[] dataArray;
}

unsigned HashTable::calculatePosition(const string& key) {
    // Hash function: calculates position without considering collisions
    unsigned position = 1;
    for (unsigned i = 0; i < key.size(); i++)
        position = PRIME * position + key[i];
    return position % capacity;    
}

int HashTable::searchKey(const string& key) {
    // Searches for the position of a key. Returns INVALID_POSITION if not found.
    unsigned position = calculatePosition(key);
    unsigned startPosition = position;
    Data currentData;

    do {
        currentData = dataArray[position];
        if (currentData == EMPTY) return INVALID_POSITION; 
        if (currentData.interestedName == key) return position;
        position = (position + 1) % capacity;
    } while (position != startPosition);

    // Key was not found
    return INVALID_POSITION;
}

void HashTable::insert(const string& subject, const string& interested, const char& type, const int& value) {
    if (interested.empty()) 
        throw invalid_argument("Invalid key.");
    if (size == capacity) 
        throw runtime_error("Error: hash table is full!");

    if (searchKey(interested) != INVALID_POSITION)   
        throw runtime_error("Error: duplicate key insertion.");

    unsigned position = calculatePosition(interested);
    while ((dataArray[position] != EMPTY) and (dataArray[position] != REMOVED))
        position = (position + 1) % capacity;

    dataArray[position].subject = subject;
    dataArray[position].interestedName = interested;
    dataArray[position].type = type;
    dataArray[position].processNumber = value;
    size++;
}

void HashTable::print() {
    for (unsigned i = 0; i < capacity; ++i) {
        cout << '[' << i << ":";
        if (dataArray[i] != EMPTY) {
            if (dataArray[i] == REMOVED)
                cout << "REMOVED";
            else
                cout << dataArray[i].interestedName << '/' << dataArray[i].processNumber;
        }
        cout << "] ";
    }
    cout << endl;
}

void HashTable::remove(const string& key) {
    if (size == 0) {
        cout << "Error: hash table is empty!" << endl;
        return;
    }
    
    int position = searchKey(key);
    if (position == INVALID_POSITION) {
        cout << "Error: element does not exist!" << endl;
        return;
    }

    dataArray[position] = REMOVED;
    size--;
}

int HashTable::search(const string& key) {
    if (size == 0) {
        cout << "Error: hash table is empty!" << endl;
        return INVALID_POSITION;
    }
    int position = searchKey(key);
    if (position == INVALID_POSITION) {
        cout << "Error: element does not exist!" << endl;
        return INVALID_POSITION;
    }

    return dataArray[position].processNumber;
}

int main() {
    HashTable table(6);
    char operation;

    string subject, interested;
    char type;
    int value;

    do {
        try {
            cin >> operation;
            switch (operation) {
                case 'i': 
                    cin >> subject >> interested >> type >> value;
                    table.insert(subject, interested, type, value);
                    break;
                case 'r': 
                    cin >> interested;
                    table.remove(interested);
                    break;
                case 'l': 
                    cin >> interested;
                    value = table.search(interested);
                    if (value != INVALID_POSITION)
                        cout << value << endl;
                    break;
                case 'p': 
                    table.print();
                    break;
                case 'f': 
                    break;
                default:
                    cerr << "Invalid operation." << endl;
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    } while (operation != 'f'); 

    table.print();
    return 0;
}
