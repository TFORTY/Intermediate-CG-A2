#version 410

layout(location = 0) in vec4 inPos;
layout(location = 1) in float inSize;
layout(location = 2) in vec4 inColor;

out Vertex
{
	float size;
	vec4 color;
} v;

void main()
{
	v.size = inSize;
	v.color = inColor;
	gl_Position = inPos;
}