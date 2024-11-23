#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct team {
    string teamName;
    string leader;
    string language; 
    int membersQtt;
};

class node {
friend class List;
private:
    team squad; // could be another type of variable
    node* next;
public:
    // node();
    node(team d);
};

// constructing a team by calling its constructor
node::node(team d) {
    squad = d;
    next = NULL;
}

// Dynamically linked List
class List {
private:
    node* first;
    node* last;
    int size;
    void clear(); // removes all elements from the List
    // reverse print starting from a node -> example of recursion usage
    void reversePrintAux(node* aNode);
public:
    // constructors and destructor
    List();
    List(const List& aList);
    ~List();
    // overload of the assignment operator
    List& operator=(const List& aList);  
    // insertion, removal, and search
    inline void insert(team squad);
    void insertLast(team squad);
    void insertFirst(team squad);
    void insertOnPosition(int position, team squad);
    int search(string value); // returns the position of the node with the value
    // additional methods (printing, empty check)
    void print();
    void reversePrint();
    inline bool empty();
    void removeLast();
    void removeFirst();
};

// constructs a List initially empty
List::List() {
    size = 0;
    first = NULL;
    last = NULL;
}

// copy constructor
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

// destructor of the List (calls auxiliary private function)
List::~List() {
    clear();
}

// removes all elements from the List
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

// overload of the assignment operator
List& List::operator=(const List& aList) {
    // clears the current List
    clear();
    // iterates through the List received as a parameter, copying the data
    node* aux = aList.first;
    
    while (aux != NULL) {
        insertLast(aux->squad);
        aux = aux->next;  
    }
    
    return *this; 
}

// insert at the end of the List
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

// insert at the beginning of the List
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

// insert at a specific position in the List
void List::insertOnPosition(int position, team squad) {
    node* newNode = new node(squad);

    if ((position <= size) && (position >= 0)) {
        if (empty()) {
            insertFirst(squad);
        } else if (position == 0) {
            insertFirst(squad);
        } else if (position == size) {
            insertLast(squad);
        } else {
            node* aux = first;
            int posAux = 0;

            while (posAux != (position - 1)) {
                aux = aux->next;
                posAux++;
            }

            newNode->next = aux->next;
            aux->next = newNode;
            size++;
        }
    } else {
        cout << "Non-existent position!" << endl;
    }
}

// searches the position of a specific element
int List::search(string value) {
    if (empty()) {
        throw runtime_error("Empty List!");
    } 

    node* aux = first;
    int posAux = 0;

    while ((aux != NULL) && (aux->squad.teamName != value)) {
        aux = aux->next;
        posAux++;
    }

    if (aux == NULL) {
        posAux = -1;
    }

    return posAux;
}

// basic method that traverses a List, printing its elements
// could traverse performing another action (e.g., multiplying values)
void List::print() {
    if (empty()) {
        throw runtime_error("Empty List!");
    } 

    node* aux = first;

    while ((aux != NULL)) {        
        cout << "(" + aux->squad.teamName + ", " + aux->squad.leader + ", " + aux->squad.language + ", " << aux->squad.membersQtt << ")" << endl;
        aux = aux->next;
    }
}

// checks if the List is empty
inline bool List::empty() {
    return (first == NULL);
}

// removes the last element from the List
void List::removeLast() {
    if (empty()) {
        cout << "Empty List Removal!" << endl;
        return;
    }
    if (first == last) {
        delete first;
        first = NULL;
        last = NULL;
    } else {
        node* atual = first;
        while (atual->next != last) {
            atual = atual->next;
        }
        delete last;
        last = atual;
        last->next = NULL;
    }
    size--;
}

// removes the first element from the List
void List::removeFirst() {
    if (empty()) {
        cout << "Empty List Removal!" << endl;
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
    char comand;
    int position;
    string teamName;

    do {
        try {
            cin >> comand;
            switch (comand) {
                case 'i': // insert
                    cin >> info.teamName >> info.leader >> info.language >> info.membersQtt;
                    myList.insertFirst(info);
                    break;
                case 'h': // insert
                    cin >> info.teamName >> info.leader >> info.language >> info.membersQtt;
                    myList.insertLast(info);
                    break;             
                case 'm': // insert
                    cin >> position;
                    cin >> info.teamName >> info.leader >> info.language >> info.membersQtt;
                    myList.insertOnPosition(position, info);
                    break;             
                case 's': // search
                    cin >> teamName;
                    if (myList.search(teamName) == -1) {
                        cout << "Not Found!" << endl;
                    } else {
                        cout << myList.search(teamName) << endl;
                    } 
                        
                    break;                    
                case 'r': // remove
                    myList.removeFirst();
                    break;
                case 'a': // remove
                    myList.removeLast();
                    break;                                   
                case 'p': // print
                    myList.print();
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
    } while (comand != 'f'); // end execution
    cout << endl;
    return 0;
}
