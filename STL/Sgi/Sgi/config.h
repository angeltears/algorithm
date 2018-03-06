#pragma once
/* 
this config just use in MSC
just for using functions;
*/
# if defined(_MSC_VER) && !defined(__ICL) && !defined(__MWERKS__)
#   define __STL_NO_DRAND48
#   define __STL_STATIC_CONST_INIT_BUG
#   define __STL_NEED_TYPENAME
#   define __STL_NO_USING_CLAUSE_IN_CLASS
#   define __STL_NO_FRIEND_TEMPLATE_CLASS
#   if _MSC_VER < 1100  /* 1000 is version 4.0, 1100 is 5.0, 1200 is 6.0. */
#     define __STL_NEED_EXPLICIT
#     define __STL_NO_BOOL
#     define __STL_NO_BAD_ALLOC
#   endif
#   if _MSC_VER > 1000
#     include <yvals.h>
#     define __STL_DONT_USE_BOOL_TYPEDEF
#   endif
#   define __STL_NON_TYPE_TMPL_PARAM_BUG
#   define __SGI_STL_NO_ARROW_OPERATOR
#   define __STL_DEFAULT_CONSTRUCTOR_BUG
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define __STL_WIN32THREADS
#   endif
#   if _MSC_VER >= 1200
#     define __STL_PARTIAL_SPECIALIZATION_SYNTAX
#     define __STL_HAS_NAMESPACES
#     define __STL_CAN_THROW_RANGE_ERRORS
#     define NOMINMAX
#     undef min
#     undef max
// disable warning 'initializers put in unrecognized initialization area'
#     pragma warning ( disable : 4075 )
// disable warning 'empty controlled statement found'
#     pragma warning ( disable : 4390 )
// disable warning 'debug symbol greater than 255 chars'
#     pragma warning ( disable : 4786 )
#   endif
#   if _MSC_VER < 1100
#     define __STL_NO_EXCEPTION_HEADER
#     define __STL_NO_BAD_ALLOC
#   endif
// Because of a Microsoft front end bug, we must not provide a
// namespace qualifier when declaring a friend function.
#   define __STD_QUALIFIER
# endif


# ifdef __STL_NEED_TYPENAME
#   define typename
# endif

# ifdef __STL_LIMITED_DEFAULT_TEMPLATES
#   define __STL_DEPENDENT_DEFAULT_TMPL(_Tp)
# else
#   define __STL_DEPENDENT_DEFAULT_TMPL(_Tp) = _Tp
# endif

# ifdef __STL_MEMBER_TEMPLATE_KEYWORD
#   define __STL_TEMPLATE template
# else
#   define __STL_TEMPLATE
# endif

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __STL_NULL_TMPL_ARGS <>
# else
#   define __STL_NULL_TMPL_ARGS
# endif

# if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) \
     || defined (__STL_PARTIAL_SPECIALIZATION_SYNTAX)
#   define __STL_TEMPLATE_NULL template<>
# else
#   define __STL_TEMPLATE_NULL
# endif

# ifndef __STL_DEFAULT_ALLOCATOR
#   ifdef __STL_USE_STD_ALLOCATORS
#     define __STL_DEFAULT_ALLOCATOR(T) allocator< T >
#   else
#     define __STL_DEFAULT_ALLOCATOR(T) alloc
#   endif
# endif

#if defined(__STL_HAS_NAMESPACES) && !defined(__STL_NO_NAMESPACES)
#   define __STL_USE_NAMESPACES
#   define __STD std
#   define __STL_BEGIN_NAMESPACE namespace std {
#   define __STL_END_NAMESPACE }
#   if defined(__STL_FUNCTION_TMPL_PARTIAL_ORDER) && \
       !defined(__STL_NO_RELOPS_NAMESPACE)
#     define __STL_USE_NAMESPACE_FOR_RELOPS
#     define __STL_BEGIN_RELOPS_NAMESPACE namespace std { namespace rel_ops {
#     define __STL_END_RELOPS_NAMESPACE } }
#     define __STD_RELOPS std::rel_ops
#   else /* Use std::rel_ops namespace */
#     define __STL_USE_NAMESPACE_FOR_RELOPS
#     define __STL_BEGIN_RELOPS_NAMESPACE namespace std {
#     define __STL_END_RELOPS_NAMESPACE }
#     define __STD_RELOPS std
#   endif /* Use std::rel_ops namespace */
# else
#   define __STD 
#   define __STL_BEGIN_NAMESPACE 
#   define __STL_END_NAMESPACE 
#   undef  __STL_USE_NAMESPACE_FOR_RELOPS
#   define __STL_BEGIN_RELOPS_NAMESPACE 
#   define __STL_END_RELOPS_NAMESPACE 
#   define __STD_RELOPS 
#   undef  __STL_USE_NAMESPACES
# endif



# if defined(__STL_USE_NAMESPACES) && !defined(__STD_QUALIFIER)
#   define __STD_QUALIFIER std::
# else
#   define __STD_QUALIFIER
# endif

# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_THROW(x) throw x
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }
# else
#   define __STL_TRY 
#   define __STL_CATCH_ALL if (false)
#   define __STL_THROW(x) 
#   define __STL_RETHROW 
#   define __STL_NOTHROW 
#   define __STL_UNWIND(action) 
# endif

#ifdef __STL_ASSERTIONS
# include <stdio.h>
# define __stl_assert(expr) \
    if (!(expr)) { fprintf(stderr, "%s:%d STL assertion failure: %s\n", \
			  __FILE__, __LINE__, # expr); abort(); }
#else
# define __stl_assert(expr)
#endif

#if defined(__STL_WIN32THREADS) || defined(__STL_SGI_THREADS) \
    || defined(__STL_PTHREADS)  || defined(__STL_UITHREADS)
#   define __STL_THREADS
#   define __STL_VOLATILE volatile
#else
#   define __STL_VOLATILE
#endif