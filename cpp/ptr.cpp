#pragma once
#include<iostream>
#include"vector.cpp"
#include"list.cpp"
using namespace std;
template <typename T> class vec;
template <typename T> class li;
/*
这是一个内存管理类
*/
template <typename T>
class PTR{
    protected:
        T* _p;
        size_t n;
    public:
        friend class li<T>;
        friend class vec<T>;
        PTR():n(0){};
        PTR(const PTR& item):n(item.n){
            newspace(n);
            for(auto i=0;i<n;i++)
                _p[i]=item[i];
        }
        PTR& operator=(const PTR& item)
        {
            n=item.n;
            newspace(n);
            for(auto i=0;i<n;i++)
                _p[i]=item[i];
            return *this;
        }
        bool newspace(size_t n)
        {
            this->n=n;
            _p=(T*)malloc(n*sizeof(T));
            return !!_p;
        }
        bool spspace(size_t n)
        {
            this->n=n;
            T* te=(T*)realloc(_p,n*sizeof(T));
            if(te)
            {
                _p=te;
            }
            else
                return false;
            return true;
        }
        void despace()
        {
            free(_p);
            _p=NULL;
        }

        T& operator[](size_t n)
        {
            return _p[n];
        }
        T operator[](size_t n)const
        {
            return _p[n];
        }
        bool operator==(const PTR& item)
        {
            return n==item.n;
        }
        bool operator!=(const PTR& item)
        {
            return !*this==item;
        }
        ~PTR()
        {
            despace();
        }
};
