#include <iostream>
using namespace std;

// Definition of the stack class
class stack {
private:
    int* arr;       // Pointer to dynamically allocated array for stack elements
    int arrsize;        // Current size (number of elements) of the stack
    int capacity;    // Maximum capacity of the stack
    int top;         // Index of the top element in the stack

public:
    // Constructor for stack with a specified capacity
    stack(int new_capacity) {
        arr = new int[new_capacity];  // Allocate memory for stack elements
        capacity = new_capacity;       // Set the capacity
        arrsize = 0;                      // Initialize size
        top = -1;                      // Initialize top index (empty stack)
    }

    // Destructor for stack
    ~stack() {
        delete[] arr;  // Release dynamically allocated memory
    }

    // Method to push a value onto the stack
    void push(int val) {
        if (arrsize == capacity) {
            cout << "The Stack is Full" << endl;  // Check for stack overflow
            return;
        }
        else {
            top = (top + 1) % capacity;  // Update the top index
            arr[top] = val;             // Add the new value
            arrsize++;                      // Increment size
        }
    }

    // Method to get the top element of the stack
    int get_top() {
        if (is_empty()) {
            cout << "The stack is empty" << endl;
        }
        else {
            return arr[top];  // Return the top element
        }
    }

    // Method to pop the top element off the stack
    void pop() {
        if (is_empty()) {
            cout << "The Stack is Empty" << endl;  // Check for underflow
            return;
        }
        else {
            top = (top - 1 + capacity) % capacity;  // Update the top index
            arrsize--;                                // Decrement size
        }
    }

    // Method to check if the stack is empty
    bool is_empty() {
        return arrsize == 0;  // Returns true if stack is empty
    }
};
/*
int main() {
    int num = 0;
    int temp = 0;

    cout << "Please Input The Number of Elements: ";
    cin >> num;
    stack tmpst(num);  // Temporary stack used for sorting
    stack st(num);     // Main stack

    cout << "Please Input " << num << " Elements" << endl;
    cout << "(1)push the elements ";
    while (num--) {
        cin >> temp;
        st.push(temp);  // Push elements onto the main stack
    }
    cout << "onto the stack list" << endl;

    cout << "(2) The process of sorting elements of stack st is: " << endl;
    // Sorting algorithm using two stacks
    while (!st.is_empty()) {
        int tmp = st.get_top();  // Get the top element from the main stack
        st.pop();                // Pop it from the main stack
        cout << "st: pop out " << tmp << "=>" << endl;

        // Move elements from the temporary stack back to the main stack if they are greater than the current element
        while (!tmpst.is_empty() && tmpst.get_top() > tmp) {
            cout << "tmpst: get the top element " << tmpst.get_top() << "." << endl;
            cout << "Since " << tmpst.get_top() << ">" << tmp << " tmpst: pop out " << tmpst.get_top() << "." << endl;
            st.push(tmpst.get_top());
            tmpst.pop();
            cout << "st: push " << tmp << "." << endl;
        }
        tmpst.push(tmp);  // Push the current element onto the temporary stack
        cout << "tmpst: push " << tmp << "." << endl;
    }

    // Move all elements back to the main stack
    while (!tmpst.is_empty()) {
        st.push(tmpst.get_top());
        tmpst.pop();
    }

    cout << "(3)the sorting of stack st ends" << endl;
    cout << "(4)the popping sequence of st is:";

    // Print the elements in sorted order
    while (!st.is_empty()) {
        cout << st.get_top() << " ";
        st.pop();
    }
    cout << endl;

    return 0;
}
*/
