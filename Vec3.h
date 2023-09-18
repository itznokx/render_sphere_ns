#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
using namespace std;
class Color {
public:
    int r,g,b;
    void setRGB (int _r,int _g,int _b){
        this->r = _r;
        this->g = _g;
        this->b = _b;
    }
};
class Vec3{
public:
    Color color;
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
    double length = sqrt((v1.x*v1.x)+(v1.y*v1.y)+(v1.z+v1.z));
    return Vec3(v1.x/length,v1.y/length,v1.z/length);
}
Vec3 arroba (Vec3 v1,Vec3 v2){
    return Vec3(v1.x*v2.x,v1.y*v2.y,v1.z*v2.z);
}
void checkMatrix (int **matrix,int x, int y){
    for (int l=0; l<y ; l++){
        for (int c=0;c<x;c++){
            cout << matrix[l][c] << endl;
        }
    }
}
Color setColor (Vec3 SphereCenter,Vec3 dr,Vec3 RayOrigin,Vec3 pInt,Vec3 lightPosition,Vec3 colorObj, Vec3 lightIntesity, float m,float sphereRay){
    Vec3 l = normalize(pInt-RayOrigin);
    Vec3 n = (pInt-SphereCenter)/sphereRay;
    Vec3 v = dr*(-1);
    Vec3 r = 2*(l*n)*n-l;
    Vec3 rDifusa    = (arroba(lightIntesity,colorObj)*((l*n)));
    Vec3 rEspecular = (arroba(lightIntesity,colorObj)*(pow((v*r),m)));
    Vec3 colorFinal = rDifusa + rEspecular;
    Color final;
    final.setRGB(colorFinal.x,colorFinal.y,colorFinal.z);
    return final;
}

int drawPixels (Color **matrix,int wJanela,int hJanela){

    // Inicializar a biblioteca para poder usar suas funções
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Não foi possível inicializar o SDL! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    // Criar uma janela
    SDL_Window* window = SDL_CreateWindow(
        "CG I - Raycaster",       // Título da Janela
        SDL_WINDOWPOS_UNDEFINED,        // Posição inicial X
        SDL_WINDOWPOS_UNDEFINED,        // Posição inicial Y
        wJanela,                           // Largura da janela em pixels
        hJanela,                            // Altura da janela em pixels
        SDL_WINDOW_SHOWN                // Flags
    );

    // Verificar se a janela foi criada corretamente
    if (!window) {
        SDL_Log("Criação da janela falhou! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Criar o objeto renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Criação do renderer falhou! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Main loop - É dentro do main while loop que fazemos todas as interações com a janela
    bool isRunning = true; //variável de controle do loop
    SDL_Event event; //variável para checar os eventos da janela

    while (isRunning) {
        // É possível interagir com a janela, com clicks, apertando teclas ou clicando para fechar a janela
        // essas interações são chamadas de "eventos", abaixo, verificamos se o evento de fechar janela ocorre
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // É uma boa prática limpar o renderer antes de desenhar novos pixeis, no caso de existir "lixo" no renderer
        SDL_RenderClear(renderer);


        // Aqui temos a estrutura para pintar um pixel, no caso, um loop para pintar todos os pixeis da janela

        //SDL_SetRenderDrawColor(renderer,  100, 100, 100, 255); // <---- Aqui escolhemos a cor que desejamos pintar
                                                          // DETALHE: essa função utiliza o padrão RGBA, para 
                                                          // o nosso propósito, podemos ignorar o último parâmetro
        int pixelCount = 0;
        for (int x = 0; x <= wJanela; x++) {
            for (int y = 0; y <= hJanela; y++) {
            	SDL_SetRenderDrawColor(renderer,  matrix[y][x].r, matrix[y][x].g, matrix[y][x].b, 255);
            	SDL_RenderDrawPoint(renderer, x, y); 
            }
        }

        // Por fim, atualizamos a janela com o renderer que acabamos de pintar e tudo deve funcionar corretamente
        SDL_RenderPresent(renderer);
    }

    // Destruir os objetos criados para limpar a memória
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
