
#include "math3d/core/math3d_plugin_sse.h"

#ifndef math3d_plugin_sse3_h
#define math3d_plugin_sse3_h 1



namespace math3d {
    class sse3Implementation: public sseImplementation {

    public:
#if _MSC_VER > 1400 || !defined(_MSC_VER)
        virtual float4 & vecnormalize(float4 & v);
        
        virtual const float vecdot(const float4 & v1, const float4 & v2);

        virtual float4 & qinverse(float4 & q);

        virtual float4 & qmul(float4 & q1, const float4 & q2);

        virtual float4& m44mulvec(float4 & a, const float4 m[4]);

        virtual void cvtqtom44(const float4 & q, float4 m44[4]);

#endif
        virtual const std::string getName() const;

    };
}


#endif 

