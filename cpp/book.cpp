#pragma once
#include<iostream>
using namespace std;
#include"string.cpp"
#include"vector.cpp"
#include"file.cpp"
struct Book{
    str bookname;
    str booknum;
    double price;
};
struct Books{
    vec<Book> Booklist;
    Books()
    {
        vec<str> a=File("book\\book.txt");
        for(auto i:a)
        {
            int j=0;
            while(i[j++]==' ');
            if(i[j]!='"')
            {
                Book a;
                char te=i.str2char();
                sscanf(te,"%s %s %d",a.bookname,a.booknum,a.price);
            }
        }
    }
};
