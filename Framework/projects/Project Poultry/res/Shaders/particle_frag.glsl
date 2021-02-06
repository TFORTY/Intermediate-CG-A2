#version 410

layout(location = 0) in vec2 inUV;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 frag_color;

uniform sampler2D u_Diffuse;

void main()
{
	//vec4 textureCol = texture(u_Diffuse, inUV);

	//frag_color = vec4(inColor /** textureCol*/);

	frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}