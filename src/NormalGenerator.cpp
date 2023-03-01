#include "NormalGenerator.hpp"

NormalGenerator::NormalGenerator(){}

NormalGenerator::~NormalGenerator(){}

glm::vec3 NormalGenerator::GetSmoothNormal(int x, int z, float* heightData, unsigned int xSegs, unsigned int zSegs) {
	float heightL = GetHeight(x-1, z, heightData, xSegs, zSegs);
	float heightR = GetHeight(x+1, z, heightData, xSegs, zSegs);
	float heightD = GetHeight(x, z-1, heightData, xSegs, zSegs);
	float heightU = GetHeight(x, z+1, heightData, xSegs, zSegs);
	glm::vec3 normal = glm::vec3(heightL-heightR, 2.0f, heightD-heightU);
	return glm::normalize(normal);
}

float NormalGenerator::GetHeight(int x, int z, float* heightData, unsigned int xSegs, unsigned int zSegs) {
	
	int dataLength = xSegs*zSegs;
	x = x<0 ? 0:x;
	z = z<0 ? 0:z;
	x = x>=dataLength ? dataLength-1 :x;
	z = z>=dataLength ? dataLength-1 :z;
	
	return heightData[x+z*xSegs];

}
