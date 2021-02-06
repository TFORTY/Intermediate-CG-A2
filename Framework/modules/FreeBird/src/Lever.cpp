#include "Lever.h"

namespace freebird
{
	Lever::Lever(Entity nextEnt)
	{
		next = nextEnt;
		isPowered = false;
	}

	void Lever::Update()
	{
		if (isPowered && next.Has<Wire>())
		{
			next.Get<Wire>().SetIsPowered(true);
		}
		else if (!isPowered && next.Has<Wire>())
		{
			next.Get<Wire>().SetIsPowered(false);
		}
	}

	bool Lever::GetPowered()
	{
		return isPowered;
	}

	void Lever::SetPowered(bool pow)
	{
		isPowered = pow;
	}

}