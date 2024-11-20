// Stack (linked) implementation in C++

#include <iostream>
#include <stdexcept>

using namespace std;

struct Data {
  string name;
  char type;
  int value;
};

// Prints the information of a given Data
void print_Data(const Data &newData) {
  cout << "name: " << newData.name << " type: " << newData.type
       << " value: " << newData.value << endl;
}

class Node {
  friend class Stack;

private:
  Data mData; // Could be another type of variable
  Node *mNext;

public:
  Node(Data v) {
    mData = v;
    mNext = NULL;
  }
};

class Stack {
public:
  // Constructs an empty Stack.
  Stack();
  // Destructor that deallocates memory.
  ~Stack();
  // Removes and returns the value at the top of the Stack.
  // Displays an error message if it's not possible to unstack.
  Data Unstack(); // Returns the top of the Stack.
  // Inserts a value into the Stack.
  void Pile(const Data &d);
  // Clears all elements from the Stack.
  void Clear();
  // Prints the value at the top of the Stack without unstacking it.
  inline void Top();
  // Checks if the Stack is empty.
  inline bool Empty();

private:
  Node *PilemPtTop;
};

Stack::Stack() { PilemPtTop = nullptr; }

Stack::~Stack() { Clear(); }

Data Stack::Unstack() {
  if (this->Empty())
    throw runtime_error("Error: Empty Stack!");
  Data auxData = PilemPtTop->mData;
  Node *aux = PilemPtTop;
  PilemPtTop = PilemPtTop->mNext;
  delete aux;
  return auxData;
}

void Stack::Pile(const Data &d) {
  Node *newNode = new Node(d);
  newNode->mNext = PilemPtTop;
  PilemPtTop = newNode;
}

void Stack::Clear() {
  while (!Empty()) {
    Unstack();
  }
}

void Stack::Top() {
  if (this->Empty())
    throw runtime_error("Error: Empty Stack!");
  cout << "name: " << PilemPtTop->mData.name << " type: " << PilemPtTop->mData.type
       << " value: " << PilemPtTop->mData.value << endl;
}

bool Stack::Empty() {
  return PilemPtTop == nullptr;
}

int main() {
  Stack stack;
  Data info;
  char command;

  do {
    try {
      cin >> command;
      switch (command) {
      case 'i': // insert
        cin >> info.name >> info.type >> info.value;
        stack.Pile(info);
        break;
      case 'r': // remove
        print_Data(stack.Unstack());
        break;
      case 'l': // clear all
        stack.Clear();
        break;
      case 's': // spy (view top element)
        stack.Top();
        break;
      case 'f': // finish
        // Checked in the do-while loop
        break;
      default:
        cerr << "invalid command\n";
      }
    } catch (runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (command != 'f'); // finish execution

  while (!stack.Empty()) {
    print_Data(stack.Unstack());
  }

  cout << endl;

  return 0;
}
