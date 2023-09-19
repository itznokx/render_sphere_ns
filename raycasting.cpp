#include <iostream>
#include <cmath>
#include "Raycasting.h"
using namespace std;
int main(){
	float Sradius =  30.0;
	float Djanela = 1.0;
	Vec3 Light (0.0f,5.0f,0.0f);
	Vec3 RayOrigin (0.0f,0.0f,0.0f);
	Vec3 teste(2,2,2);
	int wJanela = 640;
	int hJanela = 480;
	Vec3 SphereCenter (0,0,-(Djanela+Sradius));
	raycasting(SphereCenter,RayOrigin,Light,wJanela,hJanela,Sradius,Djanela);
	
	return 0;
}