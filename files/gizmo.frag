#version 330 core


out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D diffuse0;



void main()
{
	// outputs final color
	FragColor = texture(diffuse0, texCoord);
}