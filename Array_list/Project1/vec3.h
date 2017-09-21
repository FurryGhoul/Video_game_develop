#include <math.h>
template<class T>
class vec3
{
public:

	T x, y, z;

	vec3() {}
	
	vec3(T i, T j, T k) {
		x = i;
		y = j;
		z = k;
	}

	vec3(const vec3& vec_2) {
		x = vec_2.x;
		y = vec_2.y;
		z = vec_2.z;
	}
	~vec3() {}

	vec3 operator+(const vec3& vec_2) {

		vec3 vec_3;

		vec_3.x = vec_2.x + x;
		vec_3.y = vec_2.y + y;
		vec_3.z = vec_2.z + z;

		return vec3;
	}

	vec3 operator-(const vec3& vec_2) {

		vec3 vec_3;

		vec_3.x = x - vec_2.x;
		vec_3.y = y - vec_2.y;
		vec_3.z = z - vec_2.z;

		return vec_3;
	}

	vec3 operator =(const vec3& vec_2)  {

		x = vec_2.x;
		y = vec_2.y;
		z = vec_2.z;

		return this;
	}


	vec3 operator+=(const vec3& vec_2) {

		x = x + vec_2.x;
		y = y + vec_2.y;
		z = z + vec_2.z;

		return this;

	}
	vec3 operator-=(const vec3& vec_2) {
		
		x = x - vec_2.x;
		y = y - vec_2.y;
		z = z - vec_2.z;

		return this;
	}

	bool operator==(const vec3& vec_2) {

		return vec_2.x == x && vec_2.y == y && vec_2.z == z;

	}
	bool operator!=(const vec3& a) {

		return a.x != x || a.y != y || a.z != z;

	}

	void normalize() {
		
		T m=sqrt(x*x + y*y + z*z);

		x = x / m;
		y = y / m;
		z = z / m;
	}
	
	vec3& Zero() {
		x = 0;
		y = 0;

		return this;
	}

	bool Is_zero() {
		return x == 0 && y == 0;
	}

	T Distance_to( const vec3& vec_2) {

		return sqrt((vec_2.x - x)*(vec_2.x - x) + (vec_2.y - y)*(vec_2.y - y) + (vec_2.z - z)*(vec_2.z - z));
	}

};
