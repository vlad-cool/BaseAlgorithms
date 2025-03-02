#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

template <typename T>
void swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T>
void copy(const T *src, T *dest, ssize_t size)
{
    for (ssize_t i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

template <typename T>
bool check_sorted(T *array, ssize_t size)
{
    for (ssize_t i = 1; i < size; i++)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
void array_bubble_sort(T *array, ssize_t size, bool with_check = false)
{
    bool sorted;
    for (ssize_t i = 1; i < size; i++)
    {
        sorted = true;
        for (ssize_t j = 0; j < size - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                sorted = false;
                swap(array + j, array + j + 1);
            }
        }
        if (with_check && sorted)
        {
            return;
        }
    }
}

template <typename T>
void array_shaker_sort(T *array, ssize_t size, bool with_check = false)
{
    bool sorted;
    for (ssize_t i = 1; i < size / 2; i++)
    {
        sorted = true;
        for (ssize_t j = i - 1; j < size - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                sorted = false;
                swap(array + j, array + j + 1);
            }
        }

        for (ssize_t j = size - i - 1; j >= i; j--)
        {
            if (array[j] < array[j - 1])
            {
                sorted = false;
                swap(array + j, array + j - 1);
            }
        }

        if (with_check && sorted)
        {
            return;
        }
    }
}

#define COMB_COEFFICIENT 2 / 3
template <typename T>
void array_comb_sort(T *array, ssize_t size, bool with_check = false)
{
    bool sorted = false;
    ssize_t distance = size;

    while (!sorted || distance > 1)
    {
        distance = distance * COMB_COEFFICIENT;
        if (distance < 1)
        {
            distance = 1;
        }

        sorted = true;
        for (ssize_t i = 0; i + distance < size; i++)
        {
            if (array[i] > array[i + distance])
            {
                sorted = false;
                swap(array + i, array + i + distance);
            }
        }
    }
}
template <typename T>
using SortingFunction = void (*)(T *, ssize_t, bool);

template <typename T>
void test_sort(T *source_array, ssize_t size, SortingFunction<T> sorting_function, std::string sorting_name, std::ofstream &plots_data, std::string test_parameter)
{
    T *array = new T[size];

    for (int with_checking = 0; with_checking < 2; with_checking++)
    {
        copy(source_array, array, size);
        auto start = std::chrono::high_resolution_clock::now();
        sorting_function(array, size, with_checking);
        auto end = std::chrono::high_resolution_clock::now();
        if (check_sorted(array, size))
        {
            std::cout << "\033[0;32mOK\033[0;0m " << sorting_name << (with_checking ? " with checking" : "") << " successfully sorted array of " << size << " elements. It took " << (end - start).count() * 1e-9 << " seconds" << std::endl;
            plots_data << sorting_name << (with_checking ? " with check" : "") << ", " << test_parameter << ", " << (end - start).count() * 1e-9 << "\n";
        }
        else
        {
            std::cout << "\033[1;31mERROR\033[0;0m " << sorting_name << (with_checking ? " with checking" : "") << " failed to sort array of " << size << "elements" << std::endl;
        }
    }

    delete[] array;
}

int main(int argc, char *argv[])
{
    int *source_array;
    ssize_t size;

    std::cin >> size;

    source_array = new int[size];

    for (ssize_t i = 0; i < size; i++)
    {
        std::cin >> source_array[i];
    }

    std::string plots_data_path = "/dev/null";
    std::string test_parameter = std::to_string(size);
    if (argc > 1)
    {
        plots_data_path = argv[1];
    }
    if (argc > 2)
    {
        test_parameter = argv[2];
    }

    std::ofstream outfile(plots_data_path, std::ios::app);

    test_sort(source_array, size, array_bubble_sort, "Bubble sort", outfile, test_parameter);
    test_sort(source_array, size, array_shaker_sort, "Shaker sort", outfile, test_parameter);
    test_sort(source_array, size, array_comb_sort, "Comb sort", outfile, test_parameter);

    delete[] source_array;
}