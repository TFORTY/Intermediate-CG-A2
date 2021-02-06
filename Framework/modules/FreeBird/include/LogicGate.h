#pragma once
#include "Entity.h"
#include "Wire.h"
#include "Door.h"

namespace freebird
{
	class LogicGate
	{
	public:

		LogicGate(Entity ent1, Entity ent2, Entity out);
		LogicGate(Entity in, Entity out);

		virtual void Update() {}

		//SETTERS
		void SetInputs(bool i1, bool i2);
		void SetOutput(bool out);
		void SetIsFinal(bool fin);
		void SetEnt1(Entity ent1);
		void SetEnt2(Entity ent2);

		//GETTERS
		bool GetInput1();
		Entity GetEnt1();
		Entity GetEnt2();
		bool GetInput2();
		bool GetOutput();
		bool GetIsFinal();

	protected:

		bool input1, input2, output, isFinal;

		Entity inputEnt1, inputEnt2;
		Entity outputEnt;
	};
}