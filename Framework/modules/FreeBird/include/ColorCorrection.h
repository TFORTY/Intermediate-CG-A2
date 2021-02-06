#pragma once
#include "PostEffect.h"
#include "LUT.h"
#include <string>

namespace freebird

{

	class ColorCorrection: public PostEffect
	{
	public:
	//Initlaize framebuffer
	void Init(unsigned width, unsigned height) override;

	//Applies effect to this buffer
	void ApplyEffect(PostEffect* buffer) override;

	//Getters
	std::string GetCubeName();

	//Setters
	void SetCubeName(std::string name);


	private:
	//Create a LUT variable
	LUT3D colorEffectCube;

	//String variable that will store 'cube name' valuable from setter function
	std::string cubeName;
};

}

