#ifndef MESH_H
#define MESH_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\transform.hpp>
	

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

class Mesh
{
public:
	//Mesh();
	Mesh(std::string filename, GLuint myShaderHandle);
	~Mesh();
	void genTexture(std::string textFile);
	void setColour(sf::Vector3f colour);

	void load(std::string);
	std::vector<GLuint> *getIndices(){return &indices;}

	GLuint getVAO(){return VAOHandle;}
	GLuint getTexture(){return myTexture;}

	GLuint myShaderHandle;

private:
	void init();
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
	

	std::string m_FileName;
};
#endif