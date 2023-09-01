#pragma once
#include<iostream>
#include"string.cpp"
using namespace std;
class File
{
    FILE* _p;
    public:
    File(const char *name,const char *mode="r")
    {
        _p=fopen(name,mode);
        fseek(_p,0,SEEK_SET);
    }
    void seek(long long offset, int filepos)
    {
        fseek(_p,offset,filepos);
    }
    size_t tell()
    {
        return ftell(_p);
    }
    vec<str> read()
    {
        vec<str> as;
        seek(0,0);
        char ch=getc(_p);
        str a;
        while(ch!=EOF)
        {
            a.push_back(ch);
            if(ch=='\n')
            {
                as.push_back(a);
                a.clear();
            }
            ch=getc(_p);
        }
        return as;
    }
    str readline()
    {
        str ret;
        char ch=getc(_p);
        while(1)
        {
            ret.push_back(ch);
            if(ch=='\n')
                break;
            ch=getc(_p);
        }
        return ret;
    }
    void close()
    {
        fclose(_p);
    }
    ~File()
    {
        fclose(_p);
    }
};