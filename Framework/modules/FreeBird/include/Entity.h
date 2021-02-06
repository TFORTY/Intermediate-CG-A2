#pragma once

#include "entt.hpp"

namespace freebird
{
	class Entity
	{
	public:

		//Creates a new entity
		static Entity Create();

		//Constructor
		Entity(entt::entity ent);
		Entity() { entID = ECS.create(); }

		//virtual ~Entity();

		//Adds a component to an entity
		template<typename T, typename ... Args>
		T& Add(Args&&... arg)
		{
			return ECS.get_or_emplace<T>(entID, std::forward<Args>(arg)...);
		}

		//Gets a component from an entity to edit
		template<typename T>
		T& Get() {
			return ECS.get<T>(entID);
		}

		//Checks if an entity has a component
		template<typename T>
		bool Has() {
			return ECS.has<T>(entID);
		}

		//Removes a component from an entity
		template<typename T>
		void Remove();

		static void SetReg(entt::registry *reg);

		entt::entity GetID();

	private:
		//Registry and entity ID for use with entities in main
		static entt::registry ECS;
		static entt::registry* regRef;
		entt::entity entID;
	};
}