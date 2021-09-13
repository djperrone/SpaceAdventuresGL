#pragma once

namespace SpaceAdventures {

	namespace GameObjectData {

		constexpr uint32_t MAX_ASTEROIDS = 100;
		constexpr uint32_t MAX_SHIPS = 4;
		constexpr uint32_t MAX_PROJECTILES = 100;
		//constexpr uint32_t MAX_CHARACTERS = 204;
		constexpr uint32_t MAX_CHARACTERS = MAX_ASTEROIDS + MAX_SHIPS + MAX_PROJECTILES;
	}
}
