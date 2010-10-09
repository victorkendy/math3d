/*
 * matrix44.h
 *
 *  Created on: Jun 17, 2010
 *      Author: kendy
 */

#ifndef math3d_matrix44_h_
#define math3d_matrix44_h_ 1

#include "math3d/core/core.h"
#include "math3d/vector4.h"


namespace math3d {

    class matrix44 : public basicMath3dObject{
    public:
        matrix44() {}

        matrix44(const float a00, const float a01, const float a02, const float a03,
                 const float a10, const float a11, const float a12, const float a13,
                 const float a20, const float a21, const float a22, const float a23,
                 const float a30, const float a31, const float a32, const float a33);

        matrix44(const matrix44 & m);

        matrix44 & operator = (const matrix44 & m);

        matrix44 operator - ();

        float4 & operator [] (int i);
        const float4 & operator [] (int i) const;

        friend const matrix44 operator * (float a, const matrix44 & m);

        friend const vector4 operator * (const matrix44 & m, const vector4 & v);
        friend const matrix44 operator * (const matrix44 & a, const matrix44 & b);
        friend const matrix44 operator + (const matrix44 & a, const matrix44 & b);
        friend const matrix44 operator - (const matrix44 & a, const matrix44 & b);

        const bool operator == (const matrix44 & m) const;

        const matrix44 operator * (const float a) const;
        const matrix44 operator / (const float a) const;
        matrix44 & operator += (const matrix44 & a);
        matrix44 & operator -= (const matrix44 & a);
        matrix44 & operator *= (const matrix44 & a);
        matrix44 & operator *= (const float a);
        matrix44 & operator /= (const float a);

        operator float * () const;
        operator float4 * ();

        void loadIdentity();
        const matrix44 transpose() const;
        const matrix44 inverse() const;
        void setRow(int i, const float4 & newRow);
        void setRow(int i, const vector4 & v);
        void set(const float a00, const float a01, const float a02, const float a03,
                 const float a10, const float a11, const float a12, const float a13,
                 const float a20, const float a21, const float a22, const float a23,
                 const float a30, const float a31, const float a32, const float a33);
        const std::string asString() const;
    private:
        float4 e[4];
    };

    inline matrix44::matrix44(const float a00, const float a01, const float a02, const float a03,
                              const float a10, const float a11, const float a12, const float a13,
                              const float a20, const float a21, const float a22, const float a23,
                              const float a30, const float a31, const float a32, const float a33) {
        getCurrent()->vecset(e[0], a00, a01, a02, a03);
        getCurrent()->vecset(e[1], a10, a11, a12, a13);
        getCurrent()->vecset(e[2], a20, a21, a22, a23);
        getCurrent()->vecset(e[3], a30, a31, a32, a33);
    }

    inline matrix44::matrix44(const matrix44 & m) {
        getCurrent()->vecset(e[0], m.e[0]);
        getCurrent()->vecset(e[1], m.e[1]);
        getCurrent()->vecset(e[2], m.e[2]);
        getCurrent()->vecset(e[3], m.e[3]);
    }

    inline matrix44 & matrix44::operator = (const matrix44 & m) {
        getCurrent()->vecset(e[0], m.e[0]);
        getCurrent()->vecset(e[1], m.e[1]);
        getCurrent()->vecset(e[2], m.e[2]);
        getCurrent()->vecset(e[3], m.e[3]);
        return *this;
    }

    inline matrix44 matrix44::operator - () {
        matrix44 m;
        getCurrent()->vecmul(getCurrent()->vecset(m.e[0], e[0]), -1);
        getCurrent()->vecmul(getCurrent()->vecset(m.e[1], e[1]), -1);
        getCurrent()->vecmul(getCurrent()->vecset(m.e[2], e[2]), -1);
        getCurrent()->vecmul(getCurrent()->vecset(m.e[3], e[3]), -1);
        return m;
    }

    inline const float4 & matrix44::operator [] (int i) const {
        return e[i];
    }

    inline float4 & matrix44::operator [] (int i) {
        return e[i];
    }

    inline const matrix44 operator * (float a, const matrix44 & m) {
        matrix44 r;
        getCurrent()->vecmul(getCurrent()->vecset(r.e[0], m.e[0]), a);
        getCurrent()->vecmul(getCurrent()->vecset(r.e[1], m.e[1]), a);
        getCurrent()->vecmul(getCurrent()->vecset(r.e[2], m.e[2]), a);
        getCurrent()->vecmul(getCurrent()->vecset(r.e[3], m.e[3]), a);
        return r;
    }

    inline const matrix44 operator * (const matrix44 & a, const matrix44 & b) {
        matrix44 r (a);
        getCurrent()->m44mul(r.e, b.e);
        return r;
    }

    inline const matrix44 operator + (const matrix44 & a, const matrix44 & b) {
        matrix44 r;
        getCurrent()->vecadd(getCurrent()->vecset(r.e[0], a.e[0]), b.e[0]);
        getCurrent()->vecadd(getCurrent()->vecset(r.e[1], a.e[1]), b.e[1]);
        getCurrent()->vecadd(getCurrent()->vecset(r.e[2], a.e[2]), b.e[2]);
        getCurrent()->vecadd(getCurrent()->vecset(r.e[3], a.e[3]), b.e[3]);
        return r;
    }

