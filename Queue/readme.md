# Queue Implementation in C++

## What is a Queue?

A **queue** is a data structure that follows the **First In, First Out (FIFO)** principle. This means that the first element added to the queue will be the first one to be removed. It is similar to a real-life queue, like a line at a ticket counter.

### Key Operations:
1. **Pile**: Adds an element to the back of the queue.
2. **Dequeue**: Removes and returns the element at the front of the queue.
3. **Peek** (or "FirstOfQueue" in this implementation): Views the element at the front of the queue without removing it.
4. **Empty**: Checks if the queue is empty.
5. **Full**: Checks if the queue is full (if the queue has a fixed size).

---

## Implementation Overview

This project demonstrates a **circular queue** implementation in C++ using a fixed-size array. A circular queue allows the array to be reused by wrapping around when the end of the array is reached.

### Features:
- Fixed size queue with a maximum capacity of 6.
- Circular behavior for efficient use of memory.
- Clear function to reset the queue.
- Exception handling for cases like Pileing into a full queue or dequeuing from an empty queue.

### Key Components:
1. **`Data` Struct**:
   - Holds the information for each item in the queue.
   - Includes fields for `name`, `subject`, `type`, and `nProcess`.

2. **`Queue` Class**:
   - Encapsulates the queue operations.
   - Uses two pointers:
     - `firstPosition`: Tracks the front of the queue.
     - `lastPosition`: Tracks the back of the queue.
   - Implements circular indexing to manage the fixed-size array efficiently.

3. **Queue Operations**:
   - **Pile**: Adds a new `Data` element to the back of the queue.
   - **Dequeue**: Removes the front element and adjusts the queue's pointers.
   - **Clear**: Resets the queue to an empty state.
   - **FirstOfQueue**: Prints the data at the front without removing it.
   - **Empty**: Returns `true` if the queue is empty.
   - **Full**: Returns `true` if the queue is full.

---

## Execute the program

### Compilation and Execution

1. Compile the code using a C++ compiler:
   ```bash
    g++ -o queue queue.cpp
   ```
2. Run the program:
   ```bash
    ./queue
   ```
### Commands in the Program:

- `i`: Insert a new element into the queue. You will be prompted to input the name, subject, type, and nProcess.
- `r`: Remove the front element from the queue and display its details.
- `l`: Clear the queue.
- `s`: Display the data at the front of the queue without removing it.
- `f`: Finish the program.

### Example Input:

    ```bash
        i John Math A 123
        i Alice Science B 456
        s
        r
        l
        f
    ```

### Example Output:

    ```bash
        Name: John Subject: Math Type: A Process: 123
        Name: Alice Subject: Science Type: B Process: 456
    ```