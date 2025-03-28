#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

#include <algorithm>

#define BASE_N 10

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

long long get_digit(long long n, long long digit)
{
    for (long long i = 1; i < digit; i++)
    {
        n /= BASE_N;
    }
    return n % BASE_N;
}

void k_sort(long long *array, ssize_t size, long long digit, long long *tmp_array)
{
    if (digit == 0)
    {
        return;
    }
    ssize_t arrays_sizes[BASE_N] = {0};
    ssize_t arrays_indexes[BASE_N] = {0};
    ssize_t arrays_prefix_sum[BASE_N] = {0};

    for (ssize_t i = 0; i < size; i++)
    {
        arrays_sizes[get_digit(array[i], digit)]++;
    }

    for (long long i = 1; i < BASE_N; i++)
    {
        arrays_prefix_sum[i] = arrays_prefix_sum[i - 1] + arrays_sizes[i - 1];
    }

    for (ssize_t i = 0; i < size; i++)
    {
        long long current_digit = get_digit(array[i], digit);
        // arrays[current_digit][arrays_indexes[current_digit]] = array[i];
        tmp_array[arrays_prefix_sum[current_digit] + arrays_indexes[current_digit]] = array[i];
        arrays_indexes[current_digit]++;
    }

    // for (ssize_t i = 0; i < size; i++)
    // {
    //     array[i] = tmp_array[i];
    // }

    long long index_first = 0;
    for (long long i = 0; i < BASE_N; i++)
    {
        k_sort(tmp_array + index_first, arrays_sizes[i], digit - 1, array + index_first);
        index_first += arrays_sizes[i];
    }
}

void array_radix_sort(long long *array, ssize_t size)
{
    long long max_digits = 0;

    long long *tmp_array = new long long[size];

    for (ssize_t i = 0; i < size; i++)
    {
        long long digits = 1;
        long long number = array[i];
        while (number >= BASE_N)
        {
            digits++;
            number /= BASE_N;
        }

        max_digits = digits > max_digits ? digits : max_digits;
    }

    k_sort(array, size, max_digits, tmp_array);

    if (max_digits % 2 == 1)
    {
        for (ssize_t i = 0; i < size; i++)
        {
            array[i] = tmp_array[i];
        }
    }

    delete[] tmp_array;
}

void array_std_sort(long long *array, ssize_t size)
{
    std::sort(array, array + size);
}

template <typename T>
using SortingFunction = void (*)(T *, ssize_t);

template <typename T>
void test_sort(long long *source_array, ssize_t size, SortingFunction<T> sorting_function, std::string sorting_name, std::ofstream &plots_data, std::string test_parameter)
{
    T *array = new T[size];

    copy(source_array, array, size);
    auto start = std::chrono::high_resolution_clock::now();
    sorting_function(array, size);
    auto end = std::chrono::high_resolution_clock::now();

    // for (ssize_t i = 0; i < size; i++)
    // {
    //     std::cout << array[i] << " ";
    // }
    // std::cout << std::endl;

    if (check_sorted(array, size))
    {
        std::cout << "\033[0;32mOK\033[0;0m " << sorting_name << " successfully sorted array of " << size << " elements. It took " << (end - start).count() * 1e-9 << " seconds" << std::endl;
        plots_data << sorting_name << ", " << test_parameter << ", " << (end - start).count() * 1e-9 << "\n";
    }
    else
    {
        std::cout << "\033[1;31mERROR\033[0;0m " << sorting_name << " failed to sort array of " << size << " elements" << std::endl;
    }

    delete[] array;
}

int main(int argc, char *argv[])
{
    long long *source_array;
    ssize_t size;

    std::cin >> size;

    source_array = new long long[size];

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

    test_sort(source_array, size, array_radix_sort, "Radix sort", outfile, test_parameter);
    test_sort(source_array, size, array_std_sort, "std::sort", outfile, test_parameter);

    delete[] source_array;
}