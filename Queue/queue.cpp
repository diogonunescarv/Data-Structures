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

// Prints the details of a Data object.
void print_Data(const Data &newData) {
  cout << "Name: " << newData.name << " "
       << "Subject: " << newData.subject << " "
       << "Type: " << newData.type << " "
       << "Process: " << newData.nProcess << endl;
}

class Queue {
private:
  Data *mQueue; // Dynamic array to hold queue elements
  int firstPosition, lastPosition;

public:
  // Constructs an empty Queue.
  Queue();
  // Destructor that deallocates the memory.
  ~Queue();
  // Removes and returns the element at the front of the Queue.
  Data Dequeue();
  // Inserts an element into the Queue.
  void Enqueue(const Data &d);
  // Clears all Data from the Queue.
  void Clear();
  // Displays the element at the front of the Queue without removing it.
  void FrontOfQueue() const;
  // Checks if the Queue is empty.
  inline bool Empty() const;
  // Checks if the Queue is full.
  inline bool Full() const;
};

Queue::Queue() {
  mQueue = new Data[QUEUE_CAPACITY]; // Allocates memory for the queue.
  firstPosition = 0;
  lastPosition = EMPTYQUEUE; // Initializes lastPosition to -1 to indicate an empty queue.
}

Queue::~Queue() {
  delete[] mQueue; // Deallocates the dynamic array.
}

Data Queue::Dequeue() {
  if (this->Empty()) {
    throw runtime_error("Error: The Queue is empty!");
  }
  Data removedData = mQueue[firstPosition];

  // Advances the front position index with circular behavior.
  if (firstPosition == lastPosition) {
    // If there's only one element, reset the Queue.
    firstPosition = 0;
    lastPosition = EMPTYQUEUE;
  } else {
    firstPosition = (firstPosition + 1) % QUEUE_CAPACITY;
  }

  return removedData;
}

void Queue::Enqueue(const Data &d) {
  if (this->Full()) {
    throw runtime_error("Error: The Queue is full!");
  }

  // If the Queue is empty, reset first and last positions.
  if (lastPosition == EMPTYQUEUE) {
    firstPosition = 0;
    lastPosition = 0;
  } else {
    // Update the last position index with circular behavior.
    lastPosition = (lastPosition + 1) % QUEUE_CAPACITY;
  }

  mQueue[lastPosition] = d;
}

void Queue::Clear() {
  firstPosition = EMPTYQUEUE;
  lastPosition = EMPTYQUEUE;
}

void Queue::FrontOfQueue() const {
  if (this->Empty()) {
    throw runtime_error("Error: The Queue is empty!");
  }
  print_Data(mQueue[firstPosition]);
}

bool Queue::Empty() const { 
  return lastPosition == EMPTYQUEUE; 
}

bool Queue::Full() const {
  // The Queue is full when the next index of lastPosition wraps around to firstPosition.
  return ((lastPosition + 1) % QUEUE_CAPACITY) == firstPosition &&
         lastPosition != EMPTYQUEUE;
}

int main() {
  Queue queue;
  Data info;
  char command;
  do {
    try {
      cin >> command;
      switch (command) {
      case 'i': // Insert
        cin >> info.name >> info.subject >> info.type >> info.nProcess;
        queue.Enqueue(info);
        break;
      case 'r': // Remove
        print_Data(queue.Dequeue());
        break;
      case 'l': // Clear
        queue.Clear();
        break;
      case 's': // Display front element
        if (!queue.Empty())
          queue.FrontOfQueue();
        else
          cout << "Error: The Queue is empty!" << endl;
        break;
      case 'f': // Finish
        break;
      default:
        cerr << "Error: Invalid command!" << endl;
      }
    } catch (const runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (command != 'f'); // Finish execution

  // Print remaining Data in the Queue.
  while (!queue.Empty()) {
    print_Data(queue.Dequeue());
  }

  return 0;
}
