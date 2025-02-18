#include <iostream>

#include "../common/list.h"

#define PATH_MAX 4096

struct str_slice
{
    char *str;
    ssize_t length;

    str_slice()
    {
        str = nullptr;
        length = 0;
    }

    str_slice(char *str, ssize_t length)
    {
        this->str = str;
        this->length = length;
    }
};


int main()
{
    char input_path[PATH_MAX + 1] = {0}, output_path[PATH_MAX + 1] = {0};

    ListNode<str_slice> *root_node = new ListNode<str_slice>(str_slice());
    // root_node->next = new ListNode(root_node);
    

    std::cin.getline(input_path, PATH_MAX);

    //  Splitting input_path by slashed to list
    // ListNode<str_slice> *iter_node = root_node->insert_after(str_slice());
    ListNode<str_slice> *iter_node = root_node;
    for (ssize_t i = 0; i <= PATH_MAX && input_path[i] != '\0'; i++)
    {
        if (input_path[i] == '/')
            continue;

        ssize_t j = 0;
        while (input_path[i + j] != '/' && input_path[i + j] != '\0')
            j++;

        iter_node = iter_node->insert_after(str_slice(input_path + i, j));

        i += j - 1;
    }

    iter_node->insert_after(str_slice());

    // Removing nodes
    iter_node = root_node;
    while (!iter_node->is_last())
    {
        if (iter_node->item.length == 1 && iter_node->item.str[0] == '.')
        {
            iter_node = iter_node->get_prev();
            iter_node->delete_next_node();
        }
        else if (iter_node->item.length == 2 && iter_node->item.str[0] == '.' && iter_node->item.str[1] == '.')
        {
            // std::cout << std::boolalpha << root_node->is_first() << std::endl;
            // std::cout << std::boolalpha << (root_node == root_node->get_next()->get_prev()) << std::endl;
            // std::cout << root_node << std::endl;
            // std::cout << iter_node->get_prev() << std::endl;
            // std::cout << iter_node << std::endl;
            if (iter_node->get_prev()->is_first())
            {
                std::cout << "Going upper than the root directory is not possible." << std::endl;
                // while (root_node != nullptr)
                // {
                //     // ListNode *node_to_delete = root_node;
                //     root_node = root_node->next;
                //     root_node->delete_prev_node();
                //     // delete node_to_delete;
                // }
                return 179;
            }
            else
            {
                iter_node = iter_node->get_prev()->get_prev();
                iter_node->delete_next_node();
                iter_node->delete_next_node();
            }
        }
        else
        {
            iter_node = iter_node->get_next();
        }
    }

    // Merging list to a string
    iter_node = root_node->get_next();
    output_path[0] = '/';
    ssize_t j = 0;

    while (!iter_node->is_last())
    {
        output_path[j] = '/';
        j++;
        for (ssize_t i = 0; i < iter_node->item.length; i++)
        {
            output_path[j] = iter_node->item.str[i];
            j++;
        }
        iter_node = iter_node->get_next();
    }

    std::cout << output_path << std::endl;

    // std::cout << "AAAAAAA" << std::endl;

    // std::cout << "AAAAAAAAAAAAAAA" << root_node->is_first() << root_node->is_last() << std::endl;

    // Freeing memory
    // iter_node = root_node;

    // while (iter_node != nullptr)
    // {
    //     ListNode *node_to_delete = iter_node;
    //     iter_node = iter_node->next;
    //     delete node_to_delete;
    // }

    delete root_node;

    return 0;
}