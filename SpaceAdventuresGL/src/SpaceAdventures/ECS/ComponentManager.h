#pragma once
#include "Component.h"

#include <array>
#include <memory>

namespace SpaceAdventures {

	class ComponentManager
	{
	private:
		//std::unordered_map<ComponentType, Component> components_map;
		//std::vector<std::unique_ptr<Component>> components;
		std::array<std::shared_ptr<Component>, 32> componentArray;
	public:
		ComponentManager() = default;		

		template <typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);

			componentArray[static_cast<int>(T::GetStaticType())] = component;
		}

		template <typename T>
		T& GetComponent()
		{
			auto ptr = componentArray[static_cast<int>(T::GetStaticType())];
			return *dynamic_cast<T*>(ptr.get());
		}
	};
}