#pragma once
namespace SpaceAdventures {

	enum class ComponentType
	{
		None = 0,
		TransformComponent,
		TextureComponent,
		ColliderComponent,
		CombatComponent,
		ProjectileComponent,
		MovementComponent
	};

	#define COMPONENT_CLASS_TYPE(type) static ComponentType GetStaticType() {return ComponentType::##type;}\
									virtual ComponentType GetComponentType() const override {return GetStaticType();}	

	class Component
	{
	public:

		virtual ComponentType GetComponentType() const { return ComponentType::None; }
		virtual void Init() {}
		virtual void Update() {}
		virtual void Draw() {}
		virtual ~Component() {}

	};
}