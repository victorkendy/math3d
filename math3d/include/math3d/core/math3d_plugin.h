

#ifndef math3d_plugin
#define math3d_plugin 1

#include <cstdlib>
#include <cstdio>
#include <string>


#ifdef _MSC_VER
    // Disable the deprecation warning for sprintf on VS
    #pragma warning(disable: 4996)
#endif

namespace math3d {
#ifdef __GNUG__    
    struct _vector {
        inline _vector(){}
        inline _vector(const float x, const float y, const float z, const float w) {
            e[0] = x; e[1] = y; e[2] = z; e[3] = w;
        }
        inline const float & operator [] (int index) const {
            return e[index];
        }
        inline float & operator [] (int index) {
            return e[index];
        }

        inline operator float*()const { return (float *)e; }

        inline const _vector & operator=(const _vector & v) {
            e[0] = v[0]; e[1] = v[1]; e[2] = v[2]; e[3] = v[3];
            return *this;
        }

        inline const std::string asString() const {
            std::string r;
            char buffer[100];
            sprintf(buffer, "(%f, %f, %f, %f)", e[0], e[1], e[2], e[3]);
            r = std::string(buffer);
            return r;
        }

        float e[4];
    };
    typedef struct _vector __attribute__((aligned(16))) float4;
#else
#include <xmmintrin.h>
    struct _vector {
        inline _vector() {}
        inline _vector(const float x, const float y, const float z, const float w) {
            e.m128_f32[0] = x; e.m128_f32[1] = y; e.m128_f32[2] = z; e.m128_f32[3] = w;
        }
        inline const float & operator [] (int index) const {
            return e.m128_f32[index];
        }
        inline float & operator [] (int index) {
            return e.m128_f32[index];
        }
        
        inline operator float*()const { return (float *)&e; }

        inline const _vector & operator=(const _vector & v) {
            e.m128_f32[0] = v[0]; e.m128_f32[1] = v[1]; e.m128_f32[2] = v[2]; e.m128_f32[3] = v[3];
            return *this;
        }

        inline const std::string asString() const {
            std::string r;
            char buffer[100];
            sprintf(buffer, "(%f, %f, %f, %f)", e.m128_f32[0], e.m128_f32[1], e.m128_f32[2], e.m128_f32[3]);
            r = std::string(buffer);
            return r;
        }

        __m128 e;
    };

    typedef struct _vector float4;
#endif

    class math3dImplementation {
    public:
    // Functions for 4 dimension vectors
        virtual float4 & vecset(float4 & v, const float v0, const float v1, const float v2, const float v3);
        virtual float4 & vecset(float4 & dest, const float4 & source);
        virtual float4 & vecadd(float4 & v1, const float4 & v2);
        virtual float4 & vecsub(float4 & v1, const float4 & v2);
        virtual float4 & vecdiv(float4 & v, const float & a);
        virtual float4 & vecmul(float4 & v, const float & a);

        virtual float4 & veccross(float4 & v1, const float4 & v2);
        virtual float4 & vecnormalize(float4 & v);
        virtual float4 & vecabs(float4 & v);
        virtual float4 & vecmax(float4 & v1, const float4 & v2);
        virtual float4 & vecmin(float4 & v1, const float4 & v2);
        virtual float4 & vecreflect(float4 & v, const float4 & n);

        virtual const float  vecsize(const float4 & v);
        virtual const float  vecdot(const float4 & v1, const float4 & v2);
        virtual const float  vecminval(const float4 & v);
        virtual const float  vecmaxval(const float4 & v);
        virtual const float  vectripleproduct(const float4 & v1, const float4 & v2, const float4 & v3);

        virtual const bool   vecequal(const float4 & v1, const float4 & v2);
    // Functios for quaternions
        virtual float4 & qinverse(float4 & q);
        virtual float4 & qmul(float4 & q1, const float4 & q2);
        virtual float4 & qconjugate(float4 & q);
    // Functions for 4x4 matrices
        // perform a * b store result in a
        virtual void m44mul(float4 a[4], const float4 b[4]);
        virtual float4& m44mulvec(float4 & a, const float4 m[4]);
        virtual void m44inv(float4 a[4]);
        virtual void m44identity(float4 a[4]);
        virtual void m44transpose(float4 a[4]);
    // Type conversion
        virtual void cvtqtom44(const float4 & q, float4 m44[4]);

    // Auxiliary Functions matrix utils
        virtual void createm44ortho(float4 m[4], const float & left, const float & right, 
                                                 const float & bottom, const float & top, 
                                                 const float & near, const float & far);
    // Batch operations
        virtual void batchm44mul(float4 m[], const float4 base[4], const int numMatrices);

    // Print information
        virtual const std::string getName() const;
    };

}

#endif

