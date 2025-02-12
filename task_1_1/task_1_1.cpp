#include <iostream>

#define PATH_MAX 4096

struct ListNode
{
    ListNode *next;
    ListNode *prev;
    char *item;
    size_t length;

    ListNode()
    {
        next = nullptr;
        prev = nullptr;
        item = nullptr;
        length = 0;
    }

    ListNode(ListNode *prev_node)
    {
        next = nullptr;
        prev = prev_node;
        item = nullptr;
        length = 0;
    }
};

int main()
{
    char input_path[PATH_MAX + 1] = {0}, output_path[PATH_MAX + 1] = {0};

    ListNode *root_node = new ListNode();
    root_node->next = new ListNode(root_node);

    std::cin.getline(input_path, PATH_MAX);

    //  Splitting input_path by slashed to list
    ListNode *iter_node = root_node->next;
    for (size_t i = 0; i <= PATH_MAX && input_path[i] != '\0'; i++)
    {
        if (input_path[i] == '/')
            continue;

        size_t j = 0;
        while (input_path[i + j] != '/' && input_path[i + j] != '\0')
            j++;

        iter_node->item = input_path + i;
        iter_node->length = j;
        iter_node->next = new ListNode(iter_node);

        iter_node = iter_node->next;

        i += j - 1;
    }

    // {
    //     ListNode *iter_node = root_node->next;
    //     while (iter_node->next != nullptr)
    //     {
    //         std::cout << "/";
    //         for (size_t i = 0; i < iter_node->length; i++)
    //         {
    //             std::cout << iter_node->item[i];
    //         }
    //         iter_node = iter_node->next;
    //     }
    // }

    // std::cout << "\n######################################" << std::endl;

    // Removing nodes
    iter_node = root_node->next;
    while (iter_node->next != nullptr)
    {
        if (iter_node->length == 1 && iter_node->item[0] == '.')
        {
            iter_node->prev->next = iter_node->next;

            if (iter_node->next != nullptr)
                iter_node->next->prev = iter_node->prev;

            ListNode *node_to_delete = iter_node;

            iter_node = iter_node->next;

            delete node_to_delete;
        }
        else if (iter_node->length == 2 && iter_node->item[0] == '.' && iter_node->item[1] == '.')
        {
            if (iter_node->prev->prev == nullptr)
            {
                std::cout << "Going upper than the root directory is not possible." << std::endl;
                return 179;
            }
            else
            {
                // if (iter_node->prev->prev != nullptr)
                //     //     root_node = iter_node;
                //     // else
                iter_node->prev->prev->next = iter_node->next;
                iter_node->next->prev = iter_node->prev->prev;

                // if (iter_node->next != nullptr)
                //     iter_node->next->prev = iter_node->prev->prev;

                ListNode *node_to_delete = iter_node;

                iter_node = iter_node->next;

                delete node_to_delete->prev;
                delete node_to_delete;
            }
        }
        else
        {
            iter_node = iter_node->next;
        }
    }

    // Merging list to a string
    iter_node = root_node->next;
    output_path[0] = '/';
    size_t j = 0;

    while (iter_node->next != nullptr)
    {
        output_path[j] = '/';
        j++;
        for (size_t i = 0; i < iter_node->length; i++)
        {
            output_path[j] = iter_node->item[i];
            j++;
        }
        iter_node = iter_node->next;
    }

    std::cout << output_path << std::endl;

    // Freeing memory
    iter_node = root_node;

    while (iter_node != nullptr)
    {
        ListNode *node_to_delete = iter_node;
        iter_node = iter_node->next;
        delete node_to_delete;
    }

    return 0;
}