#version 430

in vec3 o_VertPos;
in vec3 o_VertNorm;
in vec2 o_TexCoords;

#define MAX_SPOTLIGHTS 4
#define MAX_POINTLIGHTS 4

struct Material
{vec3 diff;
vec3 spec;
float specEx;};

struct SpotLight
{ vec3 position;
 vec3 spotDir;
 float spotOutCut;
 float spotInCut;

 float constant;
 float linear;
 float quadratic;

 vec3 amb;            //ambient light intensity
 vec3 diff;           // Diffuse light intensity
 vec3 spec;};

struct PointLight
{ vec3 position;

 float constant;
 float linear;
 float quadratic;

 vec3 amb;            //ambient light intensity
 vec3 diff;            // Diffuse light intensity
 vec3 spec;};

uniform mat3 NormalMatrix;

uniform vec3 meshColour;    //! Currently unused !//

uniform vec3 viewPos;
uniform int numOfSpotLights;
uniform int numOfPointLights;
uniform SpotLight spotLight[MAX_SPOTLIGHTS];
uniform PointLight pointLight[MAX_POINTLIGHTS];
uniform Material material;

uniform sampler2D u_DiffuseTexture;
uniform int u_Textured;
out vec4 FragColour;

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 vertPos, vec3 diff, vec3 spec)
{
	vec3 lightDir	= normalize(light.position - vertPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    
	float theta		= dot(lightDir,normalize(-light.spotDir));
	float epsilon	= (light.spotInCut - light.spotOutCut);
	
	float distance	= length(light.position - vertPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 ambientCol  = light.amb * diff;
	//ambientCol	*= attenuation;

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

			return ambientCol + diffuseCol + specularCol;
		//}
	}
	return  ambientCol;
}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 vertPos, vec3 diff, vec3 spec)
{
	vec3 lightDir	= normalize(light.position - vertPos);
    vec3 reflectDir = reflect(-lightDir, normal);
	
	float distance	= length(light.position - vertPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 ambientCol  = light.amb * diff;
	//ambientCol	*= attenuation;
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
		
	return ambientCol + diffuseCol + specularCol;
	//}
	//return  ambientCol;
}

vec3 CalDirLight(vec3 normal, vec3 diff, vec3 spec)
{
return vec3(0,0,0);
}
void main()
{
	 //--Properties--//
	vec3 norm = normalize(NormalMatrix * o_VertNorm);
    vec3 viewDir = normalize(viewPos - o_VertPos);

	vec3 result= vec3(0.0,0.0,0.0);

	if(u_Textured==0)
	{
		for(int i=0;i<numOfPointLights;++i)
		{
			result += CalPointLight(
			pointLight[i], 
			norm, 
			viewDir,
			o_VertPos, 
			material.diff, 
			material.spec
			);
		}
		for(int i=0;i<numOfSpotLights;i++)
		{
			result += CalSpotLight(
			spotLight[i],
			norm, 
			viewDir,
			o_VertPos, 
			material.diff, 
			material.spec
			);
		}
	}
	else if(u_Textured==1)
	{
		for(int i=0;i<numOfPointLights;++i)
		{
			result += CalPointLight(
			pointLight[i], 
			norm, 
			viewDir, 
			o_VertPos, 
			texture(u_DiffuseTexture,o_TexCoords).xyz, 
			material.spec
			);
		}
		for(int i=0;i<numOfSpotLights;i++)
		{
			result += CalSpotLight(
			spotLight[i], 
			norm, 
			viewDir,
			o_VertPos,
			texture(u_DiffuseTexture,o_TexCoords).xyz,
			material.spec
			);
		}
	}

	vec4 colour=vec4(result,1.0);
	if(u_Textured)
	{
	//colour.w=texture(u_DiffuseTexture,o_TexCoords).w;
	}
	
	FragColour=colour;
}
