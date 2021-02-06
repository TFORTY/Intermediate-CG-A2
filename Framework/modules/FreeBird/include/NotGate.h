#pragma once
#include "LogicGate.h"

namespace freebird
{
	class NotGate : public LogicGate
	{
	public:

		NotGate(Entity in, Entity out);

		void Update();

	private:
	};
}
