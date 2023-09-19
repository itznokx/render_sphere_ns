#include <iostream>
#include <cmath>
using namespace std;
class Vec3{
public:
	float x,y,z;
	Vec3 (float _x, float _y, float _z){
		x = _x;
		y = _y;
		z = _z;
	}
};
float operator*(Vec3 const& v1, Vec3 const& v2){
	float a = v1.x*v2.x;
	float b = v1.y*v2.y;
	float c = v1.z*v2.z;
	return (a+b+c); 
}
Vec3 operator*(Vec3 v1 , float num){
	return Vec3(v1.x*num,v1.y*num,v1.z*num);
}
Vec3 operator*(float num, Vec3 v1){
	return Vec3(v1.x*num,v1.y*num,v1.z*num);
}
Vec3 operator+(Vec3 v1, Vec3 v2){
	float x = v1.x+v2.x;
	float y = v1.y+v2.y;
	float z = v1.z+v2.z;
	return Vec3(x,y,z);
}
Vec3 operator-(Vec3 v1, Vec3 v2){
	float x = v1.x-v2.x;
	float y = v1.y-v2.y;
	float z = v1.z-v2.z;
	return Vec3 (x,y,z);
}
Vec3 operator/(Vec3 v1,float n){
    return Vec3(v1.x/n,v1.y/n,v1.z/n);
}
Vec3 normalize (Vec3 v1){
    float length = sqrt((v1.x*v1.x)+(v1.y*v1.y)+(v1.z+v1.z));
    return Vec3(v1.x/length,v1.y/length,v1.z/length);
}
Vec3 arroba (Vec3 v1,Vec3 v2){
    return Vec3(v1.x*v2.x,v1.y*v2.y,v1.z*v2.z);
}