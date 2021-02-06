#include "Entity.h"

namespace freebird
{
	entt::registry Entity::ECS;
	entt::registry *Entity::regRef = &ECS;

	Entity::Entity(entt::entity ent)
	{
		entID = ent;
	}

	void Entity::SetReg(entt::registry *reg)
	{
		regRef = reg;
	}

	entt::entity Entity::GetID()
	{
		return entID;
	}


	Entity Entity::Create()
	{
		entt::entity entity = ECS.create();

		return Entity(entity);
	}

	template<typename T>
	void Entity::Remove()
	{
		ECS.remove<T>(entID);
	}
}