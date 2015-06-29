#pragma once
namespace Rand
{
	/**Initialises the Random system.*/
	void initialise(uint32_t seed);

	/**Returns a random number within the range [min,max] (I think...).*/
	int Random(int min, int max);

	/**Returns a random number within the range [min,max] (I think...).*/
	float Random(float min, float max);

	/**Returns a random number within the range [min,max] (I think...).*/
	double Random(double min, double max);
}