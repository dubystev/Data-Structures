#include <iostream>
#include <vector>

// You could copy the contents into your main cpp program.

int search(const std::vector<int>& arr, const int key)
{
    int beg = 0; // initialise the beginning variable
    int end = arr.size() - 1; // initialise the end variable
    while (beg <= end) { // while the beg index isn't above the end index
        int mid = (beg + end) / 2;
        if (arr[mid] == key) // Check if the element at mid is the target element
            return mid;
        if (arr[mid] < key) // Check if the element at mid is less than the target element (key).
            beg = mid + 1;
        else
            end = mid - 1; // Slide the search to the left side of the mid-element
    }

    return -1;
}

int main()
{
    // create the array in the slide
    const std::vector arr = {10, 12, 24, 29, 39, 40, 51, 56, 69};
    int result = search(arr, 40);   // call the binary search function
    std::cout << result << std::endl; // display the result.
    return 0;
}
