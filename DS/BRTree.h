#pragma once
#include <stack>
#include <iostream>
using namespace std;
typedef enum { RED = 0, BLACK } COLOR;

template<class Type>
class RBTree
{
	class RBNode
	{
	public:
		typedef RBNode* pointer;
		typedef const RBNode* const_pointer;
		friend class RBTree;
	public:
		RBNode() :data(Type()), color(RED), leftchild(nullptr), rightchild(nullptr),parent(nullptr) {}
		RBNode(Type d, pointer left = nullptr, pointer right = nullptr, pointer pf = nullptr ) :
			data(d), color(RED), leftchild(left), rightchild(right), parent(pf) {}
		~RBNode() {};
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
		Type data;
		pointer leftchild;
		pointer rightchild;
		pointer parent;
		COLOR color;
	};
public:
	typedef RBNode*					pointer;
	typedef const RBNode*			const_pointer;
	typedef Type					value_type;
	RBTree() : root(NULL){}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
	bool Remove(const Type &x)
	{
		return Remove(root, x);
	}
private:
	bool Remove(pointer t, const Type &x)
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
		if (p->leftchild != nullptr && p->rightchild != nullptr)
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
		{
			t = p;
			p->color = RED;
		}
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
				if (p->color == RED)
					break;
				else
				{
					if (q != nullptr && q->color == RED)
					{
						q->color = BLACK;
					}
					else if(pr->rightchild == q)
					{
						if (pr->leftchild->color == BLACK)
						{
							if (pr->leftchild->leftchild != nullptr
								&& pr->leftchild->leftchild->color == RED)
							{
								pr->color = BLACK;
								pr->leftchild->color = RED;
								pr->leftchild->leftchild->color = BLACK;
								RotateR(pr);
							}
							else if((pr->leftchild->leftchild == nullptr) ||
								(pr->leftchild->leftchild != nullptr &&
									pr->leftchild->leftchild->color != RED))
							{
								if (pr->leftchild->rightchild != nullptr
									&& pr->leftchild->rightchild->color == RED)
								{
									pr->color = BLACK;
									RotateL(pr->leftchild);
									RotateR(pr);
								}
								else if (pr->color == RED)
								{
									pr->color = BLACK;
									pr->leftchild->color = RED;
								}
								else
								{
									pr->color = RED;
									RotateR(pr);
								}
							}
						}
						else
						{	
							if (pr->leftchild->rightchild != nullptr)
							{
								if (pr->leftchild->rightchild->leftchild != nullptr
									&& pr->leftchild->rightchild->leftchild->color == RED)
								{
									pr->leftchild->rightchild->leftchild->color = BLACK;
									RotateL(pr->leftchild);
									RotateR(pr);
								}
								else if (pr->leftchild->rightchild->leftchild == nullptr || pr->leftchild->rightchild->leftchild->color == BLACK)
								{
									if (pr->leftchild->rightchild->rightchild != nullptr
										&& pr->leftchild->rightchild->rightchild->color == RED)
									{
										pr->leftchild->rightchild->rightchild->color = BLACK;
										RotateL(pr->leftchild->rightchild);
										RotateL(pr->leftchild);
										RotateR(pr);
									}
									else
									{
										RotateR(pr);
									}
								}
							}
						}
					}
					else if (pr->leftchild == q)
					{
						if (pr->rightchild->color == BLACK)
						{
							if (pr->rightchild->rightchild != nullptr && pr->rightchild->rightchild->color == RED)
							{
								pr->color = BLACK;
								pr->rightchild->rightchild->color = BLACK;
								pr->rightchild->color = RED;
								RotateL(pr);
							}
							else if ( pr->rightchild->rightchild == nullptr || pr->rightchild->rightchild->color != RED)
							{

								if (pr->rightchild->leftchild != nullptr && pr->rightchild->leftchild->color == RED)
								{
									pr->color = BLACK;
									RotateL(pr->leftchild);
									RotateR(pr);
								}
								else if (pr->color == RED)
								{
									pr->color = BLACK;
									pr->rightchild->color = RED;
								}
								else
								{
									pr->color = RED;
									RotateR(pr);
								}
							}
							else
							{
								if (pr->rightchild->leftchild != nullptr)
								{
									if (pr->rightchild->leftchild->rightchild != nullptr
										&& pr->rightchild->leftchild->rightchild->color == RED)
									{
										pr->rightchild->leftchild->rightchild->color = BLACK;
										RotateR(pr->rightchild);
										RotateL(pr);
									}
									else if (pr->rightchild->leftchild->rightchild == nullptr || pr->rightchild->leftchild->rightchild->color == BLACK)
									{
										if (pr->rightchild->leftchild->leftchild != nullptr
											&& pr->rightchild->leftchild->leftchild->color == RED)
										{
											pr->rightchild->leftchild->leftchild->color = BLACK;
											RotateR(pr->rightchild->leftchild);
											RotateR(pr->rightchild);
											RotateL(pr);
										}
										else
										{
											RotateL(pr);
										}
									}
								}
							}
						}
					}
					break;
				}
			}
			if (st.empty())
				t = pr;
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
	bool Insert(pointer t, const Type &v)
	{
		pointer p = t;
		pointer pr = nullptr;
		while (p != NULL)
		{
			if (v == p->data)
				return false;
			pr = p;
			if (v < p->data)
				p = p->leftchild;
			else
				p = p->rightchild;
		}
		pointer x = new RBNode(v);
		x->parent = pr;
		if (pr == NULL)
		{
			t = x;
			t->color = BLACK;
			root = t;
			return true;
		}
		if (pr->data > x->data)
			pr->leftchild = x;
		else
			pr->rightchild = x;

		_Insert_Fixup(t, x);
		return true;
	}
