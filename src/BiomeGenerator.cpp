#include "BiomeGenerator.hpp"
#include <cmath>
#include <algorithm>

BiomeGenerator::BiomeGenerator(float maxHeight) {
	m_maxHeight = maxHeight;
}

BiomeGenerator::~BiomeGenerator() {}

glm::vec3 BiomeGenerator::GetBiomeColor(float height) {

	if(height <= -0.39) {
		return glm::vec3(131, 215, 238);   // water
	} else if (height < 0.1 * m_maxHeight) { 
		return glm::vec3(76, 70, 50);  // sand
	} else if (height < 0.3 * m_maxHeight) {
		return glm::vec3(75, 112, 4);     // trees
	} else if (height < 0.65 * m_maxHeight) {
		return glm::vec3(128, 132, 135);     // rock
	} else {
		return glm::vec3(255, 255, 255);  // snow
	}

}

