#include <iostream>
#include <string>
#include "../common/list.h"

void visit(ListNode<std::string> *list, std::string website)
{

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

            ListNode *iter_node = current_node->next;
            while (iter_node != nullptr)
            {
                ListNode *node_to_delete = iter_node;

                iter_node = iter_node->next;
                delete node_to_delete;
            }

            current_node->next = new ListNode(current_node);
            current_node->next->item = website;
            current_node = current_node->next;

            std::cout << website << std::endl;
        }
        else if (command == "back")
        {
            std::cin >> N;
            while (N != 0 && current_node->prev != nullptr)
            {
                N--;
                current_node = current_node->prev;
            }
            std::cout << current_node->item << std::endl;
        }
        else if (command == "forward")
        {
            std::cin >> N;
            while (N != 0 && current_node->next != nullptr)
            {
                N--;
                current_node = current_node->next;
            }
            std::cout << current_node->item << std::endl;
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }

    ListNode *iter_node = root_node;
    while (iter_node != nullptr)
    {
        ListNode *node_to_delete = iter_node;

        iter_node = iter_node->next;
        delete node_to_delete;
    }

    return 0;
}