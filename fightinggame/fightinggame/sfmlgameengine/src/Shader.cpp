#include "Shader.h"

void Shader::useProgram()
{
	glUseProgram(m_ProgID);
}
void Shader::createShader(string _vertFile, string _fragFile)
{
	//////////////////////////////////////////////////////
	/////////// Vertex shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file
	//"shader/basic.vert"
	ifstream inFile( _vertFile );
	if (!inFile) {
		std::cout<<"Error opening: "+_vertFile<<std::endl;
		exit(EXIT_FAILURE);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	m_vertShader = glCreateShader( GL_VERTEX_SHADER );
	if (0 == m_vertShader) {
		std::cout<<"Error creating: "+_vertFile+" \n"<<std::endl;
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = {codeStr.c_str()};
	glShaderSource(m_vertShader, 1, codeArray, NULL);

	// Compile the shader
	glCompileShader( m_vertShader );

	// Check compilation statussuc
	GLint result;
	glGetShaderiv( m_vertShader, GL_COMPILE_STATUS, &result );
	if( FALSE == result ) {
		fprintf( stderr, "Vertex shader compilation failed!\n" );

		GLint logLen;
		glGetShaderiv( m_vertShader, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(m_vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file into shaderCode here
	//"shader/basic.frag"
	ifstream fragFile( _fragFile  );
	if (!fragFile) {
		std::cout<<"Error Opening :"+_fragFile<<std::endl;
		exit(EXIT_FAILURE);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Create the shader object
	m_fragShader = glCreateShader( GL_FRAGMENT_SHADER );
	if (0 == m_fragShader) {
		std::cout<<"Error creating" + _fragFile<<std::endl;
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	glShaderSource( m_fragShader, 1, codeArray, NULL );

	// Compile the shader
	glCompileShader( m_fragShader );

	// Check compilation status
	glGetShaderiv( m_fragShader, GL_COMPILE_STATUS, &result );
	if (FALSE == result) {
		fprintf( stderr, "Fragment shader compilation failed!\n" );

		GLint logLen;
		glGetShaderiv( m_fragShader, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(m_fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	linkMe();
}

void Shader::linkMe()
{

	// Create the program object
	m_ProgID = glCreateProgram();
	if(0 == m_ProgID) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}

	// Attach the shaders to the program object
	glAttachShader( m_ProgID, m_vertShader );
	glAttachShader( m_ProgID, m_fragShader );

	// Link the program
	glLinkProgram( m_ProgID );

	// Check for successful linking
	GLint status;
	glGetProgramiv( m_ProgID, GL_LINK_STATUS, &status );
	if (FALSE == status) {

		fprintf( stderr, "Failed to link shader program!\n" );

		GLint logLen;
		glGetProgramiv( m_ProgID, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetProgramInfoLog(m_ProgID, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
}

void Shader::setUniform(const char *name, float x, float y, float z)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc,x,y,z);
}

void Shader::setUniform(const char *name, const glm::vec3 &_v)
{
	this->setUniform(name,_v.x,_v.y,_v.z);
}

void Shader::setUniform(const char *name, const glm::vec4 &_v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc,_v.x,_v.y,_v.z,_v.w);
}

void Shader::setUniform(const char *name, const glm::vec2 &_v)
{
	GLint loc = getUniformLocation(name);
	glUniform2f(loc,_v.x,_v.y);
}
void Shader::setUniform(const char *_name, const sf::Vector3f &_v)
{
	GLint loc = getUniformLocation(_name);
	glUniform3f(loc,_v.x,_v.y,_v.z);
}
void Shader::setUniform(const char *name, const glm::mat4 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, FALSE, &m[0][0]);
}

void Shader::setUniform(const char *name, const glm::mat3 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix3fv(loc, 1, FALSE, &m[0][0]);
}

void Shader::setUniform(const char *name, float _val )
{
	GLint loc = getUniformLocation(name);
	glUniform1f(loc, _val);
}

void Shader::setUniform(const char *name, int __val )
{
	GLint loc = getUniformLocation(name);
	glUniform1i(loc, __val);
}

void Shader::setUniform(const char *name, GLuint __val )
{
	GLint loc = getUniformLocation(name);
	glUniform1ui(loc, __val);
}

void Shader::setUniform(const char *name, bool _val )
{
	int loc = getUniformLocation(name);
	glUniform1i(loc, _val);
}

int Shader::getUniformLocation(const char * _name )
{
	std::map<std::string, int>::iterator pos;
	pos = uniformLocations.find(_name);

	if( pos == uniformLocations.end() ) {
		uniformLocations[_name] = glGetUniformLocation(m_ProgID, _name);
	}

	return uniformLocations[_name];
}

