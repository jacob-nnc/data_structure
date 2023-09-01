#pragma once
#include<iostream>
#include<initializer_list>
#include"ptr.cpp"
using namespace std;
template <typename T> class vec 
{
    protected:  
        PTR<T> ptr;
        size_t fill,all;
        
    public:
        vec():fill(0),all(10)
        {
            if(ptr.newspace(all))
                for(size_t i=0;i<all;i++)
                {
                    ptr[i]=T();
                }
        }
        vec(const vec&item)
        {
            fill=item.fill;
            all=item.all;
            ptr=item.ptr;
        }
        bool operator==(const vec &item)
        {
            if(item.all==all&&item.fill==fill)
            {
                for(auto i=0;i<fill;i++)
                {
                    if(ptr[i]!=item[i])
                    {
                        return false;
                    }
                }
            }
            else
                return false;
            return true;
        }
        vec& operator=(const vec &item)
        {
            fill=item.fill;
            all=item.all;
            ptr=item.ptr;
            return *this;
        }
        bool operator!=(const vec& item)
        {
            return !operator==(item);
        }
        T& operator[](size_t i)
        {
            return ptr[i];
        }
        T operator[](size_t i)const
        {
            return ptr[i];
        }
        friend ostream& operator<<(ostream&os, const vec& item)
        {
            for(size_t i=0;i<item.fill;i++)
            {
                os<<item[i]<<' '<<endl;
            }
            return os;
        }
        T* begin(){return &ptr._p[0];}
        T* end(){return &ptr._p[fill];}
        T* end()const{return &ptr._p[fill];}
        T* begin()const{return &ptr._p[0];}
        bool empty()
        {
            return !fill;
        }
        size_t len()
        {
            return fill;
        }
        void pop_back()
        {
            if(fill)
                fill--;
            else
                cerr<<"you can't pop in a empty vec"<<endl;
        }
        void sp()
        {
             if(fill>all*0.75)
            {
                all*=1.5;
                if(ptr.spspace(all))
                    ;
                else
                    cerr<<"error realloc"<<endl;
            }
        }
        void push_back(const T& value)
        {
            fill++;
            sp();
            ptr[fill-1]=value;
        }
        void insert(size_t insert_pos, const T& value)
        {
            if(insert_pos>fill)
            {
                cerr<<"insert_pos out of index"<<endl;
            }
            fill++;
            sp();
            for(size_t i=fill-2;i>=insert_pos&&i<=fill-2;i--)
            {
                ptr[i+1]=ptr[i];
            }
            ptr[insert_pos]=value;
        }
        void remove(size_t pos)
        {
            for(auto i=pos;i<fill;i++)
            {
                ptr[i]=ptr[i+1];
            }
            fill--;
        }
        void clear()
        {
            fill=0;
        }
        virtual ~vec()
        {
            ptr.despace();
        }
};