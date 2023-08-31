#include <iostream>
#include "Vec3.h"
using namespace std;


int main(){
	Vec3 teste (4,3,1);
	Vec3 teste2 (3,3,10);
	teste = teste+teste2;
	cout << teste.x << endl << teste.y << endl << teste.z << endl;
	return 0;
}