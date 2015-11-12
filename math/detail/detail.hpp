#ifndef DETAIL_INCLUDED_738ADE13_1093_4593_AF81_2F9CB58DAE42
#define DETAIL_INCLUDED_738ADE13_1093_4593_AF81_2F9CB58DAE42


#ifdef MATH_ENABLE_SIMD
#define MATH_NO_SIMD
#endif

#ifdef MATH_FORCE_INLINE
#define MATH_INLINE __forceinline
#else
#define MATH_INLINE inline
#endif

#define MATH_MAT4_INLINE inline


#endif // include guard