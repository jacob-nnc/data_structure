#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct m_listnode
{
    T value;
    m_listnode<T>* next;
    m_listnode<T>* prev;
};

template <typename T>
class m_list
{
    size_t len=0;
    m_listnode<T> *first=nullptr;
    m_listnode<T> *end = nullptr;
    public:
    m_list(){};
    bool empty()
    {
        return len == 0;
    }
    void init(T _val)
    {
        len = 1;
        first = new m_listnode<T>{_val,nullptr,nullptr};
        end = first;
    }
    void push_back(T val)
    {
        if(empty())
        {
            init(val);
            return;
        }
        end->next = new m_listnode<T>({val, nullptr, end});
        end = end->next;
        len++;
    }
    void push_front(T val)
    {
        if(empty())
        {
            init(val);
            return;
        }
        len++;
        m_listnode<T> *temp = new m_listnode<T>{val, first, nullptr};
        first = temp;
    }
    void del_back()
    {
        len--;
        end = end->prev;
        delete end->next;
    }
    void del_front()
    {
        len--;
        auto temp = first->next;
        delete first;
        first = temp;
    }

    void Print()
    {
        auto tem = first;
        for (; tem != nullptr;tem=tem->next)
        {
            cout << tem->value<<' ';
        }
        cout << '\n';
    }
};