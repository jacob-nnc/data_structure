#pragma once
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;
class tree
{
    public:
    int _val;
    tree* _right;
    tree* _left;
    public:
    tree():_val(0),_left(nullptr),_right(nullptr){}
    ~tree()
    {
        if(_right)
            delete _right;
        else if(_left)
            delete _left;
    }

    void randtree(int layer)
    {
        if(layer==1)
        {
            _val=layer;
            return;
        }
        _val=layer;
        this->_right=new tree();
        this->_right->randtree(layer-1);
        this->_left=new tree();
        this->_left->randtree(layer-1);
    }

    void Traversal()
    {
        
        if(_right!=nullptr)
        {
            _right->Traversal();
        }
        
        if(_left!=nullptr)
        {
            _right->Traversal();
        }

        cout<<_val<<' ';
    }
    void Traversal_loop()
    {
        tree *it=this;
        vector<tree*>stack;
        while(it||!stack.empty())
        {
            while(it)
            {
                stack.push_back(it);
                it=it->_left;
            }
            if(!stack.empty())
            {
                it=stack.back();
                cout<<it->_val<<' ';
                stack.pop_back();
                it=it->_right;
            }
        }
    }
    void Traversal_loop()
    {
        tree *it=this;
        vector<tree*>stack;
        while(it||!stack.empty())
        {
            while(it)
            {
                stack.push_back(it);
                it=it->_left;
            }
            if(!stack.empty())
            {
                it=stack.back();
                cout<<it->_val<<' ';
                stack.pop_back();
                it=it->_right;
            }
        }
    }
};
int main()
{
    tree a;
    a.randtree(4);
    a.Traversal();
    cout<<endl;
    a.Traversal_loop();
}
