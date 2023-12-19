#include <iostream>    
#include <cstdlib>    
#include <ctime>
#include <algorithm>
using namespace std;

long* arr; // Global pointer for dynamic array allocation
long arrsize;    // Global variable for size of the array

// Function prototypes
void generateRandom(); // To initialize array with random data
void doSortedList(); // To sort the array
int findByBinSearch(int key); // To perform binary search
int findBySeqSearch(int key); // To perform sequential search

// Initialize array with random data while avoiding duplicates
void generateRandom() {
    for (long i = 0; i < arrsize; i++) {
        long x = rand() % arrsize;
        // Check if the number is already in the array to avoid duplicates
        arr[i] = findByBinSearch(x) != -1 ? x : arrsize + i;
    }
}

// Sort the array using the built-in sort algorithm
void doSortedList() {
    sort(arr, arr + arrsize);
}

// Implement binary search and count the number of comparisons at each step
int findByBinSearch(int key) {
    int count = 0; // Count of comparisons
    long left = 0, right = arrsize - 1, mid;
    while (left <= right) {
        count++; // Increment count for each comparison
        mid = (left + right) / 2;
        if (arr[mid] == key) {
            return count; // Return count if key is found
        }
        else if (arr[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Return -1 if key is not found
}

// Implement sequential search and count the number of accesses at each step
int findBySeqSearch(int key) {
    int count = 0; // Count of accesses
    for (long i = 0; i < arrsize; i++) {
        count++; // Increment count for each access
        if (arr[i] == key) {
            return count; // Return count if key is found
        }
    }
    // If not found, return -1
    return -1;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    cout << "Size\t\tindex\tComplexity-Sequential\tComplexity-Binary\tSeq.Cost\tBinary Cost" << endl;
    // Loop over different sizes of the array
    for (arrsize = 10; arrsize < 10000000; arrsize *= 10) {
        arr = new long[arrsize]; // Dynamically allocate memory for the array
        generateRandom(); // Fill the array with random numbers
        doSortedList(); // Sort the array
        long index = rand() % arrsize; // Choose a random index for the key
        long key = arr[index]; // The key to be searched
        int seqCost = findBySeqSearch(key); // Perform sequential search and get the cost
        int binCost = findByBinSearch(key); // Perform binary search and get the cost
        // Print the results
        cout << arrsize << "\t\t" << index << "\t\t" << seqCost << "\t\t" << binCost << "\t\t\t";
        // Determine the case for sequential search (best, worst, average)
        if (seqCost == 1)
        {
            cout << "best\t\t";
        }
        else if (seqCost == arrsize)
        {
            cout << "worst\t\t";
        }
        else
        {
            cout << "average\t\t";
        }
        // Determine the case for binary search (best, worst, average)
        if (binCost == 1)
        {
            cout << "best" << endl;
        }
        else if (binCost == floor(log2(arrsize) + 1))
        {
            cout << "worst" << endl;
        }
        else
        {
            cout << "average" << endl;
        }

        delete[] arr; // Deallocate the memory to prevent memory leaks
    }
    return 0;
}
