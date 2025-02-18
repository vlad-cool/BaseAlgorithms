#ifndef LIST_H
#define LIST_H

template <typename T>
class ListNode
{
private:
    ListNode *next;
    ListNode *prev;

public:
    T item;

    bool is_last()
    {
        return next == nullptr;
    }

    bool is_first()
    {
        return prev == nullptr;
    }

    ListNode(T item)
    {
        next = nullptr;
        prev = nullptr;
        this->item = item;
    }

    ~ListNode()
    {
        while (next != nullptr)
        {
            ListNode *to_delete = next;
            next = next->next;
            to_delete->next = nullptr;
            to_delete->prev = nullptr;
            delete to_delete;
        }
        while (prev != nullptr)
        {
            ListNode *to_delete = prev;
            prev = prev->prev;
            to_delete->next = nullptr;
            to_delete->prev = nullptr;
            delete to_delete;
        }
    }

    void delete_next_node()
    {
        if (next == nullptr)
        {
            return;
        }
        ListNode *node_to_delete = next;
        next = next->next;

        if (next != nullptr)
        {
            next->prev = this;
        }

        node_to_delete->prev = nullptr;
        node_to_delete->next = nullptr;

        delete node_to_delete;
    }

    void delete_prev_node()
    {
        if (prev == nullptr)
        {
            return;
        }
        ListNode *node_to_delete = prev;
        prev = prev->prev;

        if (prev != nullptr)
        {
            prev->next = this;
        }

        node_to_delete->prev = nullptr;
        node_to_delete->next = nullptr;

        delete node_to_delete;
    }

    ListNode *insert_after(T item)
    {
        ListNode *new_node = new ListNode(item);
        new_node->next = next;
        new_node->prev = this;
        if (next != nullptr)
        {
            next->prev = new_node;
        }
        next = new_node;
        return next;
    }

    ListNode *insert_before(T item)
    {
        ListNode *new_node = new ListNode(item);
        new_node->prev = prev;
        new_node->next = this;
        if (prev != nullptr)
        {
            prev->next = new_node;
        }
        prev = new_node;
        return prev;
    }

    ListNode *get_prev()
    {
        return prev;
    }

    ListNode *get_next()
    {
        return next;
    }
};

// template <typename T>
// class List
// {
// private:
//     ListNode *first_node, *last_node;
// public:
//     List()
//     {
//         first_node = nullptr;
//         last_node = nullptr;
//     }

//     push_back(T item)
//     {

//     }
// };

#endif
