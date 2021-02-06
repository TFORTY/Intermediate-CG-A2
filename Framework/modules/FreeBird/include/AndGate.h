#pragma once
#include "LogicGate.h"

namespace freebird
{
	class AndGate : public LogicGate
	{
	public:

		AndGate(Entity ent1, Entity ent2, Entity out);

		void Update();

	private:
	};
}

