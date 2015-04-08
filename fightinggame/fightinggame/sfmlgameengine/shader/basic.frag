#version 430

in vec3 o_VertPos;
in vec3 o_VertNorm;
in vec2 o_TexCoords;
in vec4 o_ShadowCoords;


#define MAX_SPOTLIGHTS 4
#define MAX_POINTLIGHTS 4

struct Material
{
vec3 diff;
vec3 spec;
float specEx;
};

struct SpotLight
{ 
vec3 position;
 vec3 spotDir;
 float spotOutCut;
 float spotInCut;

 float constant;
 float linear;
 float quadratic;

 vec3 amb;            //ambient light intensity
 vec3 diff;           // Diffuse light intensity
 vec3 spec;
 };

struct PointLight
{
 vec3 position;

 float constant;
 float linear;
 float quadratic;

 vec3 amb;             //ambient light intensity
 vec3 diff;            // Diffuse light intensity
 vec3 spec;
 };

struct DirectionLight
{
 vec3 direction;

 vec3 amb;             //ambient light intensity
 vec3 diff;            // Diffuse light intensity
 vec3 spec;
};

uniform mat4			u_ShadowMatrix;
uniform mat3			NormalMatrix;
uniform vec3			viewPos;

uniform int				numOfSpotLights;
uniform int				numOfPointLights;
uniform SpotLight		spotLight[MAX_SPOTLIGHTS];
uniform PointLight		pointLight[MAX_POINTLIGHTS];
uniform DirectionLight  dirLight;

uniform Material		material;

uniform sampler2D u_DiffuseTexture;
uniform sampler2D u_SpecularTexture;
uniform sampler2D u_NormalTexture;

uniform sampler2DShadow u_ShadowMap;

layout(location=0)out vec4 FragColour;

subroutine void    RenderType();
subroutine uniform RenderType renderPass;

vec4 shadeShadows(vec3 ambient, vec3 diffuse)
{
	float visibility = 1.0;//textureProj(u_ShadowMap, o_ShadowCoords);

	return vec4(diffuse * visibility + ambient, 1.0);
}

vec3 CalSpotLight (SpotLight  light, vec3 normal, vec3 viewDir, vec3 vertPos, vec3 diff, vec3 spec)
{
	vec3 lightDir	  = normalize(light.position - vertPos);
    vec3 reflectDir   = reflect(-lightDir, normal);
    				  
	float theta		  = dot(lightDir,normalize(-light.spotDir));
	float epsilon	  = (light.spotInCut - light.spotOutCut);
					  
	float distance	  = length(light.position - vertPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	if(theta > light.spotOutCut)
	{
		//if(dot(viewDir,normal)>0)
		//{
			float intensity = clamp((theta - light.spotOutCut) / epsilon, 0.0, 1.0);
 
			float diffuse = max(dot(normal, lightDir), 0.0);
  
			float specular = pow(max(dot(viewDir, reflectDir), 0.0), material.specEx);
    
			vec3 diffuseCol = light.diff * diffuse * diff * intensity; 
			vec3 specularCol = light.spec * specular * spec * intensity;
			if(dot(viewDir,normal)<0)
			{
			specularCol=vec3(0,0,0);
			}
			diffuseCol *= attenuation;
			specularCol*= attenuation;

			return diffuseCol + specularCol;
		//}
	}
	return  vec3(0.0);
}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 vertPos, vec3 diff, vec3 spec)
{
	vec3 lightDir	  = normalize(light.position - vertPos);
    vec3 reflectDir   = reflect(-lightDir, normal);
					  
	float distance	  = length(light.position - vertPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	//if(dot(viewDir,normal)>0)
	//{
	float diffuse  = max(dot(normal, lightDir), 0.0);
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), material.specEx);
    

	vec3 diffuseCol  = light.diff * diffuse  * diff; 
	vec3 specularCol = light.spec * specular * spec;

	if(dot(viewDir,normal)<0)
	{
	specularCol=vec3(0,0,0);
	}

	diffuseCol *= attenuation;
	specularCol*= attenuation;	

	return  diffuseCol + specularCol;
}

