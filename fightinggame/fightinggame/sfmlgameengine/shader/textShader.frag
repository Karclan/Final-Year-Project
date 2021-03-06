#version 430

in vec2 texCoords;
out vec4 fragColour;

uniform sampler2D text;
uniform vec3 textColour;

void main()
{
	vec4 sampled = vec4(1.0,1.0,1.0,texture(text,texCoords).r);
	fragColour = vec4(textColour,1.0) * sampled;
}