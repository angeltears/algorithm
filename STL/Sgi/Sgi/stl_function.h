#pragma once
template<class _Arg, class _Result>
struct unary_function
{
	typedef _Arg            argument_type;
	typedef _Result         result_type;
};

template <class _Arg1, class _Arg2, class _Result>
struct binary_function 
{
	typedef _Arg1			first_argument_type;
	typedef _Arg2			second_argument_type;
	typedef _Result			result_type;
};

template <class _Tp>
struct greater : public binary_function<_Tp, _Tp, bool>
{
	bool operator()(const _Tp& __x, const _Tp& __y)
	{
		return __x < __y;
	}
};

template <class _Tp>
struct less : public binary_function<_Tp, _Tp, bool>
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
	{
		return __x < __y;
	}
};

template<class _Tp>
struct equal_to : public binary_function<_Tp, _Tp, bool>
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
	{
		return __x == __y;
	}
};

template<class _Tp>
struct not_equal_to : public binary_function<_Tp, _Tp, bool>
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
	{
		return __x != __y;
	}
};

template <class T>
struct identity : public unary_function<T, T>
{
	const T& operator()(const T& x) const 
	{ 
		return x; 
	}
};
