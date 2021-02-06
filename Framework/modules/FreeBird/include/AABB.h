#pragma once
#include "Entity.h"
#include "GLM/glm.hpp"

namespace freebird
{
	class AABB {

	public:

		AABB(Entity ent, Entity playEnt);

		void Update();

		Entity GetPlayerEnt();
		Entity GetThisEnt();

		bool GetComplete();
		void SetComplete(bool complete);

		glm::vec3 GetNext();
		void SetNext(glm::vec3 next);

	private:
		Entity playerEnt, thisEnt;
		bool isColliding;
		bool levelComplete = false;
		glm::vec3 nextPos;
	};
}