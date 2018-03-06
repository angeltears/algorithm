#ifndef _DEQUE_H
#define _DEQUE_H

#define _DEQUEMAPSIZ	2
#define _DEQUESIZ (4096 < sizeof (_Ty) ? 1 : 4096 / sizeof (_Ty))

template<class _Ty, class _A=my_allocator<_Ty> >
class deque
{
public:
	typedef _A allocator_type;
	typedef _A::size_type       size_type;
	typedef _A::difference_type difference_type;
	typedef _A::value_type      value_type;
	typedef _A::pointer         pointer;
	typedef _A::pointer         _Tptr;
	typedef _A::const_pointer   const_pointer;
	typedef _A::reference       reference;
	typedef _A::const_reference const_reference;
	typedef _A::pointer*        _Mapptr;
public:
	class iterator
	{
		friend class deque<_Ty>;
	public:
		iterator()
		{}
		iterator(_Tptr _P, _Mapptr _M)
			:_First(*_M),_Last(*_M+_DEQUESIZ),_Next(_P),_Map(_M)
		{}
		reference operator*()const
		{
			return (*_Next); 
		}
		iterator& operator++()
		{
			if (++_Next == _Last)
			{
				_First = *++_Map;
				_Last = _First + _DEQUESIZ;
				_Next = _First; 
			}
			return (*this);
		}
		bool operator==(const iterator& _X) const
		{return (_Next == _X._Next); }
		bool operator!=(const iterator& _X) const
		{return (!(*this == _X)); }
	protected:
		pointer _First, _Last, _Next;
		_Mapptr _Map;
	};
public:
	explicit deque(const _A& _Al = _A())
		: allocator(_Al),_First(), _Last(), 
		_Map(0), _Mapsize(0),_Size(0)
	{}
public:
	size_type size()const
	{return _Size;}
	bool empty()const
	{return size() == 0;}
public:
	iterator begin()
	{
		return _First;
	}
	iterator end()
	{
		return _Last;
	}
public:
	void push_back(const _Ty &_X)
	{
		if(empty() || (_Last._Next == _Last._Last))
		{
			_Buyback();
			allocator.construct(_Last._Next++, _X);
		}
		else if(_Last._Next + 1 == _Last._Last)
        {
            allocator.construct(_Last._Next++, _X);
            _Buyback();
        }
        else
		{
            allocator.construct(_Last._Next++, _X);
		}
		++_Size;
	}
	void push_front(const _Ty& _X)
	{
		if (empty() || _First._Next == _First._First)
		{
			_Buyfront();
		}
		allocator.construct(--_First._Next, _X);
		++_Size; 
	}
protected:
	void _Getmap()
	{
		_Map = (_Mapptr)allocator._Charalloc(_Mapsize * sizeof (_Tptr));
	}
	void _Setptr(_Mapptr _M, _Tptr _P)
	{
		*_M = _P; 
	}
	_Mapptr _Growmap(size_type _Newsize)
	{
		_Mapptr _M = (_Mapptr)allocator._Charalloc(_Newsize * sizeof (_Tptr));
		copy(_First._Map, _Last._Map + 1,_M + _Newsize / 4);
		allocator.deallocate(_Map, _Mapsize);
		_Map = _M;
		_Mapsize = _Newsize;
		return (_M + _Newsize / 4); 
	}
	void _Buyback()
	{
		_Tptr _P = allocator.allocate(_DEQUESIZ, (void *)0);
		if (empty())
		{
			_Mapsize = _DEQUEMAPSIZ;
			size_type _N = _Mapsize / 2;
			_Getmap();
			_Setptr(_Map + _N, _P);
			_First = iterator(_P + _DEQUESIZ / 2, _Map + _N);
			_Last = _First; 
		}
		else if (_Last._Map < _Map + (_Mapsize - 1))
		{
			_Setptr(++_Last._Map, _P);
			_Last = iterator(_P, _Last._Map); 
		}
		else
		{
			difference_type _I = _Last._Map - _First._Map + 1;
			_Mapptr _M = _Growmap(2 * _I);
			_Setptr(_M + _I, _P);
			_First = iterator(_First._Next, _M);
			_Last = iterator(_P, _M + _I); 
		}
	}
	void _Buyfront()
	{
		_Tptr _P = allocator.allocate(_DEQUESIZ, (void *)0);
		if (empty())
		{
			_Mapsize = _DEQUEMAPSIZ;
			size_type _N = _Mapsize / 2;
			_Getmap();
			_Setptr(_Map + _N, _P);
			_First = iterator(_P + (_DEQUESIZ / 2 + 1),	_Map + _N);
			_Last = _First; 
		}
		else if (_Map < _First._Map)
		{
			_Setptr(--_First._Map, _P);
			_First = iterator(_P + _DEQUESIZ, _First._Map);
		}
		else if (_Last._Map == _First._Map)
		{
			_Setptr(_Last._Map++, *_First._Map);
			_Setptr(_First._Map+1, *_First._Map);
			_Setptr(_First._Map, _P);
			_First = iterator(_P + _DEQUESIZ, _First._Map); 
		}
		else
		{
			difference_type _I = _Last._Map - _First._Map + 1;
			_Mapptr _M = _Growmap(2 * _I);
			_Setptr(--_M, _P);
			_First = iterator(_P + _DEQUESIZ, _M);
			_Last = iterator(_Last._Next, _M + _I); 
		}
	}
private:
	_A allocator;
	iterator _First;
	iterator _Last;
	_Mapptr _Map;
	size_type _Mapsize;
	size_type _Size;
};

#endif