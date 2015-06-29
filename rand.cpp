#include "stdafx.h"
#include "rand.h"
#include "tinymt32.h"

namespace Rand
{
	tinymt32_t tinymt32;

	void initialise(uint32_t seed)
	{
		tinymt32_init(&tinymt32, seed);
	}

	int Random(int min, int max)
	{
		return min + (tinymt32_generate_uint32(&tinymt32) % (int)(max - min + 1));
	}

	float Random(float min, float max)
	{
		return min + tinymt32_generate_float(&tinymt32) * (max - min);
	}

	double Random(double min, double max)
	{
		return min + tinymt32_generate_32double(&tinymt32) * (max - min);
	}
}