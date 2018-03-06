#pragma once
#include <stack>
#include <iostream>
using namespace std;
template<class Type>
class AVLTree
{
	class AVLNode
	{
	public:
		typedef AVLNode* pointer;
		typedef const AVLNode* const_pointer;
		friend class AVLTree;
	public:
		AVLNode() :data(Type()), leftchild(nullptr), rightchild(nullptr), bf(0) {}
		AVLNode(Type d, pointer left = nullptr, pointer right = nullptr) :
			data(d), bf(0), leftchild(left), rightchild(right) {}
		~AVLNode() {};
	public:
		void setData(Type d)
		{
			data = d;
		}
		Type getData()const
		{
			return data;
		}
	private:
		int bf;
		Type data;
		pointer leftchild;
		pointer rightchild;
	};
public:
	typedef AVLNode*					pointer;
	typedef const AVLNode*			const_pointer;
	typedef Type					value_type;
public:
	AVLTree():root(nullptr) {}
public:
	bool Insert(value_type x)
	{
		return _insert(root, x);
	}
	bool Remove(Type &x)
	{
		return _remove(root, x);
	}
protected:
	bool _remove(pointer &t, Type &x)
	{
		pointer p = t;
		pointer pr = nullptr;
		stack<pointer> st;
		while (p != nullptr)
		{
			if (p->data == x)
				break;
			pr = p;
			st.push(pr);
			if (p->data > x)
				p = p->leftchild;
			else
				p = p->rightchild;
		}
		
		if (p == nullptr)
			return false;
		
		pointer q = nullptr;
		if (p->leftchild != nullptr&&p->rightchild != nullptr)
		{
			pr = p;
			st.push(pr);
			q = p->leftchild;
			while (q->rightchild != nullptr)
			{
				pr = q;
				st.push(pr);
				q = q->rightchild;
			}
			p->data = q->data;
			p = q;
		}

		if (p->leftchild != nullptr)
			q = p->leftchild;
		else
			q = p->rightchild;

		if (pr == nullptr)
			t = p;
		else
		{
			if (pr->rightchild == p)
				pr->rightchild = q;
			else
				pr->leftchild = q;


			while (!st.empty())
			{
				pr = st.top();
				st.pop();

				if (q != nullptr)
				{
					if (pr->leftchild == q)
						pr->bf++;
					else
						pr->bf--;
				}
				else
					pr->bf = 0;

				if (pr->bf == -1 || pr->bf == 1)
					return true;
				else if (pr->bf == 0)
					q = pr;
				else
				{
					if (pr->bf > 0)
						q = pr->rightchild;
					else
						q = pr->leftchild;
					if (q->bf == 0)
					{
						if (pr > 0)
						{
							RotateR(pr);
							pr->bf = 1;
							pr->leftchild->bf = 1;
						}
						else
						{
							RotateL(pr);
							pr->bf = -1;
							pr->rightchild->bf = -1;
						}
						break;
					}
					else
					{
						if (q->bf > 0 && pr->bf > 0)
						{
							RotateL(pr);
						}
						else if (q->bf < 0 && pr->bf < 0)
						{
							RotateR(pr);
						}
						else if (q->bf > 0 && pr->bf < 0)
						{
							RotateRL(pr);
						}
						else
						{
							RotateRL(pr);
						}
					}
				}
			}
			if (st.empty())
			{
				t = pr;
				t->color = BLACK;
			}
			else
			{
				pointer tmp = st.top();
				if (tmp->data > pr->data)
					tmp->leftchild = pr;
				else
					tmp->rightchild = pr;

			}
		}
		delete p;
		return true;
	}
	bool _insert(pointer &t, value_type x)
	{
		pointer p = t;
		pointer pr = nullptr;

		stack<pointer> st;
		while (p != nullptr)
		{
			pr = p;
			st.push(pr);
			if (x < p->data)
			{
				p = p->leftchild;
			}
			else if (x > p->data)
			{
				p = p->rightchild;
			}
			else
			{
				return false;
			}
		}
		p = new AVLNode(x);
		if (pr == nullptr)
		{
			t = p;
			return true;
		}
		else if (x < pr->data)
		{
			pr->leftchild = p;
		}
		else if (x > pr->data)
		{
			pr->rightchild = p;
		}
		
		while (!st.empty())
		{
			pr = st.top();
			st.pop();
			if (p == pr->leftchild)
				pr->bf--;
			else if (p == pr->rightchild)
				pr->bf++;
			
			if (pr->bf == 0)
				break;
			else if (pr->bf == 1 || pr->bf == -1)
			{
				p = pr;
				continue;
			}
			else
			{
				if (pr->bf == 2)
				{
					if (p->bf == 1)
					{
						RotateL(pr);
					}
					else if (p->bf == -1)
					{
						RotateRL(pr);
					}
				}
				else if (pr->bf == -2)
				{
					if (p->bf == 1)
					{
						RotateLR(pr);
					}
					else if (p->bf == -1)
					{
						RotateR(pr);
					}
				}
				break;
			}
		}
		if (st.empty())
			t = pr;
		else
		{
			pointer q = st.top();
			if (pr->data < q->data)
				q->leftchild = pr;
			else
				q->rightchild = pr;

		}
		
	}
private:

	void RotateL(pointer &ptr)
	{
		pointer subL = ptr;
		ptr = subL->rightchild;
		subL->rightchild = ptr->leftchild;
		ptr->leftchild = subL;
		subL->bf = ptr->bf = 0;
	}
	void RotateR(pointer &ptr)
	{
		pointer subR = ptr;
		ptr = subR->leftchild;
		subR->leftchild = ptr->rightchild;
		ptr->rightchild = subR;
		subR->bf = ptr->bf = 0;
	}
	void RotateLR(pointer &ptr)
	{
		pointer subR = ptr;
		pointer subL = ptr->leftchild;
		ptr = subL->rightchild;
		subL->rightchild = ptr->leftchild;
		subR->leftchild = ptr->rightchild;
		ptr->leftchild = subL;
		ptr->rightchild = subR;
		
		if (ptr->bf == -1)
		{
			subL->bf = ptr->bf = 0;
			subR->bf = 1;
		}
		else if (ptr->bf == 1)
		{
			subR->bf = ptr->bf = 0;
			subL->bf = -1;
		}
		else if (ptr->bf == 0)
		{
			subR->bf = ptr->bf = subL->bf = 0;
		}
	}
	void RotateRL(pointer &ptr)
	{
		pointer subL = ptr;
		pointer subR = ptr->rightchild;
		ptr = subR->leftchild;
		subR->leftchild = ptr->rightchild;
		subL->rightchild = ptr->leftchild;
		ptr->leftchild = subL;
		ptr->rightchild = subR;
		
		if (ptr->bf == -1)
		{
			subR->bf = ptr->bf = 0;
			subL->bf = 1;
		}
		else if (ptr->bf == 1)
		{
			subL->bf = ptr->bf = 0;
			subR->bf = -1;
		}
		else if (ptr->bf == 0)
		{
			subR->bf = ptr->bf = subL->bf = 0;
		}
	}
private:
	pointer root;
};