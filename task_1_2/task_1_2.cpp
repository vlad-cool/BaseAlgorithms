#include <iostream>
#include <string>
#include "../common/list.h"

void visit(ListNode<std::string> **list_node, std::string website)
{
    *list_node = (**list_node).insert_after(website);

    while (!(**list_node).is_last())
    {
        (**list_node).delete_next_node();
    }

    std::cout << website << std::endl;
}

void go_backward(ListNode<std::string> **list_node, unsigned int N)
{
    while (N != 0 && !(**list_node).is_first())
    {
        N--;
        *list_node = (**list_node).get_prev();
    }
    std::cout << (**list_node).item << std::endl;
}

void go_forward(ListNode<std::string> **list_node, unsigned int N)
{
    while (N != 0 && !(**list_node).is_last())
    {
        N--;
        *list_node = (**list_node).get_next();
    }
    std::cout << (**list_node).item << std::endl;
}

int main()
{
    ListNode<std::string> *root_node = new ListNode<std::string>("homepage");

    ListNode<std::string> *current_node = root_node;

    std::string command;
    std::string website;

    unsigned int N;

    std::cout << root_node->item << std::endl;

    while (std::cin >> command)
    {
        if (command == "visit")
        {
            std::cin >> website;
            visit(&current_node, website);
        }
        else if (command == "back")
        {
            std::cin >> N;
            go_backward(&current_node, N);
        }
        else if (command == "forward")
        {
            std::cin >> N;
            go_forward(&current_node, N);
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }

    delete root_node;

    return 0;
}