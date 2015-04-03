#ifndef GS_H
#define GS_H

#include <glm\gtx\transform.hpp>

namespace GS
{
	extern enum KEYS{W,S,A,D, 
		NUMBEROFKEYS};
	extern const float FRAMERATE;	
	extern const glm::vec3 floor;
	extern const glm::vec3 ambient;
	extern const float gravity;
	extern const float walkSpeed;
	extern const float runSpeed;
	extern const float jumpSpeed;
	extern int SCREENWIDTH;
	extern int SCREENHEIGHT;
}
#endif