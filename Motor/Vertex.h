#pragma once
#include "GL/glew.h"

//Posicion con x e y 
struct Position {
	float x;
	float y;
};

//Color con 4 valores de rgba
struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;
};

//Vertex que tendrá a los dos
struct Vertex {
	//Se crea el objeto posición y el objeto color, ocupan posición de memoria
	//Recuerda mantener orden, porque cambian la posición de memoria
	Position position;
	Color color; 
	UV uv;

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
	void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
	}
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

};