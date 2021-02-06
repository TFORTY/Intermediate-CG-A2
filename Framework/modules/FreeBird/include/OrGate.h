#pragma once
#include "LogicGate.h"

namespace freebird
{
	class OrGate : public LogicGate
	{
	public:

		OrGate(Entity ent1, Entity ent2, Entity out);

		void Update();

	private:
	};
}