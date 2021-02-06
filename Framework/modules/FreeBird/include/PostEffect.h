#pragma once

#include "Framebuffer.h"
#include "Shader.h"
namespace freebird
{
	class PostEffect
	{
	public:
		//initializes this effect
		virtual void Init(unsigned width, unsigned height);

		//Applies the effect
		virtual void ApplyEffect(PostEffect* previousBuffer);
		virtual void DrawToScreen();

		//Reshapes the buffer
		virtual void Reshape(unsigned width, unsigned height);

		//Clears the buffer
		void Clear();

		//Unloads all the buffers
		void Unload();

		//Binds buffers
		void BindBuffer(int index);
		void UnbindBuffer();

		//Bind textures
		void BindColorAsTexture(int index, int colorBuffer, int textureSlot);
		void BindDepthAsTexture(int index, int textureSlot);
		void UnbindTexture(int textureSlot);

		//Bind Shaders
		void BindShader(int index);
		void UnbindShader();

	protected:

		std::vector<Framebuffer*> _buffers;

		std::vector<Shader::sptr> _shaders;
	};
}
