#version 330 core

out vec4 FragColor;

// Imports from the Vertex Shader
in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;


// Gets the Texture Units 
uniform sampler2D diffuse0;
// Have used yet
uniform sampler2D specular0;


uniform vec4 lightColor;
uniform vec4 ShadowColor; 
uniform vec3 lightPos;
uniform vec3 rimColor;

uniform float specularLight;
uniform float specularpower;
uniform float rimPower;
uniform float rimStrength;

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

	// rim lighting
	vec3 verToCam = normalize(camPos - crntPos);
	float rimAmount = max(1.0 - pow(max(dot(normal,verToCam),0.01),rimPower)*rimStrength,0) * diffuse;
	
	

	return mix(texture(diffuse0, texCoord),vec4(rimColor,1.0),rimAmount) * (diffuseColor + specular);
	//return vec4(rimAmount,rimAmount,rimAmount,1.0);
}




void main()
{
	// outputs final color
	FragColor = direcLight();
}