vec3 CalDirLight  (vec3 normal, vec3 viewDir, vec3 diff, vec3 spec)
{
	vec3 lightDir	  = normalize(dirLight.direction);
    vec3 reflectDir   = reflect(-lightDir, normal);
	float diffuse  = max(dot(normal, lightDir), 0.0);
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), material.specEx);
    
	vec3 diffuseCol  = dirLight.diff * diffuse  * diff; 
	vec3 specularCol = dirLight.spec * specular * spec;

	if(dot(viewDir,normal)<0)
	{
	specularCol=vec3(0,0,0);
	}	

	return  diffuseCol + specularCol;
}



subroutine(RenderType)
void shadowPass()
{

// do nothing, give me the DEPTH!!!!! AHAHAHHAHAHA
}

subroutine(RenderType)
void noTexture()
{
	vec3 norm		= normalize(NormalMatrix * o_VertNorm);
    vec3 viewDir	= normalize(viewPos - o_VertPos);
	vec3 diffuseCol = vec3(0.0);
	vec3 ambientCol = vec3(0.0);
	
	ambientCol = dirLight.amb * material.diff;
	diffuseCol += CalDirLight(norm,viewDir,  material.diff, material.spec);

	for(int i=0;i<numOfPointLights;++i)
	{
		diffuseCol += CalPointLight(pointLight[i], norm, viewDir,o_VertPos, material.diff, material.spec);
	}
	for(int i=0;i<numOfSpotLights;i++)
	{
		diffuseCol += CalSpotLight(spotLight[i],norm, viewDir,o_VertPos, material.diff, material.spec);
	}
	FragColour= shadeShadows(ambientCol,diffuseCol);
}

subroutine(RenderType)
void diffuse()
{
	vec3 norm		= normalize(NormalMatrix * o_VertNorm);
    vec3 viewDir	= normalize(viewPos - o_VertPos);
	vec3 diffuseCol = vec3(0.0);
	vec3 ambientCol = vec3(0.0);

	ambientCol = dirLight.amb * material.diff;
	diffuseCol += CalDirLight(norm,viewDir, texture(u_DiffuseTexture,o_TexCoords).xyz, material.spec);

	for(int i=0;i<numOfPointLights;++i)
	{
		diffuseCol += CalPointLight(pointLight[i], norm, viewDir, o_VertPos, texture(u_DiffuseTexture,o_TexCoords).xyz, material.spec);
	}
	for(int i=0;i<numOfSpotLights;i++)
	{
		diffuseCol += CalSpotLight(spotLight[i], norm, viewDir,	o_VertPos,texture(u_DiffuseTexture,o_TexCoords).xyz,material.spec);
	}
	vec4 colour = shadeShadows(ambientCol,diffuseCol);
	colour.w = texture(u_DiffuseTexture,o_TexCoords).w;
	FragColour=colour;
}

subroutine(RenderType)
void diffuseSpecular()
{
	vec3 norm		= normalize(NormalMatrix * o_VertNorm);
    vec3 viewDir	= normalize(viewPos - o_VertPos);
	vec3 diffuseCol = vec3(0.0);
	vec3 ambientCol = vec3(0.0);

	ambientCol = dirLight.amb * material.diff;
	diffuseCol += CalDirLight(norm,viewDir, texture(u_DiffuseTexture,o_TexCoords).xyz, texture(u_SpecularTexture,o_TexCoords).xyz);

	for(int i=0;i<numOfPointLights;++i)
	{
		diffuseCol += CalPointLight(pointLight[i], norm, viewDir, o_VertPos, texture(u_DiffuseTexture,o_TexCoords).xyz, texture(u_SpecularTexture,o_TexCoords).xyz);
		//ambientCol += pointLight[i].amb * texture(u_DiffuseTexture,o_TexCoords).xyz;
	}
	for(int i=0;i<numOfSpotLights;i++)
	{
		diffuseCol += CalSpotLight(spotLight[i], norm, viewDir,	o_VertPos,texture(u_DiffuseTexture,o_TexCoords).xyz,texture(u_SpecularTexture,o_TexCoords).xyz);
		//ambientCol += spotLight[i].amb * texture(u_DiffuseTexture,o_TexCoords).xyz;
	}
	vec4 colour = shadeShadows(ambientCol,diffuseCol);
	colour.w = texture(u_DiffuseTexture,o_TexCoords).w;
	FragColour=colour;
}
void main()
{
	renderPass();
}
