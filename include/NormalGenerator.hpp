#ifndef NORMALGENERATOR_HPP
#define NORMALGENERATOR_HPP

#include <glm/glm.hpp>

class NormalGenerator {
public:
	NormalGenerator();
	~NormalGenerator();

	glm::vec3 GetSmoothNormal(int x, int z, float* heightData, unsigned int xSegs, unsigned int zSegs);

private:
	float GetHeight(int x, int z, float* heightData, unsigned int xSegs, unsigned int zSegs);
};

#endif
