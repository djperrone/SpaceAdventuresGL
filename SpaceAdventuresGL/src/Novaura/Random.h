#pragma once
#include <random>
// https://github.com/TheCherno/OneHourParticleSystem/blob/master/OpenGL-Sandbox/src/Random.h
#include <spdlog/spdlog.h>
namespace Novaura {
	
	class Random
	{
	public:
		static void Init()
		{
			s_RandomEngine.seed(std::random_device{}());			
		}

		static float Float()
		{
			return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
		}

		static float Float(float x, float y)
		{
			s_Distribution = std::uniform_real_distribution<>(x,y);
			float result = s_Distribution(s_RandomEngine);
			return result;
		}

	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_real_distribution<> s_Distribution;
		static std::random_device rd;
	};
}