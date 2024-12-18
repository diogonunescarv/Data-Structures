#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int INVALID = -1;

class Tournament {
private:
  int *heap;
  int size;
  int capacity;
  int dataStart;
  inline int parent(int child);
  inline int left(int parentNode);
  inline int right(int parentNode);
  void organize();
  void compete(int i);
  void checkLargestBase();

public:
  Tournament(int arr[], int sz);
  ~Tournament();
};

// Constructor of the class
Tournament::Tournament(int arr[], int sz) {
  capacity = sz * 2 - 1;
  heap = new int[capacity];

  // Initializing leaf nodes with the values from the input array
  for (int i = 0; i < sz; i++) {
    heap[capacity - sz + i] = arr[i];
  }

  // Filling intermediate positions with invalid values (haven't competed yet)
  for (int i = 0; i < capacity - sz; i++) {
    heap[i] = INVALID;
  }

  size = sz;
  dataStart = capacity - sz;

  organize(); 
}

// Destructor of the class
Tournament::~Tournament() { delete[] heap; }

// Returns the parent node position of a given element
int Tournament::parent(int child) { return (child - 1) / 2; }

// Returns the left child of a given node
int Tournament::left(int parentNode) { return 2 * parentNode + 1; }

// Returns the right child of a given node
int Tournament::right(int parentNode) { return 2 * parentNode + 2; }

// Performs the competition for each winning position in the array and prints the winner
void Tournament::organize() {
  for (int i = dataStart - 1; i >= 0; i--) {
    compete(i); 
  }
  cout << heap[0]
       << endl; 
}

// Conducts the competition between the elements
void Tournament::compete(int i) {
  int lft = left(i);
  int rgt = right(i);

  if (lft < capacity && rgt < capacity) {
    if (heap[lft] != INVALID && heap[rgt] != INVALID) {
      heap[i] = max(heap[lft], heap[rgt]);
    } else if (heap[lft] != INVALID) {
      heap[i] = heap[lft];
    } else if (heap[rgt] != INVALID) {
      heap[i] = heap[rgt];
    }
  }
}

int main() {
  int sz;
  cin >> sz;

  int arr[sz];
  for (int i = 0; i < sz; i++) {
    cin >> arr[i];
  }

  Tournament participants(arr, sz);

  return 0;
}