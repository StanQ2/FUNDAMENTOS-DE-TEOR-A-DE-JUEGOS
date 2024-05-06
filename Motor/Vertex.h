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

//Vertex que tendr� a los dos
struct Vertex {
	//Se crea el objeto posici�n y el objeto color, ocupan posici�n de memoria
	//Recuerda mantener orden, porque cambian la posici�n de memoria
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