#include <vector>
#include <thread>

template<typename T>
void merge(T* arr, int left, int mid, int right)
{
    std::vector<T> tmp;
    int i = left, j = mid;

    while (i < mid && j < right)
        tmp.push_back(arr[i] < arr[j] ? arr[i++] : arr[j++]);

    while (i < mid)   tmp.push_back(arr[i++]);
    while (j < right) tmp.push_back(arr[j++]);

    for (int k = 0; k < tmp.size(); ++k)
        arr[left + k] = tmp[k];
}

int MAX_DEPTH = 4; // max 16

template<typename T>
void merge_sort(T* arr, int left, int right, int depth = 0)
{
    if (right - left <= 1)
        return;

    int mid = (left + right) / 2;

    if (depth < MAX_DEPTH)
    {
        std::thread t1(merge_sort<T>, arr, left, mid, depth + 1);
        std::thread t2(merge_sort<T>, arr, mid, right, depth + 1);

        t1.join();
        t2.join();
    }
    else
    {
        merge_sort(arr, left, mid, depth + 1);
        merge_sort(arr, mid, right, depth + 1);
    }

    merge(arr, left, mid, right);
}

#include <iostream>

int main()
{
    int arr[] = {9, 3, 7, 1, 8, 2, 5, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, n);

    for (int x : arr)
        std::cout << x << " ";
    std::cout << "\n";
}