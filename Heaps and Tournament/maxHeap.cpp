#include <iostream>
#include <stdexcept> 
#include <utility>   // for using swap

using namespace std;

struct data {
  string taskName;
  char taskType;
  int energySpent;
  int estimatedTime;
  int priority;
};

// Overloading comparison operators
bool operator>(data d1, data d2) { return d1.energySpent > d2.energySpent; }

bool operator<(data d1, data d2) { return d1.energySpent < d2.energySpent; }

// Overloading output stream to print the structure
ostream &operator<<(ostream &output, const data &d) {
  output << "[" << d.taskName << "/" << d.taskType << "/" << d.energySpent
         << "/" << d.estimatedTime << "/" << d.priority << "]";
  return output;
}

class MaxHeap {
private:
  data *heap;
  int capacity;
  int size;
  inline int parent(int i);
  inline int left(int i);
  inline int right(int i);
  void fixDown(int i);
  void fixUp(int i);

public:
  MaxHeap(int cap);
  ~MaxHeap();
  void print();
  data removeRoot();
  void insert(data d);
};

MaxHeap::MaxHeap(int cap) {
  capacity = cap;
  heap = new data[capacity];
  size = 0;
}

MaxHeap::~MaxHeap() { delete[] heap; }

int MaxHeap::parent(int i) { return (i - 1) / 2; }

int MaxHeap::left(int i) { return (2 * i); }

int MaxHeap::right(int i) { return (2 * i + 1); }

void MaxHeap::fixDown(int i) {
  int lft = left(i);
  int rgt = right(i);
  int largest = i;

  if (lft < size && heap[lft] > heap[i]) {
    largest = lft;
  }

  if (rgt < size && heap[rgt] > heap[largest]) {
    largest = rgt;
  }

  if (largest != i) {
    swap(heap[i], heap[largest]);
    fixDown(largest);
  }
}

void MaxHeap::fixUp(int i) {
  int p = parent(i);
  if (p >= 0 && heap[i] > heap[p]) {
    swap(heap[i], heap[p]);
    fixUp(p);
  }
}

void MaxHeap::print() {
  if (size == 0) {
    cout << "Heap is empty!" << endl;
    return;
  }
  for (int i = 0; i < size; i++) {
    cout << heap[i] << " ";
  }
  cout << endl;
}

data MaxHeap::removeRoot() {
  if (size == 0) {
    throw runtime_error("Error removing root");
  }
  data temp = heap[0];
  swap(heap[0], heap[size - 1]);
  size--;
  fixDown(0);
  return temp;
}

void MaxHeap::insert(data d) {
  if (size == capacity) {
    throw runtime_error("Heap is full");
  }
  heap[size] = d; // Insert at the end
  fixUp(size);
  size++;
}

int main() {
  int capacity;
  data info;
  char command;

  cin >> capacity;
  MaxHeap myHeap(capacity);

  do {
    try {
      cin >> command;
      switch (command) {
      case 'i': // insert
        cin >> info.taskName >> info.taskType >> info.energySpent >>
            info.estimatedTime >> info.priority;
        myHeap.insert(info);
        break;
      case 'r': // remove root
        cout << myHeap.removeRoot().taskName << endl;
        break;
      case 'p': // print heap
        myHeap.print();
        break;
      case 'f': // finish execution
        break;
      default:
        cerr << "Invalid command\n";
      }
    } catch (runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (command != 'f'); // finalize execution

  return 0;
}
