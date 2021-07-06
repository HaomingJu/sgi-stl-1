
#ifndef __STL_CONFIG_H
# define __STL_CONFIG_H


# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __STL_PTHREADS
# endif

# if defined(_UITHREADS) && !defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __STL_UITHREADS
# endif






#   define __STL_DEFAULT_CONSTRUCTOR_BUG
#   ifdef __EXCEPTIONS
#   endif
#   ifdef _REENTRANT
#     define __STL_PTHREADS
#   endif


# if defined(__COMO__)
#   define __STL_MEMBER_TEMPLATES
#   define __STL_MEMBER_TEMPLATE_CLASSES
#   define __STL_TEMPLATE_FRIENDS
#   define __STL_CLASS_PARTIAL_SPECIALIZATION
#   define __STL_HAS_NAMESPACES
# endif

// Intel compiler, which uses the EDG front end.
# if defined(__ICL)
#   define __STL_LONG_LONG 
#   define __STL_MEMBER_TEMPLATES
#   define __STL_MEMBER_TEMPLATE_CLASSES
#   define __STL_TEMPLATE_FRIENDS
#   define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#   define __STL_CLASS_PARTIAL_SPECIALIZATION
#   define __STL_NO_DRAND48
#   define __STL_HAS_NAMESPACES
#   define __STL_MEMBER_TEMPLATE_KEYWORD
#   ifdef _CPPUNWIND
#   endif
#   ifdef _MT
#     define __STL_WIN32THREADS
#   endif
# endif

// Mingw32, egcs compiler using the Microsoft C runtime
# if defined(__MINGW32__)
#   define __STL_NO_DRAND48
#   ifdef _MT
#     define __STL_WIN32THREADS
#   endif
# endif

// Cygwin32, egcs compiler on MS Windows
# if defined(__CYGWIN__)
#   define __STL_NO_DRAND48
# endif




# if defined(__BORLANDC__)
#     define __STL_NO_BAD_ALLOC
#     define __STL_NO_DRAND48
#     define __STL_DEFAULT_CONSTRUCTOR_BUG
#   if __BORLANDC__ >= 0x540 /* C++ Builder 4.0 */
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#     define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#     define __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#     define __STL_MEMBER_TEMPLATES
#     define __STL_TEMPLATE_FRIENDS
#   else
#     define __STL_NEED_TYPENAME
#     define __STL_LIMITED_DEFAULT_TEMPLATES
#     define __SGI_STL_NO_ARROW_OPERATOR
#     define __STL_NON_TYPE_TMPL_PARAM_BUG
#   endif
#   ifdef _CPPUNWIND
#   endif
#   ifdef __MT__
#     define __STL_WIN32THREADS
#   endif
# endif

# if defined(__STL_NO_BOOL) && !defined(__STL_DONT_USE_BOOL_TYPEDEF)
    typedef int bool;
#   define true 1
#   define false 0
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

# ifdef __STL_NEED_EXPLICIT
#   define explicit
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

// Use standard-conforming allocators if we have the necessary language
// features.  __STL_USE_SGI_ALLOCATORS is a hook so that users can 
// disable new-style allocators, and continue to use the same kind of
// allocators as before, without having to edit library headers.
# if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) && \
     defined(__STL_MEMBER_TEMPLATES) && \
     defined(__STL_MEMBER_TEMPLATE_CLASSES) && \
    !defined(__STL_NO_BOOL) && \
    !defined(__STL_NON_TYPE_TMPL_PARAM_BUG) && \
    !defined(__STL_LIMITED_DEFAULT_TEMPLATES) && \
    !defined(__STL_USE_SGI_ALLOCATORS) 
#   define __STL_USE_STD_ALLOCATORS
# endif

# ifndef __STL_DEFAULT_ALLOCATOR
#   ifdef __STL_USE_STD_ALLOCATORS
#     define __STL_DEFAULT_ALLOCATOR(T) allocator< T >
#   else
#     define __STL_DEFAULT_ALLOCATOR(T) alloc
#   endif
# endif

// __STL_NO_NAMESPACES is a hook so that users can disable namespaces
// without having to edit library headers.  __STL_NO_RELOPS_NAMESPACE is
// a hook so that users can disable the std::rel_ops namespace, keeping 
// the relational operator template in namespace std, without having to 
// edit library headers.
# if defined(__STL_HAS_NAMESPACES) && !defined(__STL_NO_NAMESPACES)
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

// Some versions of the EDG front end sometimes require an explicit
// namespace spec where they shouldn't.  This macro facilitates that.
// If the bug becomes irrelevant, then all uses of __STD_QUALIFIER
// should be removed.  The 7.3 beta SGI compiler has this bug, but the
// MR version is not expected to have it.

# if defined(__STL_USE_NAMESPACES) && !defined(__STD_QUALIFIER)
#   define __STD_QUALIFIER std::
# else
#   define __STD_QUALIFIER
# endif

#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_THROW(x) throw x
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }

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

#if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) \
    && defined(__STL_MEMBER_TEMPLATES) \
    && !defined(_STL_NO_CONCEPT_CHECKS)
#  define __STL_USE_CONCEPT_CHECKS
#endif


#endif /* __STL_CONFIG_H */

// Local Variables:
// mode:C++
// End:
