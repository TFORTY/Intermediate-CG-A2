#version 410

layout(location = 0) in vec3 inPos1;
layout(location = 1) in vec3 inCol;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec3 inNorm1;
layout(location = 4) in vec3 inPos2;
layout(location = 5) in vec3 inNorm2;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec2 outUV;
layout(location = 3) out vec3 outNormal;

uniform mat4 u_Model;
uniform mat3 u_ModelRotation;
uniform mat4 u_ModelViewProjection;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_LightPos;
uniform float u_MorphT;

void main()
{

	vec3 vertPos = mix(inPos1, inPos2, u_MorphT);

	gl_Position = u_ModelViewProjection * vec4(vertPos, 1.0f);

	outPosition = (u_Model * vec4(vertPos, 1.0f)).xyz;

	outUV = inUV;

	outNormal = u_ModelRotation * mix(inNorm1, inNorm2, u_MorphT);

	outColor = inCol;
	

}
