#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct ProgramAction {
    int id;
    string action;
    int execTime;
    int consumedTime;
};

class Node {
friend class DoublyLinkedList;
private:
    ProgramAction action;
    Node* next;
    Node* prev;
public:
    Node(ProgramAction d);
};

Node::Node(ProgramAction d) {
    action = d;
    next = nullptr;
    prev = nullptr;
}

class DoublyLinkedList {
private:
    Node* first;
    Node* last;
    int size;
    void clear();
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insertLast(ProgramAction action);
    void insertFirst(ProgramAction action);
    void insertAtPosition(int position, ProgramAction action);
    int search(const string& value) const;
    void print() const;
    inline bool empty() const;
    void removeLast();
    void removeFirst();
};

DoublyLinkedList::DoublyLinkedList() {
    size = 0;
    first = nullptr;
    last = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

void DoublyLinkedList::clear() {
    Node* aux = first;
    while (aux != nullptr) {
        Node* temp = aux;
        aux = aux->next;
        delete temp;
    }
    size = 0;
    first = nullptr;
    last = nullptr;
}

void DoublyLinkedList::insertLast(ProgramAction action) {
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

void DoublyLinkedList::insertFirst(ProgramAction action) {
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

void DoublyLinkedList::insertAtPosition(int position, ProgramAction action) {
    Node* newNode = new Node(action);

    if (position >= 0 && position <= size) {
        if (empty() || position == 0) {
            insertFirst(action);
        } else if (position == size) {
            insertLast(action);
        } else {
            Node* aux = first;
            for (int i = 0; i < position - 1; ++i) {
                aux = aux->next;
            }

            newNode->next = aux->next;
            aux->next->prev = newNode;
            aux->next = newNode;
            newNode->prev = aux;
            size++;
        }
    } else {
        cout << "Invalid position!" << endl;
    }
}

int DoublyLinkedList::search(const string& value) const {
    if (empty()) {
        throw runtime_error("The list is empty!");
    }

    Node* aux = first;
    int posAux = 0;

    while (aux != nullptr && aux->action.action != value) {
        aux = aux->next;
        posAux++;
    }

    if (aux == nullptr) {
        cout << "Value not found!" << endl;
        return -1;
    }

    cout << posAux << endl;
    return posAux;
}

void DoublyLinkedList::print() const {
    if (empty()) {
        cout << "The list is empty!" << endl;
        return;
    }

    Node* aux = first;
    while (aux != nullptr) {
        cout << "(" << aux->action.id << ", "
             << aux->action.action << ", "
             << aux->action.execTime << ", "
             << aux->action.consumedTime << ")" << endl;
        aux = aux->next;
    }

    cout << "PRINTING REVERSE" << endl;

    aux = last;
    while (aux != nullptr) {
        cout << "(" << aux->action.id << ", "
             << aux->action.action << ", "
             << aux->action.execTime << ", "
             << aux->action.consumedTime << ")" << endl;
        aux = aux->prev;
    }
}

inline bool DoublyLinkedList::empty() const {
    return first == nullptr;
}

void DoublyLinkedList::removeFirst() {
    if (empty()) {
        cout << "Cannot remove from an empty list!" << endl;
        return;
    }
    Node* aux = first;
    first = first->next;
    if (first != nullptr) {
        first->prev = nullptr;
    } else {
        last = nullptr;
    }
    delete aux;
    size--;
}

void DoublyLinkedList::removeLast() {
    if (empty()) {
        cout << "Cannot remove from an empty list!" << endl;
        return;
    }
    if (first == last) {
        delete first;
        first = nullptr;
        last = nullptr;
    } else {
        Node* aux = last->prev;
        delete last;
        last = aux;
        last->next = nullptr;
    }
    size--;
}

int main() {
    DoublyLinkedList myList;
    ProgramAction info;
    char command;
    int position;
    string action;

    do {
        try {
            cin >> command;
            switch (command) {
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
                    myList.insertAtPosition(position, info);
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
    } while (command != 'f');
    return 0;
}
