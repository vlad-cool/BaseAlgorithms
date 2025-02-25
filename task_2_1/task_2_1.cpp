#include <iostream>
#include <chrono>

template <typename T>
void swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T>
void copy(const T* src, T* dest, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

template <typename T>
bool check_sorted(T *array, size_t size)
{
    for (size_t i = 1; i < size; i++)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
void array_bubble_sort(T *array, size_t size, bool with_check=false)
{
    bool sorted;
    for (size_t i = 1; i < size; i++)
    {
        sorted = true;
        for (size_t j = 0; j < size - i; j++)
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
void array_shaker_sort(T *array, size_t size, bool with_check=false)
{
    bool sorted;
    for (size_t i = 1; i < size / 2; i++)
    {
        sorted = true;
        for (size_t j = i - 1; j < size - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                sorted = false;
                swap(array + j, array + j + 1);
            }
        }

        for (size_t j = size - i - 1; j >= i; j--)
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

int main()
{
    int *source_array, *array;
    size_t size;
    
    std::cin >> size;

    source_array = new int[size];
    array = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        std::cin >> source_array[i];
    }

    copy(source_array, array, size);
    
    auto start = std::chrono::high_resolution_clock::now();
    array_bubble_sort(array, size);
    auto end = std::chrono::high_resolution_clock::now();
    // for (size_t i = 0; i < size; i++)
    // {
    //     std::cout << array[i] << " ";
    // }
    std::cout << std::endl;
    if (check_sorted(array, size))
    {
        std::cout << "\033[0;32mOK\033[0;0m" << std::endl;
        std::cout << "Buble sort successfully sorted array of " << size << " elements. It took " << (end - start).count() * 1e-9 << " seconds" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31mERROR\033[0;0m" << std::endl;
    }

    copy(source_array, array, size);
    array_shaker_sort(array, size);
    // for (size_t i = 0; i < size; i++)
    // {
    //     std::cout << array[i] << " ";
    // }
    std::cout << std::endl;
    if (check_sorted(array, size))
    {
        std::cout << "\033[0;32mOK\033[0;0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31mERROR\033[0;0m" << std::endl;
    }


    delete[] array;
}