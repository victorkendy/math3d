#include "math3d/core/math3d_plugin.h"

#ifndef math3d_plugin_sse_h
#define math3d_plugin_sse_h 1

namespace math3d {
    class sseImplementation: public math3dImplementation {
    public:
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

//        virtual const float4 vecreflect(const float4 & v, const float4 & n);

        virtual const float vecsize(const float4 & v);

        virtual const float vecdot(const float4 & v1, const float4 & v2);

        virtual const float vecminval(const float4 & v);

        virtual const float vecmaxval(const float4 & v);


        virtual float4 & qinverse(float4 & q);

        virtual float4 & qmul(float4 & q1, const float4 & q2);

        virtual float4 & qconjugate(float4 & q);

        virtual void m44mul(float4 a[4], const float4 b[4]);

        virtual float4& m44mulvec(float4 & a, const float4 m[4]);

        virtual void m44inv(float4 a[4]);

        virtual void m44identity(float4 a[4]);

        virtual void cvtqtom44(const float4 & q, float4 m44[4]);


        virtual void batchm44mul(float4 m[], const float4 base[4], const int numMatrices);

        virtual const std::string getName() const;

    };
}

#endif 

