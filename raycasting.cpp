#include <iostream>
#include "Vec3.h"
using namespace std;

void raycasting (Vec3 SphereCenter,Vec3 RayOrigin,int wJanela,int hJanela,float Sradius,float Djanela ){
 //test
}
int main(){
	float Sradius = 2;
	int Djanela = 1;
	Vec3 RayOrigin (0,0,0);
	int wJanela = 640;
	int hJanela = 480;
	Vec3 SphereCenter (0,0,-(Djanela+Sradius));
	raycasting(SphereCenter,RayOrigin,wJanela,hJanela,Sradius,Djanela);
	return 0;
}