#version 430

in vec3 i_VertPosition;
in vec3 i_VertNormal;
in vec2 i_TexCoords;

uniform mat4 mModel;        //Matrix to covert into world coordinate system
uniform mat4 mView;         //Matrix to convert into camera coordinate system
uniform mat4 mProjection;   //Matrix to covert to normalised screen coordinates

uniform mat4 u_ShadowMatrix;

out vec4 o_ShadowCoord;
out vec3 o_VertPos;
out vec3 o_VertNorm;
out vec2 o_TexCoords;

void main()  
{
	o_VertPos   = vec3(mModel * vec4(i_VertPosition,1.0)); 
	o_VertNorm  = i_VertNormal;
	o_TexCoords = i_TexCoords;
	o_ShadowCoord = u_ShadowMatrix * vec4(i_VertPosition,1.0);
	gl_Position = mProjection * mView * mModel * vec4(i_VertPosition,1.0); //Transform from local to world to camera to NDCs
}
