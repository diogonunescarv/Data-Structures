# Linked Stack Implementation in C++

This project demonstrates a **linked list-based implementation of a Stack** in C++. A Stack is a linear data structure that follows the **Last In, First Out (LIFO)** principle, meaning the last element added to the Stack will be the first one to be removed.

## Features

The implementation supports the following operations:
- **Pile (Push):** Add a new element to the top of the Stack.
- **Unstack (Pop):** Remove and return the top element of the Stack.
- **Top (Peek):** View the top element of the Stack without removing it.
- **Clear:** Remove all elements from the Stack.
- **Empty:** Check if the Stack is empty.

## Structure Overview

### `Data`
The `Data` structure holds the information stored in each element of the Stack:
- `name` (string): Represents the name of the element.
- `type` (char): Represents the type of the element.
- `value` (int): Represents the value of the element.

### `Node`
The `Node` class represents an individual element in the Stack. Each node contains:
- `mData`: The data stored in the node.
- `mNext`: A pointer to the next node in the Stack.

### `Stack`
The `Stack` class manages the linked list of nodes and provides the Stack functionalities. Key methods include:
- **`Pile(const Data &d):`** Adds a new element to the top of the Stack.
- **`Unstack():`** Removes and returns the top element of the Stack.
- **`Top():`** Displays the top element without removing it.
- **`Clear():`** Clears all elements in the Stack.
- **`Empty():`** Checks if the Stack is empty.

## Execute the program

### Input Commands
The program reads commands from the user to interact with the Stack:
- `i`: Insert a new element. Input format: `i name type value`.
- `r`: Remove and display the top element.
- `l`: Clear all elements from the Stack.
- `s`: Display the top element without removing it.
- `f`: Finish the program.

### Example Input:

   ```bash
      i Alice A 10
      i Bob B 20
      s
      r
      l
      f
   ```

### Example Output:

    ```bash
        name: Bob type: B value: 20
        name: Bob type: B value: 20
        name: Alice type: A value: 10
    ```

## How It Works

1. **Pile Operation:** Adds a new `Node` to the top of the Stack and updates the pointer to the top.
2. **Unstack Operation:** Removes the top `Node`, retrieves its data, and updates the top pointer to the next node.
3. **Top Operation:** Retrieves the data of the top element without altering the Stack.
4. **Clear Operation:** Iteratively removes all nodes from the Stack.
5. **Empty Check:** Verifies if the top pointer is `nullptr`.

## Error Handling
- If an operation is performed on an empty Stack (e.g., `Unstack` or `Top`), the program throws a `runtime_error` with an appropriate message.

## Compilation and Execution

1. Compile the code using a C++ compiler:
   ```bash
    g++ -o stack stack.cpp
   ```
2. Run the program:
   ```bash
    ./stack
   ```
