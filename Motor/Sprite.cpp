#include "Sprite.h"
#include "Vertex.h"
#include "cstddef"//SI ERES REBELDE Y QUIERES PONER COLOR ANTES QUE POSITION

Sprite::Sprite()
{
	vboID = 0;
}


void Sprite::init(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	
	if (vboID == 0) {
		glGenBuffers(1, &vboID);// Separar espacio espacio n�mero que va a ocupar el objeto

	}
	//6 v�rtices de x e y = 12 puntos
	/*float vertexData[12];
	vertexData[0] = x + width;
	vertexData[1] = y +	height;

	vertexData[2] = x;
	vertexData[3] = y + height;
	vertexData[4] = x;
	vertexData[5] = y;

	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;
	vertexData[10] = x + width;
	vertexData[11] = y + height;*/

	Vertex vertexData[6];
	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);



	glBindBuffer(GL_ARRAY_BUFFER, vboID); //array al id ,recibe m�s parametros
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(vertexData), vertexData, GL_STATIC_DRAW); //recibe 4 cosas: que se va a mandar un array, el tama�o de la variable, la variable y el tipo de dibujo (static) 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/*void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);//x pares e y son impares
	//cuantas variables estas mandando (6) 
	glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 0, 0); //0 es el primer elemento, xy son coordenadas= 2, tipo float las variables,
														//	false es para no normalizar, 0 y 0 solo son n�meros no hay otro valor.
	glDrawArrays(GL_TRIANGLES,0,6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/


void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);//x pares e y son impares
	/*cuantas variables estas mandando (6) 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //0 es el primer elemento, xy son coordenadas= 2, tipo float las variables,
	false es para no normalizar, 0 y 0 solo son n�meros no hay otro valor.*/
	

	//Si eres rebelde y usas: (void*)offsetof(Vertex, position));  
	// revela posici�n de memoria dentro de vertex, no importa si est� desordenado
	//SI QUIERES MANDAR ATRIBUTOS POR AQU�

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, position)); 

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
		(void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



Sprite::~Sprite()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}