#include <iostream>
#include <cmath>
#include "Vec3.h"
using namespace std;

void raycasting(Vec3 SphereCenter,Vec3 RayOrigin,Vec3 Light,int wJanela,int hJanela,float Sradius,float Djanela ){
	Color **matrix;
	matrix = new Color *[hJanela];
	for (int i=0;i<=wJanela;i++){
		matrix[i] = new Color [wJanela];
	}
	for (int y = 0;y<hJanela;y++){
		for (int x=0; x<wJanela;x++){
			float _x = -wJanela/2 + 1/2 + x*1;
			float _y = hJanela/2 - 1/2 - y*1;
			Vec3 dr (_x,_y,-(Djanela+Sradius));
			Vec3 w = RayOrigin-SphereCenter;
			float a = dr*dr;
			float b = 2.0f*(w*dr);
			float c = (w*w) - (pow(Sradius,2));
			float delta = pow(b,2) - 4.0f*(a*c);
			Vec3 lightPosition (0.0f,5.0f,0.0f);
			Vec3 colorObj (255,0,0);
			Vec3 lightIntesity (0.7f,0.7f,0.7f);
			if (delta >= 0.0f){
				float tInt = (-b*sqrt(delta))/a;
				Vec3 pInt = RayOrigin+(tInt*dr);
				Color aux = setColor(SphereCenter,dr,RayOrigin,pInt,lightPosition,colorObj,lightIntesity, 1.0f,Sradius);
				matrix[y][x] = aux;
			}
			else {
				Color aux;
				aux.setRGB(0, 0, 0);
				matrix[y][x] = aux;
			}
		}
	}
	drawPixels (matrix,wJanela,hJanela);
		
}

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