#include<iostream>
using namespace std;
#include"complex.cpp"
#include"book.cpp"
#include"vector.cpp"
#include"string.cpp"

#include"file.cpp"
#include"list.cpp"
#include"ptr.cpp"
#include"list.cpp"
#include"tree.cpp"
#include"matix.cpp"
#include<math.h>
#include"tree.cpp"
#include"graph.cpp"
int main()
{
	clock_t a=clock();
    cout<<sqrt(999999);
    cout<<clock()-a<<endl;
    a=clock();
    int s=999999;
    int x=s/2;
    for(int i=0;i<1000;i++)
    {
        x=x-(x*x-s)/x/2;
    }
    cout<<x<<endl;
    cout<<clock()-a<<endl;
}
