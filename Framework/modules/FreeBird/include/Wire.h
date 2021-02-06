#pragma once
#include "Entity.h"

namespace freebird
{
	class Wire
	{
	public:

		Wire(Entity input);

		void Update();

		bool GetIsPowered();
		Entity GetLast();
		Entity GetNext();

		void SetIsPowered(bool power);
		void SetLast(Entity last);
		void SetNext(Entity next);

	private:
		bool isPowered;
		Entity lastEnt, nextEnt;
	};
}