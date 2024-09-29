// solve the selection problem
// given N integers, return the Kth largest

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int selection_problem(const vector<int>& nums, int k)
{
    // do not modify the main vector, work on a copy
    vector<int> nums_copy = nums;
    // sort the vector
    sort(nums_copy.begin(), nums_copy.end());
    return nums_copy[k-1];
}

vector<int> generate(int n)
{
    if(n < 0)
        return {};

    vector<int> nums(n);
    // populate vector
    for(auto &element : nums)
    {
        element = rand() % 100;
    }

    return nums;
}

void printVector(const vector<int>& nums)
{
    cout << "Printing the vector of integers:\n";
    for(auto &&n : nums)
    {
        cout << n << ' ';
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Usage: main NUM\n";
        exit(1);
    }

    string num = argv[1];
    int n = stoi(num);
    if(n == 0)
    {
        cerr << "NUM is not valid\n";
        exit(2);
    }

    srand(time(nullptr));

    vector<int> nums = generate(n);
    // printVector(nums);

    cout << "The Kth largest number is : "
        << selection_problem(nums,n/2) << endl;
}
