#pragma once

#include "PostEffect.h"

namespace freebird
{
	class Greyscale : public PostEffect
	{
	public:
		//Init framebuffer
		//Overrides post effect init
		void Init(unsigned width, unsigned height) override;

		//Applies the effect to this buffer
		//Passes the previous buffer with the texture to apply as a parameter
		void ApplyEffect(PostEffect* buffer) override;

		//applies the effect to the screen
		void DrawToScreen() override;

		//Getter
		float GetIntensity() const;

		//Setters
		void SetIntensity(float intensity);

	private:

		float _intensity = 1.0f;

	};
}