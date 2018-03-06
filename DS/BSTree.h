#pragma once
#include <iostream>
using std::cout;
using std::endl;

template<class Type>
class BSTree
{
	class BSNode
	{
	public:
		typedef BSNode* pointer;
		typedef const BSNode* const_pointer;
		friend class BSTree;
	public:
		BSNode() :data(Type()), leftchild(nullptr), rightchild(nullptr){}
		BSNode(Type d, pointer left = nullptr, pointer right = nullptr) :
			data(d), leftchild(left), rightchild(right) {}
		~BSNode() {};
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
	};
public:
	typedef BSNode*					pointer;
	typedef const BSNode*			const_pointer;
	typedef Type					value_type;
	typedef BSNode&                 reference;
	typedef const BSNode&           const_reference;
	typedef size_t                  size_type;
public:
	BSTree() :root(nullptr) {}
	BSTree(Type ar[], size_type n) : root(nullptr)
	{
		for (size_type i = 0; i < n; i++)
		{
			insert(ar[i]);
		}
	}
	~BSTree()
	{
		MakeEmpty();
	}
public:
	bool insert(value_type &x)
	{
		return _insert(root, x);
	}
	void sort()const
	{
		_sort(root);
	}
	bool remove(const value_type &key)
	{
		return _remove(root, key);
	}
	pointer Max()const
	{
		return _max(root);
	}
	pointer Min()const
	{
		return _min(root);
	}
	pointer Find(value_type &key)const
	{
		return _find(root, key);
	}
	pointer Find(value_type key)const
	{
		return _find(root, key);
	}
	pointer Parent(pointer p)const
	{
		return _parent(root, root, p);
	}
	void MakeEmpty()
	{
		_makeEmpty(root);
	}
	bool Copy(pointer &t)  //bst1.Copy(bst2);
	{
		return _copy(root, t);
	}
	BSTree& operator=(BSTree &t) //bst1 = bst2;
	{
		MakeEmpty();
		Copy(t.root);
		return *this;
	}
private:
	bool _copy(pointer &t,pointer &p)
	{
		if (p != nullptr)
		{
			if (t == nullptr)
			{
				t = new BSNode;
			}
			_copy(t->leftchild,p->leftchild);
			t->data = p->data;
			_copy(t->rightchild,p->rightchild);
		}
		else
		{
			return false;
		}
		return true;
	}
	void _makeEmpty(pointer &t)
	{
		if (t == nullptr)
		{
			return;
		}
		else
		{
			while(t->leftchild != nullptr)
			{
				_makeEmpty(t->leftchild);
			}
			while(t->rightchild != nullptr)
			{
				_makeEmpty(t->rightchild);
			}
			if (t->rightchild == nullptr &&  t->leftchild == nullptr)
			{
				delete t;
				t = nullptr;
			}
		}
	}
	pointer _parent(pointer t,pointer p, pointer key)const
	{
		if (t != nullptr)
		{ 
			if (t->data < key->data)
			{
				p = t;
				_parent(t->rightchild, p, key);
			}
			else if (t->data > key->data)
			{
				p = t;
				_parent(t->leftchild, p, key);
			}
			else
			{
				return p;
			}
		}
		else
		{
			return nullptr;
		}
	}
	pointer _find(pointer t, value_type &key)const
	{
		if (t != nullptr)
		{
			if (t->data < key)
			{
				_find(t->rightchild, key);
			}
			else if (t->data > key)
			{
				_find(t->leftchild, key);
			}
			else
			{
				return t;
			}
		}
		else
		{
			return nullptr;
		}
	}
	pointer  _max(pointer t) const
	{
		if (t == nullptr)
			return nullptr;
		while (t->rightchild)
			t = t->rightchild;
		return t;
	}
	pointer  _min(pointer t) const
	{
		if (t == nullptr)
			return nullptr;
		while (t->leftchild)
			t = t->leftchild;
		return t;
	}
	bool _remove(pointer &_t, const value_type &_key)
	{
		if (_t != nullptr)
		{
			if (_t->data < _key)
			{
				return _remove(_t->rightchild, _key);
			}
			else if (_t->data > _key)
			{
				return _remove(_t->leftchild, _key);
			}
			else 
			{
				pointer tmp;
				if (!_t->leftchild)
				{
					tmp = _t;
					_t = _t->rightchild;
					delete tmp;
				}
				else if (!_t->rightchild)
				{
					tmp = _t;
					_t = _t->leftchild;
					delete tmp;
				}
				else
				{
					tmp = _t;
					pointer _s = _t->leftchild;
					while (_s->rightchild)
					{
						tmp = _s;
						_s = _s->rightchild;
					}
					_t->data = _s->data;
					if (tmp != _t)
					{
						tmp->rightchild = _s->leftchild;
					}
					else
					{
						_t->leftchild = _s->leftchild;
					}
					delete _s;
				}
				return true;
			}
		}
		return false;
	}
	void _sort(pointer _t) const
	{
		if (_t != nullptr)
		{
			_sort(_t->leftchild);
			cout <<_t->data << " ";
			_sort(_t->rightchild);
		}
	}
	bool _insert(pointer &_t, value_type &_x)
	{
		if (_t == nullptr)
		{
			_t = new BSNode(_x);
			return true;
		}
		else
		{
			if (_t->data > _x)
			{
				return _insert(_t->leftchild, _x);
			}
			else if (_t->data < _x)
			{
				return _insert(_t->rightchild, _x);
			}
			else
			{
				return false;
			}
		}
	}
private:
	pointer root;
};