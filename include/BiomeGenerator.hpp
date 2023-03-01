#ifndef BIOMEGENERATOR_HPP
#define BIOMEGENERATOR_HPP

#include <glm/glm.hpp>
#include <vector>

class BiomeGenerator {
public:
	BiomeGenerator(float m_maxHeight);
	~BiomeGenerator();

	glm::vec3 GetBiomeColor(float height);

private:
	float m_maxHeight;
};

#endif
