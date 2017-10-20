#pragma once
#ifndef PM_HPP
#define PM_HPP
#include "PM.hpp"
//personal math lib

#include <cmath>

template <typename T>
class Vector3
{
	//1017º∆ªÆ
	/*1.Tracerª∫¥Ê->GLª∫¥Ê
	2.GLª∫¥ÊªÊ÷∆*/

public:
	T x, y, z, w;
	Vector3() :x(T(1)), y(T(1)), z(T(1)),w(T(1)) {};
	Vector3(const T a, const T b, const T c) :x(T(a)), y(T(b)), z(T(c)) {};
	Vector3<T> operator*(const T&f)const { return Vector3<T>(x*f, y*f, z*f); }
	Vector3<T> operator*(const Vector3<T> &v)const { return Vector3<T>(x*v.x, y*v.y, z*v.z); }
	






	~Vector3() {};
private:

};

typedef Vector3<float> vec3f;
typedef Vector3<double> vec3d;
typedef vec3f Point;
inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }//∑µªÿ0-1




#endif // !PM_HPP

