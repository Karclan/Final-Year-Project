#version 430

in vec3 vertPosition;
in vec3 vertNormal;

uniform mat4 mModel;        //Matrix to covert into world coordinate system
uniform mat4 mView;         //Matrix to convert into camera coordinate system
uniform mat4 mProjection;   //Matrix to covert to normalised screen coordinates

out vec3 vertPos;
out vec3 vertNorm;

void main()  
{
	vertPos = vec3(mModel * vec4(vertPosition,1.0)); 
	vertNorm = vertNormal;
	gl_Position = mProjection * mView * mModel * vec4(vertPosition,1.0); //Transform from local to world to camera to NDCs
}
