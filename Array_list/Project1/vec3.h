#pragma once
#include <math.h>
template<class T>
class vec3
{
public:
	vec3() {}
	
	vec3(T i, T j, T k) {
		x = i;
		y = j;
		z = k;
	}

	vec3(const vec3& a) {
		x = a.x;
		y = a.y;
		z = a.z;
	}
	~vec3() {}

	vec3 operator+(vec3& a) {

		vec3 c;

		c.x = a.x + x;
		c.y = a.y + y;
		c.z = a.z + z;

		return c;
	}

	vec3 operator-(const vec3& a) {

		vec3 c;

		c.x = x - a.x;
		c.y = y - a.y;
		c.z = z - a.z;

		return c;
	}

	vec3 operator =  {
		
		vec3 c;

		c.x = x;
		c.y = y;
		c.z = z;

		return (c);
	}


	vec3& operator+=(const vec3 a) {

		x = x + b.x;
		y = y + b.y;
		z = z + b.z;

		return this;

	}
	vec3& operator-=(const vec3 a) {
		
		x = x - a.x;
		y = y - a.y;
		z = z - a.z;

		return this;
	}

	bool operator==(vec3 a) {

		return a.x == x && a.y == y && a.z == z;

	}
	bool operator!=(vec3 a) {

		return a.x != x || a.y != y || a.z != z;

	}

	T normalize() {
		return sqrt(x*x + y*y + z*z);
	}
	
	vec3& Zero() {
		x = 0;
		y = 0;

		return this;
	}

	bool Is_zero() {
		return x == 0 && y == 0;
	}

	T Distance_to( const vec3 a) {

		return sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y) + (a.z - z)*(a.z - z));
	}

private:
	T x, y, z;

};
