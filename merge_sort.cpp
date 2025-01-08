//
// Created by Stephen A. Adubi on 08/Jan/2025.
//

#include <cmath>
#include <iostream>

void merge(int array[], int start1, int end1, int start2, int end2)
{
    const int size = end2 - start1 + 1;
    int array_result[size];
    int p1=start1, p2=start2;
    for(int i = 0; i < size; i++)
    {
        if(p1 <= end1 && p2 <= end2)
        {
            if(array[p1] < array[p2])
            {
                array_result[i] = array[p1];
                p1++;
            }
            else
            {
                array_result[i] = array[p2];
                p2++;
            }
        }
        else if(p1 <= end1)
        {
            array_result[i] = array[p1];
            p1++;
        }
        else
        {
            array_result[i] = array[p2];
            p2++;
        }
    }

    int j = 0;
    for(int i = start1; i <= end2; i++)
        array[i] = array_result[j++];
}

void merge_sort(int array[], int start, int end)
{
    int size = end - start + 1;
    if(size > 1)
    {
        int mid = static_cast<int>(floor((start + end) / 2));
        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, end);
        merge(array, start, mid, mid + 1, end);
    }
}

int main()
{
    std::cout << "Merge Sort Demo";
    srand(time(0));
    constexpr int min_size = 15, max_size = 250;
    constexpr int range = max_size - min_size + 1;
    const int arr_size = min_size + rand() % range;
    int array[arr_size];
    for(int i = 0; i < arr_size; i++)
    {
        constexpr int val_min = 1;
        constexpr int val_max = 1000;
        int x = rand() % (val_max - val_min + 1);
        array[i] = val_min + x;
    }

    std::cout << "\nInitial array before sorting shown below...\n";
    for(int i = 0; i < arr_size; i++)
        std::cout << array[i] << " ";

    //merge_sort(new int[] {3, 3, 8, 10, 11, 4, 8, 17}, 0, 7);
    merge_sort(array, 0, arr_size - 1);

    std::cout << "\n\nSorted array shown below...\n";
    for(int i = 0; i < arr_size; i++)
        std::cout << array[i] << " ";
}