#include "list.h"

using namespace std;

namespace calc
{

template<typename T>
list<T>::node::node(const T& value)
{
    data = value;
    next = nullptr;
}

template<typename T>
list<T>::list()
{
    head = nullptr;
    size = 0;
}

template<typename T>
list<T>::~list()
{
    for(int i=0; i<size;i++)
    {
        pop_front();
    }
    delete head;
}

template<typename T>
list<T>::list(const initializer_list<T>& initList)
{
    head = nullptr;
    size = 0;
    for (const T& value : initList) {
        push_back(value);
    }
}

template<typename T>
typename list<T>::node* list<T>::get_node(int position)
{
    node* current_node = head;
    for(int i = 0; i < position; i++)
    {
        current_node = current_node->next;
    }
    return current_node;
}

template<typename T>
void list<T>::insert(const T& value, int position)
{
    if(position < 0 || position > this->size)
    {
        throw invalid_argument("position cannot be greater than size of a list (or less than 0)");
    }

    if(position == 0) push_front(value);
    else if(position == this->size-1) push_back(value);
    else
    {
        node* new_node = new node(value);
        node* prev_node = get_node(position-1);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
        this->size++;
    }
    
}

template<typename T>
void list<T>::push_front(const T& value)
{
    node* new_head = new node(value);
    new_head->next = this->head;
    this->head = new_head;
    this->size++;    
}

template<typename T>
void list<T>::push_back(const T& value)
{
    if(size == 0)
    {
        push_front(value);
    }
    else
    {
        node* new_tail = new node(value);
        get_node(size-1)->next = new_tail;
        this->size++;
    }
}

template<typename T>
void list<T>::remove(int position)
{
    if(position < 0 || position >= this->size)
    {
        throw invalid_argument("List out of range");
    }

    if(position == 0) pop_front();
    else if(position == size-1) pop_back();
    else
    {
        node* prev_node = get_node(position-1);
        node* node_to_del = prev_node->next;
        prev_node->next = node_to_del->next;
        delete node_to_del;
    }
    size--;

}

template<typename T>
void list<T>::pop_front()
{
    // if list is empty we do nothing
    if(head != nullptr)
    {
        node* old_head = head;
        head = head->next;
        delete old_head;
        this->size--;
    }
}

template<typename T>
void list<T>::pop_back()
{
    // if list is empty we do nothing
    if(head != nullptr)
    {
        if(size == 1)
        {
            pop_front();
            size--;
        }
        else
        {
            node* prev_node = get_node(size - 2);
            node* last_node = prev_node->next;
            prev_node->next = nullptr;
            delete last_node;
            size--;
        }
    }
}

template<typename T>
void list<T>::remove_value(const T& value)
{
    if(head->data == value)
    {
        node* node_to_del = head;
        head = head->next;
        delete node_to_del;
        size--;
        return;
    }
    else
    {
        node* prev_node;
        for(int i = 1;i < size; i++)
        {
            prev_node = get_node(i-1);
            if(prev_node->next->data == value)
            {
                if(i == size-1) pop_back();
                else
                {
                    node* node_to_del = prev_node->next;
                    prev_node->next = node_to_del->next;
                    delete node_to_del;
                    size--;
                    return;
                }
            }
        }
    }
}

template<typename T>
void list<T>::remove_all_values(const T& value)
{   
    node* prev_node;
    for(int i = 1;i < size; i++)
    {
        prev_node = get_node(i-1);
        if(prev_node->next->data == value)
        {
            if(i == size-1) pop_back();
            else
            {
                node* node_to_del = prev_node->next;
                prev_node->next = node_to_del->next;
                delete node_to_del;
                size--;
            }
        }
    }
    if(head->data == value)
    {
        node* node_to_del = head;
        head = head->next;
        delete node_to_del;
        size--;
    }
}

template<typename T>
int list<T>::position_of_value(const T& value)
{
    for(int i = 0;i < size; i++)
    {
        if(get_node(i)->data == value)
        {
            return i;
        }
    }
    throw invalid_argument("no such value");

}

template<typename T>
int list<T>::count_values(const T& value)
{
    int counter = 0;
    for(int i = 0;i < size; i++)
    {
        if(get_node(i)->data == value)
        {
            counter++;
        }
    }
    return counter;
}

template<typename T>
int list<T>::number_of_elements()
{
    return this->size;
}

template<typename T>
bool list<T>::empty()
{
    if(size == 0) return true;
    return false;
}

template<typename T>
ostream& operator<<(ostream& output, list<T>& a)
{
    output << "[";
    for(int i=0; i<a.size; i++)
    {
        output << a.get_node(i)->data << " ";
    }
    output << "]";
    return output;
}

template<typename T>
queue<T>::queue() : list<T>() {};

template<typename T>
void queue<T>::push(const T& value)
{
    this->push_front(value);
}

template<typename T>
T queue<T>::pop()
{
    T value;
    if(this->head != nullptr)
    {
        if(this->size == 1)
        {
            typename list<T>::node* old_head = this->head;
            this->head = old_head->next;
            value = old_head->data;
            delete old_head;
            this->size--;
        }
        else
        {
            typename list<T>::node* prev_node = this->get_node(this->size - 2);
            typename list<T>::node* last_node = prev_node->next;
            prev_node->next = nullptr;
            value = last_node->data;
            delete last_node;
            this->size--;
        }
    }
    else
    {
        throw out_of_range ("queue is empty");
    }
    return value;
}

template<typename T>
stack<T>::stack() : list<T>() {};

template<typename T>
void stack<T>::push(const T& value)
{
    this->push_front(value);
}

template<typename T>
T stack<T>::pop()
{
    T value;
    if(this->head != nullptr)
    {
        typename list<T>::node* old_head = this->head;
        this->head = old_head->next;
        value = old_head->data;
        delete old_head;
        this->size--;
    }
    else
    {
        throw out_of_range ("stack is empty");
    }
    return value;
}

}
