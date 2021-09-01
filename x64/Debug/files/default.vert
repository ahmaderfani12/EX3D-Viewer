#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Outputs for the Fragment Shader
out vec3 crntPos;
out vec3 normal;
out vec3 color;
out vec2 texCoord;


uniform mat4 camMatrix;
uniform mat4 model;

uniform vec3 worldPos;
uniform vec3 rotationAngle;
uniform vec3 scale;

mat4 PositionMatrix(){
	return mat4(1.0,0.0,0.0,worldPos.x,
				0.0,1.0,0.0,worldPos.y,
				0.0,0.0,1.0,worldPos.z,
				0.0,0.0,0.0,1.0
	);
}

mat4 ScaleMatrix(){
	return mat4(scale.x,0.0,0.0,0.0,
				0.0,scale.y,0.0,0.0,
				0.0,0.0,scale.z,0.0,
				0.0,0.0,0.0,1.0
	);
}

mat4 RotationMatrix(){
//x,y,z matrix
	return 
	mat4(1.0,0.0,0.0,0.0,
		0.0,cos(rotationAngle.x),sin(rotationAngle.x),0.0,
		0.0,-sin(rotationAngle.x),cos(rotationAngle.x),0.0,
		0.0,0.0,0.0,1.0
	)*	
	mat4(cos(rotationAngle.y),0.0,-sin(rotationAngle.y),0.0,
		 0.0,1.0,0.0,0.0,
		 sin(rotationAngle.y),0.0,cos(rotationAngle.y),0.0,
		 0.0,0.0,0.0,1.0
	)*	
	mat4(cos(rotationAngle.z),sin(rotationAngle.z),0.0,0.0,
		 -sin(rotationAngle.z),cos(rotationAngle.z),0.0,0.0,
		 0.0,0.0,1.0,0.0,
		 0.0,0.0,0.0,1.0
	);

}

vec3 transformPos(in vec3 vec){
	 return vec4(vec,1.0) *ScaleMatrix()*RotationMatrix() * PositionMatrix();
}
vec3 transformNormal(in vec3 vec){
	 return vec4(vec,1.0) *RotationMatrix();
}


void main()
{

	normal = transformNormal(aNormal);
	crntPos=transformPos(aPos);
	color = aColor;
	texCoord = aTex;



	gl_Position = camMatrix * vec4(crntPos,1.0);
}