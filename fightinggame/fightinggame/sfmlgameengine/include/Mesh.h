#ifndef MESH_H
#define MESH_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\transform.hpp>
	

#include <assimp\Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

/*! \brief  Mesh

Mesh class. Mesh class which contains all data about a mesh

*/
class Mesh
{
public:
	Mesh(std::string filename, GLuint myShaderHandle); //!< Constructor which loads mesh
	~Mesh();
	void genTexture(std::string textFile); //!< loads a texture. Old function
	void setColour(sf::Vector3f colour); //!< Old function left over from old systyem design

	void load(std::string); //!< Uses Assimp to load mesh and put mesh data into vectors
	std::vector<GLuint> *getIndices(){return &indices;} //!< gets the number of indicies a mesh has. Used for rendering

	GLuint getVAO(){return VAOHandle;}
	GLuint getTexture(){return myTexture;}

	GLuint myShaderHandle;

private:
	void init();
	void genMesh();

	void setVerts();
	void setNormals();
	void setColours();
	void setTangents();
	void setBiTangents();
	void setIndicies();

	bool hasTexture;
	GLuint	positionBufferHandle,
			normalBufferHandle,
			uvBufferHandle,
			tangentBufferHandle,
			biTangentBufferHandle,
			index_buffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> biTangents;
	std::vector<glm::vec2> uvData;
	std::vector<GLuint> indices;

	//std::vector<glm::vec3> colours;

	GLuint VAOHandle, VBOHandle[4];
	GLuint myTexture;
	sf::Image myImage;
	

	std::string m_FileName;
};
#endif