    inline const matrix44 operator - (const matrix44 & a, const matrix44 & b) {
        matrix44 r;
        getCurrent()->vecsub(getCurrent()->vecset(r.e[0], a.e[0]), b.e[0]);
        getCurrent()->vecsub(getCurrent()->vecset(r.e[1], a.e[1]), b.e[1]);
        getCurrent()->vecsub(getCurrent()->vecset(r.e[2], a.e[2]), b.e[2]);
        getCurrent()->vecsub(getCurrent()->vecset(r.e[3], a.e[3]), b.e[3]);
        return r;
    }

    inline const vector4 operator * (const matrix44 & m, const vector4 & v) {
        vector4 r(v);
        getCurrent()->m44mulvec(r, m.e);
        return r;
    }

    inline const matrix44 matrix44::operator * (const float a) const {
        matrix44 r;
        getCurrent()->vecmul(getCurrent()->vecset(r.e[0], e[0]), a);
        getCurrent()->vecmul(getCurrent()->vecset(r.e[1], e[1]), a);
        getCurrent()->vecmul(getCurrent()->vecset(r.e[2], e[2]), a);
        getCurrent()->vecmul(getCurrent()->vecset(r.e[3], e[3]), a);
        return r;
    }

    inline const matrix44 matrix44::operator / (const float a) const {
        matrix44 r;
        getCurrent()->vecdiv(getCurrent()->vecset(r.e[0], e[0]), a);
        getCurrent()->vecdiv(getCurrent()->vecset(r.e[1], e[1]), a);
        getCurrent()->vecdiv(getCurrent()->vecset(r.e[2], e[2]), a);
        getCurrent()->vecdiv(getCurrent()->vecset(r.e[3], e[3]), a);
        return r;
    }

    inline const bool matrix44::operator == (const matrix44 & m) const {
        return (getCurrent()->vecequal(e[0], m.e[0]) &&
                getCurrent()->vecequal(e[1], m.e[1]) &&
                getCurrent()->vecequal(e[2], m.e[2]) &&
                getCurrent()->vecequal(e[3], m.e[3]));
    }

    inline matrix44 & matrix44::operator += (const matrix44 & a) {
        getCurrent()->vecadd(e[0], a.e[0]);
        getCurrent()->vecadd(e[1], a.e[1]);
        getCurrent()->vecadd(e[2], a.e[2]);
        getCurrent()->vecadd(e[3], a.e[3]);
        return *this;
    }

    inline matrix44 & matrix44::operator -= (const matrix44 & a) {
        getCurrent()->vecsub(e[0], a.e[0]);
        getCurrent()->vecsub(e[1], a.e[1]);
        getCurrent()->vecsub(e[2], a.e[2]);
        getCurrent()->vecsub(e[3], a.e[3]);
        return *this;
    }

    inline matrix44 & matrix44::operator *= (const matrix44 & m) {
        getCurrent()->m44mul(e, m.e);
        return *this;
    }

    inline matrix44 & matrix44::operator *= (const float a) {
        getCurrent()->vecmul(e[0], a);
        getCurrent()->vecmul(e[1], a);
        getCurrent()->vecmul(e[2], a);
        getCurrent()->vecmul(e[3], a);
        return *this;
    }

    inline matrix44 & matrix44::operator /= (const float a) {
        getCurrent()->vecdiv(e[0], a);
        getCurrent()->vecdiv(e[1], a);
        getCurrent()->vecdiv(e[2], a);
        getCurrent()->vecdiv(e[3], a);
        return *this;
    }

    inline matrix44::operator float * () const{
        return (float*) &e[0];
    }

    inline matrix44::operator float4 * () {
        return &e[0];
    }

    inline void matrix44::loadIdentity() {
        getCurrent()->m44identity(e);
    }

    inline const matrix44 matrix44::transpose() const {
        matrix44 r(*this);
        getCurrent()->m44transpose(r.e);
        return r;
    }

    inline const matrix44 matrix44::inverse() const {
        matrix44 r(*this);
        getCurrent()->m44inv(r.e);
        return r;
    }

    inline void matrix44::set(const float a00, const float a01, const float a02, const float a03,
                              const float a10, const float a11, const float a12, const float a13,
                              const float a20, const float a21, const float a22, const float a23,
                              const float a30, const float a31, const float a32, const float a33) {
        getCurrent()->vecset(e[0], a00, a01, a02, a03);
        getCurrent()->vecset(e[1], a10, a11, a12, a13);
        getCurrent()->vecset(e[2], a20, a21, a22, a23);
        getCurrent()->vecset(e[3], a30, a31, a32, a33);
    }

    inline void matrix44::setRow(int i, const float4 &v) {
        getCurrent()->vecset(e[i], v);
    }
    
    inline void matrix44::setRow(int i, const vector4 & v) {
        setRow(i, (float4&)v);
    }

    inline const std::string matrix44::asString() const {
        return e[0].asString() + "\n" + e[1].asString() + "\n" + e[2].asString() + "\n" + e[3].asString();
    }
}

#endif
