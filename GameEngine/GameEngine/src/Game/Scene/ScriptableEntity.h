#pragma once

#include "Game/Scene/Entity.h"

namespace GameEngine {

	class ScriptableEntity
	{
	public:

		virtual ~ScriptableEntity() = default;

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}


	protected:
		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnUpdate(Timestep ts) = 0;

	private:
		Entity m_Entity;
		friend class Scene;
	};


}