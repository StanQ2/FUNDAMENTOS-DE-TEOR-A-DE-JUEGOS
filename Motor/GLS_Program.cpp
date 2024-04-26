#include "GLS_Program.h"
#include "vector"
#include "fstream"

void GLS_Program::compileShader(const string& shaderPath, GLuint id)
{
	string filecontent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	//se pregunta si no hay error
	if (shaderFile.fail()) {
		//implementar mensaje de error
	}
	//chapamos todas las líneas
	while (getline(shaderFile, line)) {
		filecontent += line;
	}
	//Se cierra
	shaderFile.close();
	//Convertimos a puntero
	const char* contents = filecontent.c_str();
	//creamos el shader
	glShaderSource(id, 1, &contents, nullptr);
	//Compilamos shader
	glCompileShader(id);
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(id);
		return;

	}
}

GLS_Program::GLS_Program()
{

}

GLS_Program::~GLS_Program()
{

}

void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	//identificador de este compildaro que estamos creando
	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, vertexShaderID);

}

void GLS_Program::linkShader()
{

}
