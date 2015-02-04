#ifndef GS_H
#define GS_H

#define GLM_FORCE_RADIANS
#include <glm\gtx\transform.hpp>

namespace GS
{
	extern enum componentTag{collision,
		componentTags};

	extern enum gameObjType{gameObject, block, fallingBlock, Fighter, hitBox,
		gameObjectTypes};

	extern enum KEYS{W,S,A,D, 
		NUMBEROFKEYS};

	extern const glm::vec3 floor;
	extern const glm::vec3 ambient;
	extern const float gravity;
	extern const float walkSpeed;
	extern const float runSpeed;
	extern const float jumpSpeed;
	
}
#endif