#include "Shader.h"

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
	vertShader = glCreateShader( GL_VERTEX_SHADER );
	if (0 == vertShader) {
		std::cout<<"Error creating: "+_vertFile+" \n"<<std::endl;
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = {codeStr.c_str()};
	glShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the shader
	glCompileShader( vertShader );

	// Check compilation statussuc
	GLint result;
	glGetShaderiv( vertShader, GL_COMPILE_STATUS, &result );
	if( FALSE == result ) {
		fprintf( stderr, "Vertex shader compilation failed!\n" );

		GLint logLen;
		glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(vertShader, logLen, &written, log);

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
	fragShader = glCreateShader( GL_FRAGMENT_SHADER );
	if (0 == fragShader) {
		std::cout<<"Error creating" + _fragFile<<std::endl;
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	glShaderSource( fragShader, 1, codeArray, NULL );

	// Compile the shader
	glCompileShader( fragShader );

	// Check compilation status
	glGetShaderiv( fragShader, GL_COMPILE_STATUS, &result );
	if (FALSE == result) {
		fprintf( stderr, "Fragment shader compilation failed!\n" );

		GLint logLen;
		glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	linkMe();
}

void Shader::linkMe()
{

	// Create the program object
	shaderProgID = glCreateProgram();
	if(0 == shaderProgID) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}

	// Attach the shaders to the program object
	glAttachShader( shaderProgID, vertShader );
	glAttachShader( shaderProgID, fragShader );

	// Link the program
	glLinkProgram( shaderProgID );

	// Check for successful linking
	GLint status;
	glGetProgramiv( shaderProgID, GL_LINK_STATUS, &status );
	if (FALSE == status) {

		fprintf( stderr, "Failed to link shader program!\n" );

		GLint logLen;
		glGetProgramiv( shaderProgID, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetProgramInfoLog(shaderProgID, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	//else 
	//{
	//	glUseProgram( shaderProgID );
	//}

}