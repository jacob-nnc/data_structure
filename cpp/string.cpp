#pragma once
#include<string>
#include<iostream>
#include"vector.cpp"
struct str:public vec<char>{
    str():vec(){}
    str(const char* value)
    {
        size_t i=0;
        while(1)
        {
            if(value[i]!='\0')
            {
                fill++;
                sp();
                ptr[fill-1]=value[i];
            }
            else
                break;
            i++;
        }
    }
    str& operator=(const char* value)
    {
        size_t i=0;
        while(1)
        {
            if(value[i])
            {
                fill++;
                sp();
                ptr[fill-1]=value[i];
            }
            else
                break;
        }
        return *this;
    }
    char *str2char()
    {
        char *a=(char*)malloc(fill+1);
        for(size_t i=0;i<fill;i++)
        {
            a[i]=ptr[i];
        }
        a[fill]='\0';
        return a;
    }
    friend str operator+(const str& a, const str& b)
    {
        str ret=a;
        for(auto i:b)
        {
            ret.push_back(i);
        }
        return ret;
    }  
    friend str& operator+=(str& a, const str& b)
    {
        a=a+b;
        return a;   
    }
    friend ostream& operator<<(ostream&os, const str& item)
    {
        for(auto i:item)
        {
            os<<i;
        }
        return os;
    }

};