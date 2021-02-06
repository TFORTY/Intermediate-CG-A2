#pragma once
#include "Entity.h"
#include "Wire.h"

namespace freebird
{
	class Lever
	{
	public:
		Lever(Entity nextEnt);

		void Update();

		bool GetPowered();
		void SetPowered(bool pow);

	private:
		Entity next;
		bool isPowered;
	};
}
