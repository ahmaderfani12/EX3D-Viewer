#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;


// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
uniform vec4 ShadowColor; 

uniform vec3 lightPos;

uniform float specularLight;
uniform float specularpower;
// Gets the position of the camera from the main function
uniform vec3 camPos;



vec4 direcLight()
{


	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	vec4 diffuseColor =  mix(ShadowColor,lightColor,diffuse);

	// specular lighting
	vec3 viewDirection = normalize(camPos - vec3(0.0,0.0,0.0));
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularpower);
	float specular = specAmount * specularLight;

	return texture(diffuse0, texCoord) * (diffuseColor + specular);
}




void main()
{
	// outputs final color
	FragColor = direcLight();
}