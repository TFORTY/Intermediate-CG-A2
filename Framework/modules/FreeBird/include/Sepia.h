#pragma once

#include "PostEffect.h"
namespace freebird
{
	class Sepia : public PostEffect
	{
	public:
		void Init(unsigned width, unsigned height) override;

		//Applies the effect to this buffer
		//Passes the previous buffer with the texture to apply as a parameter
		void ApplyEffect(PostEffect* buffer) override;

		//Getter
		float GetIntensity() const;

		//Setters
		void SetIntensity(float intensity);

	private:

		float _intensity = 0.7f;
	};
}