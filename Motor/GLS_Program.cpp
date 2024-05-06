#include "GLS_Program.h"
#include "vector"
#include "fstream"
#include "Error.h"

void GLS_Program::compileShader(const string& shaderPath, GLuint id)
{
	string filecontent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	//se pregunta si no hay error
	if (shaderFile.fail()) {
		fatalError("El archivo " + shaderPath + " no se encuentra disponible");
		//implementar mensaje de error
	}
	//chapamos todas las líneas
	while (getline(shaderFile, line)) {
		filecontent += line + "\n";
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
		fatalError("Shaders no compilaron " + printf("%s", &(errorLog[0])));
		glDeleteShader(id);
		return;

	}
}

GLS_Program::GLS_Program() : programID(0), vertexShaderID(0),
fragmentShaderID(0), numAtribute(0)
{


}

GLS_Program::~GLS_Program()
{

}

//SHADERS IMPLEMENTADOS EN C++
void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	//identificador de este compildaro que estamos creando
	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);

}

//TODOS LOS SHADER SE UTILIZAN CON LINKSHADER,  
//todos los SHADERs creados, lo linkeamos al programID 
void GLS_Program::linkShader(){
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(programID);
		fatalError("Shaders no linkearon " + printf("%s", &(infoLog[0])));
		glDeleteShader(vertexShaderID); 
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLS_Program::addAtribute(const string atributeName)
{
	glBindAttribLocation(programID, numAtribute++, 
		atributeName.c_str());
}

//prendete
void GLS_Program::use()
{
	glUseProgram(programID);
	for( int i = 0; i < numAtribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

//apagate
void GLS_Program::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < numAtribute; i++ )
	{
		glDisableVertexAttribArray(i);
	}

}

GLuint GLS_Program::getUniformLocation(const string& name)
{
	GLuint location = glGetUniformLocation(programID,
	name.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Variable uniform " + name + " no encontrada");
	}
	return location;
}
