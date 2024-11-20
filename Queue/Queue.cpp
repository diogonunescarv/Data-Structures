// Queue (linked) implementation in C++

#include <iostream>
#include <stdexcept>

using namespace std;

const int EMPTYQUEUE = -1;
const int QUEUE_CAPACITY = 6;

struct Data {
  string name;
  string subject;
  char type;
  int nProcess;
};

// Prints information of any Data.
void print_Data(const Data &newData) {
  cout << "Name: " << newData.name << " "
       << "Subject: " << newData.subject << " "
       << "Type: " << newData.type << " "
       << "Process: " << newData.nProcess << endl;
}

class Queue {
private:
  Data *mQueue;
  int firstPosition, lastPosition;

public:
  // Constructs an empty Queue.
  Queue();
  // Destructor that deallocates memory.
  ~Queue();
  // Removes and returns the element at the first position.
  Data Dequeue();
  // Inserts an element into the Queue.
  void Pile(const Data &d);
  // Clears all Datas from the Queue.
  void Clear();
  // Prints the values of the element at the front of the Queue without
  // Dequeueing it.
  inline void FirstOfQueue();
  // Checks if the Queue is empty.
  inline bool Empty();
  // Checks if the Queue is full.
  inline bool Full();
};

Queue::Queue() {
  mQueue = new Data[QUEUE_CAPACITY]; // Allocates the Data array with the maximum
                                     // size of the Queue
  firstPosition = 0;
  lastPosition = EMPTYQUEUE; // Initializes last as -1, indicating an empty Queue
}

Queue::~Queue() {
  delete[] mQueue; // Deallocates the dynamic array in the destructor.
}

Data Queue::Dequeue() {
  if (this->Empty()) {
    throw runtime_error("Error: Empty Queue!");
  }
  Data removedData = mQueue[firstPosition];

  // Advances the index of the first element (with circular behavior).
  if (firstPosition == lastPosition) {
    // If there's only one element, the Queue will be empty.
    firstPosition = 0;
    lastPosition = EMPTYQUEUE;
  } else {
    firstPosition = (firstPosition + 1) % QUEUE_CAPACITY;
  }

  return removedData;
}

void Queue::Pile(const Data &d) {
  if (this->Full()) {
    throw runtime_error("Error: Full Queue!");
  }

  // If the Queue is empty, the first and last must be the same.
  if (lastPosition == EMPTYQUEUE) {
    firstPosition = 0;
    lastPosition = 0;
  } else {
    // Updates the index of the last element (with circular behavior).
    lastPosition = (lastPosition + 1) % QUEUE_CAPACITY;
  }

  mQueue[lastPosition] = d;
}

void Queue::Clear() {
  firstPosition = EMPTYQUEUE;
  lastPosition = EMPTYQUEUE;
}

void Queue::FirstOfQueue() {
  if (this->Empty()) {
    throw runtime_error("Error: Empty Queue!");
  }
  print_Data(mQueue[firstPosition]);
}

bool Queue::Empty() { return lastPosition == EMPTYQUEUE; }

bool Queue::Full() {
  // The Queue is full when the next index of lastPosition would reach firstPosition
  return ((lastPosition + 1) % QUEUE_CAPACITY) == firstPosition &&
         lastPosition != EMPTYQUEUE;
}

int main() {
  Queue Queue;
  Data info;
  char comand;
  do {
    try {
      cin >> comand;
      switch (comand) {
      case 'i': // insert
        cin >> info.name >> info.subject >> info.type >> info.nProcess;
        Queue.Pile(info);
        break;
      case 'r': // remove
        print_Data(Queue.Dequeue());
        break;
      case 'l': // clear
        Queue.Clear();
        break;
      case 's': // spy
        if (!Queue.Empty())
          Queue.FirstOfQueue();
        else
          cout << "Error: Empty Queue!" << endl;
        break;
      case 'f': // finish
        break;
      default:
        cerr << "invalid command\n";
      }
    } catch (runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (comand != 'f'); // finish the execution

  // Print the remaining Datas in the Queue.
  while (!Queue.Empty()) {
    print_Data(Queue.Dequeue());
  }

  cout << endl;
  return 0;
}
