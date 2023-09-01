#include <iostream>
#include <algorithm>
#include "json.h"
#include <easyx.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;
#define error(message)\
	{cout << string("error") + message << endl; \
	exit(1);}

template <class T>
class AVLtree;
template <class T>
class AVLtreeNode
{
public:
	T val;
	AVLtreeNode<T>* right;
	AVLtreeNode<T>* left;

	friend class AVLtree<T>;

	AVLtreeNode() = default;
	AVLtreeNode(const T& _val, AVLtreeNode<T>* R = nullptr, AVLtreeNode<T>* L = nullptr) : val(_val), right(R), left(L) {}
};
template <class T>
class AVLtree
{
public:
	AVLtreeNode<T>* root;
	AVLtree(AVLtreeNode<T>* _root = nullptr) : root(_root) {}

	AVLtreeNode<T>** firstNoBanlance(AVLtreeNode<T>*& node,int &hight)
	{
		if (node == nullptr)
		{
			hight = 0;
			return nullptr;
		}
		int rh = 0, lh = 0;
		auto ptrl=firstNoBanlance(node->left,lh);
		auto ptrr=firstNoBanlance(node->right, rh);
		if (ptrr)return ptrr;
		if (ptrl)return ptrl;
		hight = 1 + max(rh, lh);
		int d = abs(rh - lh);
		if (d > 1)
		{
			return &node;
		}
		else
		{
			return nullptr;
		}
	}
	int height(AVLtreeNode<T>* ptr)
	{
		if (ptr == nullptr)return 0;
		return 1 + max(height(ptr->left), height(ptr->right));
	}
	int height()
	{
		return height(root);
	}
	void insert(const T& val)
	{
		if (root == nullptr)
		{
			root = new AVLtreeNode<T>(val);
			return;
		}
		AVLtreeNode<T>* t = root, * p = nullptr;
		bool flag = 0;
		while (t)
		{
			p = t;
			if (val > t->val)
			{
				flag = 1;
				t = t->right;
			}
			else if (val < t->val)
			{
				flag = 0;
				t = t->left;
			}
			else
			{
				error("is in");
			}
		}
		if (flag)
			p->right = new AVLtreeNode<T>(val);
		else 
			p->left = new AVLtreeNode<T>(val);
		int _;
		auto tt = firstNoBanlance(root, _);
		if (tt != nullptr)
		{
			if ((*tt)->right)
			{
				if ((*tt)->right->right)
				{
					R_span(tt);
				}
				else
				{
					RL_span(tt);
				}
			}
			else
			{
				if ((*tt)->left->right)
				{
					LR_span(tt);
				}
				else
				{
					L_span(tt);
				}
			}
		}
	}

	void L_span(AVLtreeNode<T>** root)
	{
		AVLtreeNode<T>* t = (*root)->left;
		(*root)->left = t->right;
		t->right = (*root);
		*root = t;
	}

	void R_span(AVLtreeNode<T>** root)
	{
		AVLtreeNode<T>* t = (*root)->right;
		(*root)->right = t->left;
		t->left = (*root);
		*root = t;
	}

	void LR_span(AVLtreeNode<T>** root)
	{
		R_span(&(*root)->right);
		L_span(&(*root));
	}

	void RL_span(AVLtreeNode<T>** root)
	{
		L_span(&(*root)->left);
		R_span(&(*root));
	}

	json::obj* getJson()
	{
		auto a = new json::obj();
		a->insert("val", (json::value*)new json::numi(root->val));
		if (!root->left)
		{
			a->insert("left", (json::value*)new json::null());
		}
		else
		{
			a->insert("left", AVLtree(root->left).getJson());
		}
		if (!root->right)
		{
			a->insert("right", (json::value*)new json::null());
		}
		else
		{
			a->insert("right", AVLtree(root->right).getJson());
		}
		return a;
	}

	string toJson()
	{
		return getJson()->toJson();
	}
};

template <typename T>
void drawNode(int i, int j, const T& val)
{
	circle(i, j, 30);
	wstring t = to_wstring(val);
	outtextxy(i - (int)t.size() * 4, j - 8, t.c_str());
}

template <typename T>
void drawTree(AVLtreeNode<T>* root,int i,int j,int h)
{
	if (!root)return;
	int t = pow(2, h - 2);
	double k = atan(t * .3), sk = sin(k), ck = cos(k);
	if(root->right)
	line(i + 30 * sk, j + 30 * ck, i + t * 30- 30 * sk, j + 100 - 30 * ck);
	if (root->left)
	line(i - 30 * sk, j + 30 * ck, i - t * 30+ 30 * sk, j + 100 - 30 * ck);
	drawTree(root->right, i + t * 30, j + 100, h - 1);
	drawTree(root->left, i - t * 30, j + 100, h - 1);
	drawNode(i, j, root->val);
}

int main()
{
	initgraph(4000, 800);
	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight = 16;
	font.lfWidth = 8;
	settextstyle(&font);
	AVLtree<int> a;
	int t = 8;
	BeginBatchDraw();
	for (int i = 0; i < 250; i++)
	{
		a.insert(i);
		cleardevice();
		drawTree<int>(a.root, 2000, 30, t);
		FlushBatchDraw();
		saveimage((L"image/" + to_wstring(i) + L".jpg").c_str());
	}
	EndBatchDraw();

	ofstream("1.json") << a.toJson();
	return 0;
}