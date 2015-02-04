#ifndef MESH_H
#define MESH_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\transform.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

class Mesh
{
public:
	Mesh();
	Mesh(int _primativeType, sf::Vector3f colour, GLuint myShaderHandle);
	~Mesh();
	void genTexture(std::string textFile);
	void setColour(sf::Vector3f colour);

	void load(std::string);
	std::vector<GLuint> *getIndices(){return &indices;}

	GLuint getVAO(){return VAOHandle;}
	GLuint getTexture(){return myTexture;}

	sf::Vector3f getColour(){return myDefColour;}

	glm::mat4 mModel;
	GLuint modelMatrixID;
	GLuint myShaderHandle;

private:

	void init(int _primativeType, sf::Vector3f colour);
	void genMesh();

	bool hasTexture;
	GLuint positionBufferHandle,normalBufferHandle,uvBufferHandle, index_buffer;
	std::vector<sf::Vector3f> points;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Vector2f> uvData;
	std::vector<GLuint> indices;
	GLuint VAOHandle, VBOHandle[4];
	GLuint myTexture;
	sf::Image myImage;
	sf::Vector3f myDefColour;
};
#endif