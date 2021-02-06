#include "LogicGate.h"

namespace freebird
{
	LogicGate::LogicGate(Entity ent1, Entity ent2, Entity out)
	{
		input1 = false;
		input2 = false;
		output = false;
		isFinal = false;
		inputEnt1 = ent1;
		inputEnt2 = ent2;
		outputEnt = out;
	}

	LogicGate::LogicGate(Entity in, Entity out)
	{
		inputEnt1 = in;
		outputEnt = out;
	}

	bool LogicGate::GetInput1()
	{
		return input1;
	}

	Entity LogicGate::GetEnt1()
	{
		return inputEnt1;
	}

	Entity LogicGate::GetEnt2()
	{
		return inputEnt2;
	}

	bool LogicGate::GetInput2()
	{
		return input2;
	}

	void LogicGate::SetInputs(bool i1, bool i2)
	{
		input1 = i1;
		input2 = i2;
	}

	bool LogicGate::GetOutput()
	{
		return output;
	}

	bool LogicGate::GetIsFinal()
	{
		return isFinal;
	}

	void LogicGate::SetOutput(bool out)
	{
		output = out;
	}
	void LogicGate::SetIsFinal(bool fin)
	{
		isFinal = fin;
	}
	void LogicGate::SetEnt1(Entity ent1)
	{
		inputEnt1 = ent1;
	}
	void LogicGate::SetEnt2(Entity ent2)
	{
		inputEnt2 = ent2;
	}
}
