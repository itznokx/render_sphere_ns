#include <iostream>
#include <cmath>
#include "Vec3.h"
#include <SDL2/SDL.h>
class Color {
public:
    int r,g,b;
    void setRGB (int _r,int _g,int _b){
        this->r = _r;
        this->g = _g;
        this->b = _b;
    }
};
Color setColor (Vec3 SphereCenter,Vec3 dr,Vec3 RayOrigin,Vec3 pInt,Vec3 lightPosition,Vec3 colorObj, Vec3 lightIntesity, float m,float sphereRay){
    Vec3 l = (pInt-lightPosition);
    Vec3 n = ((pInt-SphereCenter)/sphereRay);
    Vec3 v = normalize(dr*(-1));
    Vec3 r = normalize(2*(l*n)*n-l);
    Vec3 rDifusa    = (-1)*(arroba(lightIntesity,colorObj)*((l*n)));
    Vec3 k_2 = normalize(colorObj);
    Vec3 rEspecular = (arroba(lightIntesity,k_2)*(v*r));
    Vec3 colorFinal = rDifusa;
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
			float c = (w*w) - (Sradius * Sradius);
			float delta = pow(b,2) - 4.0f*(a*c);
			Vec3 lightPosition (0.0f,3.0f,0.0f);
			Vec3 colorObj (255,0,0);
			Vec3 lightIntesity (0.7f,0.7f,0.7f);
			if (delta >= 0.0f){
				float tInt = (-b-sqrt(delta))/(2.0f*a);
				Vec3 pInt = RayOrigin+(tInt*dr);
				Color aux = setColor(SphereCenter,dr,RayOrigin,pInt,lightPosition,colorObj,lightIntesity, 0.0f,Sradius);
				
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