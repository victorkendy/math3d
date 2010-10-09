#ifndef math3d_vector4
#define math3d_vector4 1

#include <string>
#include "math3d/core/core.h"
#include "math3d/core/math3d_plugin.h"
#include "math3d/math3d_base.h"

namespace math3d {
    class vector4 : public basicMath3dObject {
    public:
        vector4() {}
        vector4(const float4 & v) { getCurrent()->vecset(e, v); }
        vector4(float x, float y, float z, float w=0.0f) { getCurrent()->vecset(e, x,y,z,w); }
        vector4(const vector4 & v) { getCurrent()->vecset(this->e, v.e); }

        float minVal() const { return getCurrent()->vecminval(e); }
        float maxVal() const { return getCurrent()->vecmaxval(e); }

        friend const vector4 operator * (const float a, const vector4 & v);
        friend const vector4 operator / (const vector4 & v, const float a);
        friend const float   dot (const vector4 & v1, const vector4 & v2);
        friend const vector4 cross(const vector4 & v1, const vector4 & v2);
        friend const float   tripleProduct(const vector4 & v1, const vector4 & v2, const vector4 & v3);

        friend const vector4 Abs(const vector4 & v);
        friend const vector4 Max(const vector4 & v1, const vector4 & v2);
        friend const vector4 Min(const vector4 & v1, const vector4 & v2);

        float size() const { return getCurrent()->vecsize(e); }
        const vector4 & normalize() { getCurrent()->vecnormalize(e); return *this; }

        const vector4 operator - () const;
        const vector4 operator + () const { return vector4(e); }
        const vector4 operator + (const vector4 & v)const;
        const vector4 operator - (const vector4 & v)const;
        const vector4 operator * (const float a) const;

        const bool operator == (const vector4 & v) const {
            return getCurrent()->vecequal(e, v.e);
        }

        const vector4 & operator = (const vector4 & v) { getCurrent()->vecset(e, v.e); return *this; }
        operator float*()const { return (float *)&e[0]; }
        operator float4 &() { return e; }

        float & operator [] (int i) { return e[i]; }
        const float & operator [] (int i) const { return e[i]; }
        float4 & getElements() { return e; }

        const vector4 & operator += (const vector4 & v) { 
            getCurrent()->vecadd(this->e, v.e);
            return *this;
        }

        const vector4 & operator -= (const vector4 & v) {
            getCurrent()->vecsub(this->e, v.e);
            return *this;
        }

        const vector4 & operator *= (const float a) {
            getCurrent()->vecmul(this->e, a);
            return *this;
        }

        const vector4 & operator /= (const float a) {
            getCurrent()->vecdiv(this->e, a);
            return *this;
        }

        const std::string asString() const { return e.asString(); }
    private:
        float4 e;
    };

    // Implementations


    inline const vector4 operator * (const float a, const vector4 & v) {
        return v * a;
    }

    inline const vector4 operator / (const vector4 & v, const float a) {
        vector4 r;
        getCurrent()->vecdiv(getCurrent()->vecset(r.e, v.e), a);
        return r;
    }

    inline const float   dot (const vector4 & v1, const vector4 & v2) {
        return getCurrent()->vecdot(v1.e, v2.e);
    }

    inline const vector4 cross(const vector4 & v1, const vector4 & v2) {
        vector4 r;
        getCurrent()->veccross(getCurrent()->vecset(r.e, v1.e), v2.e);
        return r;
    }

    inline const float   tripleProduct(const vector4 & v1, const vector4 & v2, const vector4 & v3) {
        return getCurrent()->vectripleproduct(v1.e, v2.e, v3.e);
    }

    inline const vector4 Abs(const vector4 & v) {
        vector4 r;
        getCurrent()->vecabs(getCurrent()->vecset(r.e, v.e));
        return r;
    }

    inline const vector4 Max(const vector4 & v1, const vector4 & v2) {
        vector4 r;
        getCurrent()->vecmax(getCurrent()->vecset(r.e, v1.e), v2.e);
        return r;
    }

    inline const vector4 Min(const vector4 & v1, const vector4 & v2) {
        vector4 r;
        getCurrent()->vecmin(getCurrent()->vecset(r.e, v1.e), v2.e);
        return r;
    }

    inline const vector4 vector4::operator - () const {
        vector4 r;
        getCurrent()->vecmul(getCurrent()->vecset(r.e, e), -1.0f);
        return r;
    }

    inline const vector4 vector4::operator + (const vector4 & v)const {
        vector4 r;
        getCurrent()->vecadd(getCurrent()->vecset(r.e, e), v.e);
        return r;
    }

    inline const vector4 vector4::operator - (const vector4 & v)const {
        vector4 r;
        getCurrent()->vecsub(getCurrent()->vecset(r.e, e), v.e);
        return r;
    }

    inline const vector4 vector4::operator * (const float a) const {
        vector4 r;
        getCurrent()->vecmul(getCurrent()->vecset(r.e, e), a);
        return r;
    }

}
#endif

