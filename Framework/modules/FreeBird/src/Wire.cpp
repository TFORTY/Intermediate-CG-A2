#include "Wire.h"
#include <AndGate.h>
#include <OrGate.h>
#include <NotGate.h>
#include <Lever.h>

namespace freebird
{

	Wire::Wire(Entity input)
	{
		lastEnt = input;
		isPowered = false;
	}

	void Wire::Update()
	{
		if (lastEnt.Has<Wire>() && lastEnt.Get<Wire>().GetIsPowered())
			isPowered = true;
		else if (lastEnt.Has<AndGate>() && lastEnt.Get<AndGate>().GetOutput())
			isPowered = true;
		else if (lastEnt.Has<OrGate>() && lastEnt.Get<OrGate>().GetOutput())
			isPowered = true;
		else if (lastEnt.Has<NotGate>() && lastEnt.Get<NotGate>().GetOutput())
			isPowered = true;
		else if (lastEnt.Has<Lever>() && lastEnt.Get<Lever>().GetPowered())
			isPowered = true;
		else
			isPowered = false;
	}

	bool Wire::GetIsPowered()
	{
		return isPowered;
	}

	Entity Wire::GetLast()
	{
		return lastEnt;
	}

	Entity Wire::GetNext()
	{
		return nextEnt;
	}

	void Wire::SetIsPowered(bool power)
	{
		isPowered = power;
	}

	void Wire::SetLast(Entity last)
	{
		lastEnt = last;
	}

	void Wire::SetNext(Entity next)
	{
		nextEnt = next;
	}

}

