#include <iostream>
#include <cmath>
#include "Vec3.h"
using namespace std;

void raycasting(Vec3 SphereCenter,Vec3 RayOrigin,int wJanela,int hJanela,float Sradius,float Djanela ){
	int **matrix;
	matrix = new int *[hJanela];
	for (int i=0;i<=wJanela;i++){
		matrix[i] = new int [wJanela];
	}
	for (int y = 0;y<hJanela;y++){
		for (int x=0; x<wJanela;x++){
			float _x = -wJanela/2 + 1/2 + x*1;
			float _y = hJanela/2 - 1/2 - y*1;
			Vec3 RayDirection (_x,_y,-Djanela);
			float a = RayDirection*RayDirection;
			float b = 2.0f*((RayOrigin*RayDirection));
			float c = (RayOrigin*RayOrigin) - (pow(Sradius,2));
			float delta = pow(b,2) - 4.0f*(a*c);
			cout << a << endl << b << endl << c << endl << delta << endl;
			if (delta >= 0.0f){
				matrix[y][x] = 1;
			}
			else {
				matrix[y][x] = 0;
			}
		}
	}

	drawPixels (matrix,wJanela,hJanela);
		
}
int main(){
	float Sradius =  2.0;
	float Djanela = 4.0;
	Vec3 RayOrigin (0.0f,0.0f,0.0f);
	Vec3 teste(2,2,2);
	int wJanela = 256;
	int hJanela = 144;
	Vec3 SphereCenter (0,0,-(Djanela+Sradius));
	raycasting(SphereCenter,RayOrigin,wJanela,hJanela,Sradius,Djanela);
	
	return 0;
}