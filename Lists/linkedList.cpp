#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// Struct representing a team
struct team {
    string teamName;
    string leader;
    string language; 
    int membersCount; // Renamed for clarity
};

// Node class for the linked list
class node {
    friend class List;
private:
    team squad; // Holds the team information
    node* next;
public:
    node(team d);
};

// Node constructor
node::node(team d) {
    squad = d;
    next = NULL;
}

// Dynamically linked list
class List {
private:
    node* first;
    node* last;
    int size;
    void clear(); // Removes all elements from the List
    void reversePrintAux(node* aNode); // Auxiliary function for reverse print
public:
    List(); // Default constructor
    List(const List& aList); // Copy constructor
    ~List(); // Destructor

    List& operator=(const List& aList); // Assignment operator overload

    // Insertion methods
    inline void insert(team squad);
    void insertLast(team squad);
    void insertFirst(team squad);
    void insertOnPosition(int position, team squad);

    // Search and utility methods
    int search(string value); // Returns the position of the node with the value
    void print(); // Prints all elements of the List
    void reversePrint(); // Prints the List in reverse order
    inline bool empty(); // Checks if the List is empty
    void removeLast(); // Removes the last node
    void removeFirst(); // Removes the first node
};

// Default constructor: Initializes an empty List
List::List() {
    size = 0;
    first = NULL;
    last = NULL;
}

// Copy constructor: Copies another List
List::List(const List& aList) {
    size = 0;
    first = NULL;
    last = NULL;
    
    node* aux = aList.first;
    while (aux != NULL) {
        insertLast(aux->squad);
        aux = aux->next;
    }
}

// Destructor: Clears the List
List::~List() {
    clear();
}

// Removes all nodes from the List
void List::clear() {
    node* aux = first;
    node* temp;
    
    while (aux != NULL) {
        temp = aux;
        aux = aux->next;
        delete temp;
    }
    
    size = 0;
    first = NULL;
    last = NULL;
}

// Overload of the assignment operator
List& List::operator=(const List& aList) {
    clear();
    node* aux = aList.first;
    
    while (aux != NULL) {
        insertLast(aux->squad);
        aux = aux->next;  
    }
    return *this; 
}

// Inserts a node at the end of the List
void List::insertLast(team squad) {
    node* newNode = new node(squad);
    if (empty()) {
        first = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        last = newNode;
    }
    size++;
}

// Inserts a node at the beginning of the List
void List::insertFirst(team squad) {
    node* newNode = new node(squad);
    if (empty()) {
        first = newNode;
        last = newNode;
    } else {
        newNode->next = first;
        first = newNode;
    }
    size++;
}

// Inserts a node at a specific position in the List
void List::insertOnPosition(int position, team squad) {
    node* newNode = new node(squad);

    if (position >= 0 && position <= size) {
        if (empty() || position == 0) {
            insertFirst(squad);
        } else if (position == size) {
            insertLast(squad);
        } else {
            node* aux = first;
            int currentPos = 0;

            while (currentPos != position - 1) {
                aux = aux->next;
                currentPos++;
            }

            newNode->next = aux->next;
            aux->next = newNode;
            size++;
        }
    } else {
        cout << "Invalid position!" << endl;
    }
}

// Searches for a node by team name and returns its position
int List::search(string value) {
    if (empty()) {
        throw runtime_error("The List is empty!");
    } 

    node* aux = first;
    int posAux = 0;

    while (aux != NULL && aux->squad.teamName != value) {
        aux = aux->next;
        posAux++;
    }

    return (aux == NULL) ? -1 : posAux;
}

// Prints all nodes in the List
void List::print() {
    if (empty()) {
        throw runtime_error("The List is empty!");
    } 

    node* aux = first;

    while (aux != NULL) {        
        cout << "(" << aux->squad.teamName << ", " 
             << aux->squad.leader << ", " 
             << aux->squad.language << ", " 
             << aux->squad.membersCount << ")" << endl;
        aux = aux->next;
    }
}

// Checks if the List is empty
inline bool List::empty() {
    return (first == NULL);
}

// Removes the last node from the List
void List::removeLast() {
    if (empty()) {
        cout << "Cannot remove from an empty List!" << endl;
        return;
    }
    if (first == last) {
        delete first;
        first = NULL;
        last = NULL;
    } else {
        node* current = first;
        while (current->next != last) {
            current = current->next;
        }
        delete last;
        last = current;
        last->next = NULL;
    }
    size--;
}

// Removes the first node from the List
void List::removeFirst() {
    if (empty()) {
        cout << "Cannot remove from an empty List!" << endl;
        return;
    }
    node* aux = first;
    first = first->next;
    delete aux;
    if (first == NULL) {
        last = NULL;
    }
    size--;
}

int main() {
    List myList;
    team info;
    char command;
    int position;
    string teamName;

    do {
        try {
            cin >> command;
            switch (command) {
                case 'i': // Insert at the beginning
                    cin >> info.teamName >> info.leader >> info.language >> info.membersCount;
                    myList.insertFirst(info);
                    break;
                case 'h': // Insert at the end
                    cin >> info.teamName >> info.leader >> info.language >> info.membersCount;
                    myList.insertLast(info);
                    break;             
                case 'm': // Insert at a specific position
                    cin >> position;
                    cin >> info.teamName >> info.leader >> info.language >> info.membersCount;
                    myList.insertOnPosition(position, info);
                    break;             
                case 's': // Search by team name
                    cin >> teamName;
                    if (myList.search(teamName) == -1) {
                        cout << "Not Found!" << endl;
                    } else {
                        cout << myList.search(teamName) << endl;
                    } 
                    break;                    
                case 'r': // Remove first
                    myList.removeFirst();
                    break;
                case 'a': // Remove last
                    myList.removeLast();
                    break;                                   
                case 'p': // Print List
                    myList.print();
                    break;
                case 'f': // Finish execution
                    break;
                default:
                    cerr << "Invalid command!" << endl;
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (command != 'f');

    return 0;
}
