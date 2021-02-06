#pragma once
#include "PostEffect.h"
#include "LUT.h"

namespace freebird

{

	class ColorCorrection: public PostEffect
	{
	public:
	//Initlaize framebuffer
	void Init(unsigned width, unsigned height) override;

	//Applies effect to this buffer
	void ApplyEffect(PostEffect* buffer) override;



	private:


	//Create a LUT variable
	LUT3D colorEffectCube;
};

}

