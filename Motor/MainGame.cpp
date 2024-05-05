#include "MainGame.h"

MainGame::MainGame()
{
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}


void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("RAAA", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//Es validar si hubo un error
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK); {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


void MainGame::draw()
{
	static bool primer_sprite_dibujado = false;
	static bool segundo_sprite_dibujado = false;
	static Uint32 tiempo_inicio = SDL_GetTicks();

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Dibuja el primer sprite
	if (!primer_sprite_dibujado) {
		
		sprite.draw();
		if (SDL_GetTicks() - tiempo_inicio >= 2000) {
			primer_sprite_dibujado = true;
			tiempo_inicio = SDL_GetTicks();
		}
	}
	// Dibuja el segundo sprite
	else if (!segundo_sprite_dibujado) {
		sprite2.draw();
		if (SDL_GetTicks() - tiempo_inicio >= 2000) {
			segundo_sprite_dibujado = true;
			tiempo_inicio = SDL_GetTicks();
		}
	}
	// Dibuja el tercer sprite
	else {
		if (SDL_GetTicks() - tiempo_inicio >= 2000) {
			sprite3.draw();
		}
	}

	SDL_GL_SwapWindow(window);
}




void MainGame::run()
{
	init();
	//Direcciones de donde se imprime
	
	sprite.init(-1, -1, 1, 1);
	
	sprite2.init(1, 1, -1, -1);
	
	sprite3.init(-1, 1, 1, -1);
	
	update();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}

void MainGame::processInput()
{
	//Capturar eventos en pantalla
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << "Posicion en X " << event.motion.x << " Posicion Y" << event.motion.y << endl;
		}
	}
}

MainGame::~MainGame()
{
}