private:
	void _Insert_Fixup(pointer &t, pointer x)
	{
		pointer s;
		while (x->parent->color == RED)
		{
			if (x->parent == x->parent->parent->leftchild)
			{
				s = x->parent->parent->rightchild;
				if ((s == nullptr && x == x->parent->leftchild) ||
					(s != nullptr && s->color == BLACK && x == x->parent->leftchild))
				{
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					RotateR(x->parent->parent);
					break;
				}
				else if ((s == nullptr && x == x->parent->rightchild) ||
					(s != nullptr && s->color == BLACK && x == x->parent->rightchild))
				{
					x->parent->parent->color = RED;
					x->color = BLACK;
					RotateL(x->parent);
					RotateR(x->parent);
					break;
				}
				else if (s != nullptr && s->color == RED &&x == x->parent->leftchild)
				{
					x->color = BLACK;
					RotateR(x->parent->parent);
					if (x->parent->parent != nullptr && x->parent->parent->color == RED)
					{
						x = x->parent;
						continue;
					}
					else
					{
						if (x->parent->parent == nullptr)
							x->parent->color = BLACK;
						break;
					}
				}
				else if(s != nullptr && s->color == RED &&x == x->parent->rightchild)
				{
					x = x->parent;
					RotateL(x);
					x->color = BLACK;
					RotateR(x->parent->parent);
					if (x->parent->parent != nullptr && x->parent->parent->color == RED)
					{
						x = x->parent;
						continue;
					}
					else
					{
						if (x->parent->parent == nullptr)
							x->parent->color = BLACK;
						break;
					}
				}
			}
			else
			{
				s = x->parent->parent->leftchild;
				if ((s == nullptr && x == x->parent->rightchild) ||
					(s != nullptr && s->color == BLACK && x == x->parent->rightchild))
				{
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					RotateL(x->parent->parent);
					break;
				}
				else if ((s == nullptr && x == x->parent->leftchild) ||
					(s != nullptr && s->color == BLACK && x == x->parent->leftchild))
				{
					x->parent->parent->color = RED;
					x->color = BLACK;
					RotateR(x->parent);
					RotateL(x->parent);
					break;
				}
				else if (s != nullptr && s->color == RED &&x == x->parent->rightchild)
				{
					x->color = BLACK;
					RotateL(x->parent->parent);
					if (x->parent->parent != nullptr && x->parent->parent->color == RED)
					{
						x = x->parent;
						continue;
					}
					else
					{
						if (x->parent->parent == nullptr)
							x->parent->color = BLACK;
						break;
					}
				}
				else if (s != nullptr && s->color == RED &&x == x->parent->leftchild)
				{
					x = x->parent;
					RotateR(x);
					x->color = BLACK;
					RotateL(x->parent->parent);
					if (x->parent->parent != nullptr && x->parent->parent->color == RED)
					{
						x = x->parent;
						continue;
					}
					else
					{
						if (x->parent->parent == nullptr)
							x->parent->color = BLACK;
						break;
					}
				}
			}
		}

	}
private:
	void RotateR(pointer ptr)
	{
		pointer subR = ptr;
		ptr = subR->leftchild;
		if (ptr->rightchild != nullptr)
			ptr->rightchild->parent = subR;
		subR->leftchild = ptr->rightchild;
		if (subR->parent == nullptr)
		{
			root = ptr;
			ptr->parent = nullptr;
		}
		else
		{
			if (subR == subR->parent->leftchild)
				subR->parent->leftchild = ptr;
			else
				subR->parent->rightchild = ptr;
			ptr->parent = subR->parent;
		}
		subR->parent = ptr;
		ptr->rightchild = subR;
	}
	void RotateL(pointer ptr)
	{
		pointer subL = ptr;
		ptr = subL->rightchild;

		if (ptr->leftchild != nullptr)
			ptr->leftchild->parent = subL;
		subL->rightchild = ptr->leftchild;

		if (subL->parent == nullptr)
		{
			root = ptr;
			ptr->parent = nullptr;
		}
		else
		{
			if (subL == subL->parent->leftchild)
				subL->parent->leftchild = ptr;
			else
				subL->parent->rightchild = ptr;
				ptr->parent = subL->parent;
		}
		subL->parent = ptr;
		ptr->leftchild = subL;
	}
private:
	pointer root;
};