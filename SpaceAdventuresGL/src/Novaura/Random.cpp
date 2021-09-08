#include "sapch.h"
#include "Random.h"

 // https://github.com/TheCherno/OneHourParticleSystem/blob/master/OpenGL-Sandbox/src/Random.cpp

namespace Novaura {

	std::mt19937 Random::s_RandomEngine;
	std::uniform_real_distribution<> Random::s_Distribution;	
	std::random_device Random::rd;
}