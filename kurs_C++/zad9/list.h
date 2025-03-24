#pragma once
#include <iostream>

using namespace std;

namespace calc
{

template <typename T>
class list
{
protected:
    class node
    {
    public:
        T data;
        node* next;

        node(const T& value);
    };

    node* head;
    int size;
    node* get_node(int position);

public:
    list();
    ~list();
    list(const initializer_list<T>& values);

    void insert(const T& value, int position);
    void push_front(const T& value);
    void push_back(const T& value);
    void remove(int position);
    void pop_front();
    void pop_back();
    void remove_value(const T& value);
    void remove_all_values(const T& value);
    int position_of_value(const T& value);
    int count_values(const T& value);
    int number_of_elements();
    bool empty();

    template<typename U>
    friend ostream& operator<<(ostream& output, list<U>& a);
};

template<typename T>
class queue : private list<T>
{
public:
    queue();

    void push(const T& value);
    T pop(); 

};

template<typename T>
class stack : private list<T>
{
public:
    stack();

    void push(const T& value);
    T pop(); 

};
}
