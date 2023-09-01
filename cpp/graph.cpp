#pragma once
#include<iostream>
#include<list.cpp>
#include<vector.cpp>
#include<matix.cpp>
using namespace std;
template <typename T=int,size_t N>
class LinkedMatix
{
    public:
        LinkedMatix(){}
    private:
        size_t point_num(N);
        size_t edge_num;
        matix<T> val(N,N);
};
template <typename T=int>
class LinkedMatix
{
    public:
        LinkedMatix(){}
    private:
        vec<T> point;
        vec<m_list *> edge;
};

int main()
{
}