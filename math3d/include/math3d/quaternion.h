

#ifndef math3d_quaternion
#define math3d_quaternion 1

#include <string>
#include "math3d/core/core.h"
#include "math3d/math3d_base.h"
#include "math3d/matrix44.h"

namespace math3d{

    class quaternion : public basicMath3dObject{
    public:
        quaternion() {}
        quaternion(const float4 & q) { getCurrent()->vecset(e, q); }
        quaternion(const quaternion & q) { getCurrent()->vecset(e, q.e); }
        quaternion(const float x, const float y, const float z, const float w) { getCurrent()->vecset(e, x,y,z,w); }

        friend const quaternion operator * (const float a, const quaternion & q);
        friend const quaternion operator / (const quaternion & q, const float a);

        float size() const;
        const quaternion & normalize();
        const quaternion conjugate() const;
        const quaternion inverse() const;
        const matrix44 toMatrix() const;

        const quaternion operator - () const;
        const quaternion operator + () const;
        const quaternion operator + (const quaternion & q) const;
        const quaternion operator - (const quaternion & q) const;
        const quaternion operator * (const quaternion & q) const;
        const quaternion operator * (const float a) const;

        const bool operator == (const quaternion & q) const;

        const quaternion & operator = (const quaternion & q);
        operator float * () const;

        float & operator [] (int i);
        const float & operator [] (int i) const;

        const quaternion & operator += (const quaternion & q);
        const quaternion & operator -= (const quaternion & q);
        const quaternion & operator *= (const quaternion & q);
        const quaternion & operator *= (const float a);
        const quaternion & operator /= (const float a);

        const std::string asString() const;
    private:
        float4 e;
    };

    // Implementation

     inline const quaternion operator * (const float a, const quaternion & q) {
         return q * a;
     }

     inline const quaternion operator / (const quaternion & q, const float a) {
         quaternion r;
         getCurrent()->vecdiv(getCurrent()->vecset(r.e, q.e), a);
         return r;
     }

     inline float quaternion::size() const {
         return getCurrent()->vecsize(e);
     }

     inline const quaternion & quaternion::normalize() {
         getCurrent()->vecnormalize(e);
         return *this;
     }

     inline const quaternion quaternion::conjugate() const {
         quaternion r;
         getCurrent()->qconjugate(getCurrent()->vecset(r.e, e));
         return r;
     }

     inline const quaternion quaternion::inverse() const {
         quaternion r;
         getCurrent()->qinverse(getCurrent()->vecset(r.e, e));
         return r;
     }

     inline const matrix44 quaternion::toMatrix() const {
         matrix44 m;
         getCurrent()->cvtqtom44(this->e, m);
         return m;
     }

     inline const quaternion quaternion::operator - () const {
         quaternion q;
         getCurrent()->vecmul(getCurrent()->vecset(q.e, e), -1.0f);
         return q;
     }

     inline const quaternion quaternion::operator + () const {
         quaternion q;
         getCurrent()->vecset(q.e, e);
         return q;
     }

     inline const quaternion quaternion::operator + (const quaternion & q) const {
         quaternion r;
         getCurrent()->vecadd(getCurrent()->vecset(r.e, e), q.e);
         return r;
     }

     inline const quaternion quaternion::operator - (const quaternion & q) const {
         quaternion r;
         getCurrent()->vecsub(getCurrent()->vecset(r.e, e), q.e);
         return r;
     }

     inline const quaternion quaternion::operator * (const quaternion & q) const {
         quaternion r;
         getCurrent()->qmul(getCurrent()->vecset(r.e, e), q.e);
         return r;
     }

     inline const quaternion quaternion::operator * (const float a) const {
         quaternion r;
         getCurrent()->vecmul(getCurrent()->vecset(r.e, e), a);
         return r;
     }

     inline const bool quaternion::operator == (const quaternion & q) const {
         return getCurrent()->vecequal(e, q.e);
     }

     inline const quaternion & quaternion::operator = (const quaternion & q) {
         getCurrent()->vecset(e, q.e);
         return *this;
     }

     inline quaternion::operator float * () const {
         return (float*)e;
     }

     inline float & quaternion::operator [] (int i) {
         return e[i];
     }

     inline const float & quaternion::operator [] (int i) const {
         return e[i];
     }

     inline const quaternion & quaternion::operator += (const quaternion & q) {
         getCurrent()->vecadd(e, q.e);
         return *this;
     }

     inline const quaternion & quaternion::operator -= (const quaternion & q) {
         getCurrent()->vecsub(e, q.e);
         return *this;
     }

     inline const quaternion & quaternion::operator *= (const quaternion & q) {
         getCurrent()->qmul(e, q.e);
         return *this;
     }

     inline const quaternion & quaternion::operator *= (const float a) {
         getCurrent()->vecmul(e, a);
         return *this;
     }

     inline const quaternion & quaternion::operator /= (const float a) {
         getCurrent()->vecdiv(e, a);
         return *this;
     }

     inline const std::string quaternion::asString() const {
         return e.asString();
     }
}

#endif
