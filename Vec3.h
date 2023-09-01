#include <iostream>
#include <SDL2/SDL.h>
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
int drawPixels (int **matrix,int wJanela,int hJanela){

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
        1280,                           // Largura da janela em pixels
        720,                            // Altura da janela em pixels
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
        for (int x = 0; x < wJanela; x++) {
            for (int y = 0; y < hJanela; y++) {
            	if (matrix[y][x] == 0){
            		SDL_SetRenderDrawColor(renderer,  100, 100, 100, 255);
            		SDL_RenderDrawPoint(renderer, x, y); 
            	}else if (matrix[y][x] == 1){
            		SDL_SetRenderDrawColor(renderer,  255, 0, 0, 255);
            		SDL_RenderDrawPoint(renderer, x, y); 
            	}
                SDL_RenderDrawPoint(renderer, x, y);  //<---- Aqui escolhemos qual pixel vamos pintar
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