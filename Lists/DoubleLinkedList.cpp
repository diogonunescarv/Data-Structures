#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct programAction {
    int id;
    string action;
    int execTime;
    int consumedTime;
};

class Node {
friend class doubleList;
private:
    programAction action;
    Node* next;
    Node* prev;
public:
    Node(programAction d);
};

Node::Node(programAction d) {
    action = d;
    next = NULL;
    prev = NULL;
}

class doubleList {
private:
    Node* first;
    Node* last;
    int size;
    void clear();
public:
    doubleList();
    doubleList(const doubleList& aList);
    ~doubleList();
    doubleList& operator=(const doubleList& aList);
    void insertLast(programAction action);
    void insertFirst(programAction action);
    void insertOnPosition(int position, programAction action);
    int search(string value);
    void print();
    inline bool empty();
    void removeLast();
    void removeFirst();
};

doubleList::doubleList() {
    size = 0;
    first = NULL;
    last = NULL;
}

doubleList::~doubleList() {
    clear();
}

void doubleList::clear() {
    Node* aux = first;
    while (aux != NULL) {
        Node* temp = aux;
        aux = aux->next;
        delete temp;
    }
    size = 0;
    first = NULL;
    last = NULL;
}

void doubleList::insertLast(programAction action) {
    Node* newNode = new Node(action);
    if (empty()) {
        first = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
    size++;
}

void doubleList::insertFirst(programAction action) {
    Node* newNode = new Node(action);
    if (empty()) {
        first = newNode;
        last = newNode;
    } else {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }
    size++;
}

void doubleList::insertOnPosition(int position, programAction action) {
    Node* newNode = new Node(action);

    if ((position <= size) && (position >= 0)){
        if (empty()) {
            insertFirst(action);
        } else if (position == 0) {
            insertFirst(action);
        } else if (position == size) {
            insertLast(action);
        } else {
            Node* aux = first;
            int posAux = 0;

            while (posAux != (position - 1)) {
                aux = aux->next;
                posAux++;
            }

            newNode->next = aux->next;
            aux->next->prev = newNode;
            aux->next = newNode;
            newNode->prev = aux;
            size++;
        }
    } else {
        cout << "Non-existent position!" << endl;
    }
}

int doubleList::search(string value) {
    if (empty()) {
        throw runtime_error("Empty List!");
    }

    Node* aux = first;
    int posAux = 0;

    while ((aux != NULL) && (aux->action.action != value)){
        aux = aux->next;
        posAux++;
    }

    if (aux == NULL) {
        cout << "Not found!" << endl;
        return -1;
    }

    cout << posAux << endl;
    return posAux;
}

void doubleList::print() {
    if (empty()) {
        cout << "Empty List!" << endl;
        return;
    }

    Node* aux = first;
    while (aux != NULL) {
        cout << "(" << aux->action.id << ", "
             << aux->action.action << ", "
             << aux->action.execTime << ", "
             << aux->action.consumedTime << ")" << endl;
        aux = aux->next;
    }

    cout << " PRINTING REVERSE " << endl;

    aux = last;
    while (aux != NULL) {
        cout << "(" << aux->action.id << ", "
             << aux->action.action << ", "
             << aux->action.execTime << ", "
             << aux->action.consumedTime << ")" << endl;
        aux = aux->prev;
    }
}

inline bool doubleList::empty() {
    return (first == NULL);
}

void doubleList::removeFirst() {
    if (empty()) {
        cout << "Empty List Removal!" << endl;
        return;
    }
    Node* aux = first;
    first = first->next;
    if (first != NULL) {
        first->prev = NULL;
    } else {
        last = NULL;
    }
    delete aux;
    size--;
}

void doubleList::removeLast() {
    if (empty()) {
        cout << "Empty List Removal!" << endl;
        return;
    }
    if (first == last) {
        delete first;
        first = NULL;
        last = NULL;
    } else {
        Node* atual = first;
        while (atual->next != last) {
            atual = atual->next;
        }
        delete last;
        last = atual;
        last->next = NULL;
    }
    size--;
}

int main() {
    doubleList myList;
    programAction info;
    char comand;
    int position;
    string action;

    do {
        try {
            cin >> comand;
            switch (comand) {
                case 'i':
                    cin >> info.id >> info.action >> info.execTime >> info.consumedTime;
                    myList.insertFirst(info);
                    break;
                case 'h':
                    cin >> info.id >> info.action >> info.execTime >> info.consumedTime;
                    myList.insertLast(info);
                    break;
                case 'm':
                    cin >> position >> info.id >> info.action >> info.execTime >> info.consumedTime;
                    myList.insertOnPosition(position, info);
                    break;
                case 's':
                    cin >> action;
                    myList.search(action);
                    break;
                case 'r':
                    myList.removeFirst();
                    break;
                case 'a':
                    myList.removeLast();
                    break;
                case 'p':
                    myList.print();
                    break;
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comand != 'f');
    return 0;
}
