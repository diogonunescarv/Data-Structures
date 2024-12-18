#include <iostream>
#include <stdexcept>

using namespace std;

struct Data {
  string name;
  char type;
  int value;
};

// Prints the information of a given Data.
void print_Data(const Data &newData) {
  cout << "Name: " << newData.name << " | Type: " << newData.type
       << " | Value: " << newData.value << endl;
}

class Node {
  friend class Stack;

private:
  Data mData; // Stores the data for the node.
  Node *mNext; // Pointer to the next node.

public:
  Node(Data v) {
    mData = v;
    mNext = nullptr;
  }
};

class Stack {
public:
  // Constructs an empty stack.
  Stack();
  // Destructor that deallocates memory.
  ~Stack();
  // Removes and returns the data at the top of the stack.
  // Throws an error if the stack is empty.
  Data Unstack();
  // Inserts a new data element onto the stack.
  void Pile(const Data &d);
  // Clears all elements from the stack.
  void Clear();
  // Displays the data at the top of the stack without removing it.
  void Top();
  // Checks if the stack is empty.
  bool Empty();

private:
  Node *mTop; // Pointer to the top node of the stack.
};

Stack::Stack() { mTop = nullptr; }

Stack::~Stack() { Clear(); }

Data Stack::Unstack() {
  if (this->Empty())
    throw runtime_error("Error: Stack is empty!");

  Data topData = mTop->mData; // Save data from the top node.
  Node *temp = mTop;          // Temporary pointer to the current top node.
  mTop = mTop->mNext;         // Move the top pointer to the next node.
  delete temp;                // Free memory of the removed node.

  return topData;
}

void Stack::Pile(const Data &d) {
  Node *newNode = new Node(d);
  newNode->mNext = mTop; // Link the new node to the current top.
  mTop = newNode;        // Update the top pointer.
}

void Stack::Clear() {
  while (!Empty()) {
    Unstack();
  }
}

void Stack::Top() {
  if (this->Empty())
    throw runtime_error("Error: Stack is empty!");

  cout << "Top -> Name: " << mTop->mData.name
       << " | Type: " << mTop->mData.type
       << " | Value: " << mTop->mData.value << endl;
}

bool Stack::Empty() {
  return mTop == nullptr;
}

int main() {
  Stack stack;
  Data info;
  char command;

  do {
    try {
      cin >> command;
      switch (command) {
      case 'i': // Insert a new element
        cin >> info.name >> info.type >> info.value;
        stack.Pile(info);
        break;
      case 'r': // Remove the top element
        print_Data(stack.Unstack());
        break;
      case 'l': // Clear all elements
        stack.Clear();
        break;
      case 's': // View the top element
        stack.Top();
        break;
      case 'f': // Finish the program
        break;
      default:
        cerr << "Invalid command\n";
      }
    } catch (const runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (command != 'f'); // Exit condition

  // Print remaining elements in the stack.
  while (!stack.Empty()) {
    print_Data(stack.Unstack());
  }

  cout << endl;
  return 0;
}
