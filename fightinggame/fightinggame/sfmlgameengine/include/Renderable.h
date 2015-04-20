#ifndef RENDERABLE_H
#define RENDERABLE_H

#define GLM_FORCE_RADIANS
#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Texture.h"
#include "Component.h"
#include "Transfrom.h"
#include "Mesh.h"
#include "Shader.h"

/*! \brief  Renderable Component Class

Renderable Component.
Game Objects that wish to be rendered will have one of these components.

*/


class Renderable : public Component
{
public:
	Renderable();
	Renderable(SPC_Transform t, Mesh *m, Shader* s); //!<Constructor which determins the mesh and shader the object uses

	ComponentType::type getType();
	void tearDown();

	void giveMesh(Mesh *mesh); //!<Gives a mesh to the object
	void assignTexture(std::string filename, TextureType::type type); //!<Assigns a texture to the object
	bool textured(TextureType::type type);//!<Returns bool if a certain texture type is assigned to object
	bool textured();//!<returns bool if diffuse texture is assigned
	void bindTexture(TextureType::type type);//!<Binds texture for rendering
	void unbindTextures(); //!<unbinds all textures
	void setShader(Shader *shader); 
	void setDiff(glm::vec3 diffuseReflection);
	void setSpec(glm::vec3 specularReflection);
	void setSpecEx(GLfloat exponent);

	Mesh*	  getMesh();
	Shader*	  getShader();
	glm::vec3 getDiff();
	glm::vec3 getSpec();
	GLfloat	  getSpecEx();



	SPC_Transform getTransform(){ return m_Transform; }
private:
	void setShaderHandle();

	GLuint	  m_ShaderHandle;	
	GLuint	  m_ModelMatrixID;  //!<Unused outdated value. Was originally used for location position of model matrix within the shader program
	glm::vec3 m_ColourTint;		//!<Unused colour value. Was originally used to tint the colour of an object for rendering
	glm::vec3 m_DiffuseReflection;//!< Material Diffuse value
	glm::vec3 m_SpecularReflection;//!<Material Specular value 
	GLfloat   m_SpecularExponent;//!<Material 'shiny' value
	Mesh*	  m_Mesh;		//!<Mesh pointer, not mesh class but pointer. Saves on space
	Shader*	  m_Shader;		//!<Pointer to shader
	bool	  m_Textured	 [TextureType::TYPES]; //!<flags for each texture an renderable can have
	Texture	  m_TextureObject[TextureType::TYPES]; //!<Texture objects for each texture and renderable can have 

	SPC_Transform m_Transform;
};

typedef std::shared_ptr<Renderable> SPC_Renderable;

#endif