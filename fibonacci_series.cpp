//
// Created by Stephen A. Adubi on 26/10/2024.
//

#include <iostream>
#include <map> // similar to a dictionary in Python...

unsigned long long fib_rec(const int n) // old-fashioned recursion approach
{
    if(n == 0 || n == 1)
        return n;
    return fib_rec(n-1) + fib_rec(n-2);
}

unsigned long long fib_dyn(const int n) // dynamic programming approach
{
    if(n == 0 || n == 1)
        return n;
    unsigned long long fib_array[n+1]; // first step is to create an array of size n + 1
    fib_array[0] = 0; fib_array[1] = 1; // store the values of the base cases (when n == 0 and when n == 1)
    for(int i = 2; i <= n; i++) // it is predominantly an iterative approach
        fib_array[i] = fib_array[i-1] + fib_array[i-2];
    return fib_array[n];
}

unsigned long long fib_mem(const int n, std::map<int, unsigned long long>& memo) // memoization approach
{
    if(n == 0 || n == 1)
        return n;
    if(memo.contains(n))
        return memo[n];
    memo[n] = fib_mem(n-1, memo) + fib_mem(n-2, memo);
    return memo[n];
}

int main()
{
    int n; // series limit, i.e. fib(0), fib(1), fib(2), ..., fib(n)
    int choice; // choice of the problem-solving approach by the user
    std::cout << "Program that computes values in a fibonacci series using three different methods..." << std::endl;
    std::cout << "To use pure recursion, enter 1" << std::endl;
    std::cout << "To use dynamic programming method, enter 2" << std::endl;
    std::cout << "To use memoization approach, enter 3" << std::endl;
    std::cout << "Any other value not in the set {1, 2, 3} triggers the program to terminate" << std::endl;
    std::cout << "Input your choice:";
    std::cin >> choice;
    while(choice == 1 || choice == 2 || choice == 3)
    {
        std::cout << "Input an integer to represent the number of elements in the series to compute:";
        std::cin >> n;
        if(choice == 1)
        {
            unsigned long long result = fib_rec(n);
            std::cout << "Fibonacci series up to n = " << n << " is equal to " << result << std::endl;
        }
        else if(choice == 2)
        {
            unsigned long long result = fib_dyn(n);
            std::cout << "Fibonacci series up to n = " << n << " is equal to " << result << std::endl;
        }
        else if(choice == 3)
        {
            std::map<int, unsigned long long> memo; // create a key-value pair (dictionary) of n (int) and value for n (long*)
            unsigned long long result = fib_mem(n, memo);
            std::cout << "Fibonacci series up to n = " << n << " is equal to " << result << std::endl;
        }
        std::cout << "Input your choice:";
        std::cin >> choice;
    }
}
