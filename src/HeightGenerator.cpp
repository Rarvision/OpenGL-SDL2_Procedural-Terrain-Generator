#include <cstdlib>
#include <ctime>
#include <cmath>
#include "HeightGenerator.hpp"

HeightGenerator::HeightGenerator(unsigned int gridX, unsigned int gridZ, int seed) {
	m_amplitude = 75.0f;
	m_octaves = 5;
	m_roughness= 0.35f;
	m_seed = seed;
	m_xoffset = gridX;
	m_zoffset = gridZ;
}

HeightGenerator::~HeightGenerator() {}

float HeightGenerator::GetAmplitude() {
	return m_amplitude;
}

float HeightGenerator::GenerateHeight(int x, int z) {
	float total = 0;
	float d = (float)pow(2, m_octaves-1);
	for(int i=0;i<m_octaves;i++){
		float freq = (float) (std::pow(2, i) / d);
		float amp = (float) std::pow(m_roughness, i) * m_amplitude;
		total += GetInterpolatedNoise((x+m_xoffset)*freq, (z+m_zoffset)*freq) * amp;
	}
	return total;
}

float HeightGenerator::GetInterpolatedNoise(float x, float z){
	int intX = (int) x;
	int intZ = (int) z;
	float fracX = x - intX;
	float fracZ = z - intZ;
		
	float v1 = GetSmoothNoise(intX, intZ);
	float v2 = GetSmoothNoise(intX + 1, intZ);
	float v3 = GetSmoothNoise(intX, intZ + 1);
	float v4 = GetSmoothNoise(intX + 1, intZ + 1);
	float i1 = Interpolate(v1, v2, fracX);
	float i2 = Interpolate(v3, v4, fracX);
	return Interpolate(i1, i2, fracZ);
}
	
float HeightGenerator::Interpolate(float a, float b, float blend){
	double theta = blend * 3.1415926;
	float f = (float)(1.0f - std::cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

float HeightGenerator::GetSmoothNoise(int x, int z) {
	float corners = (GetNoise(x - 1, z - 1) + GetNoise(x + 1, z - 1) + GetNoise(x - 1, z + 1)
			+ GetNoise(x + 1, z + 1)) / 16.0f;
	float sides = (GetNoise(x - 1, z) + GetNoise(x + 1, z) + GetNoise(x, z - 1)
			+ GetNoise(x, z + 1)) / 8.0f;
	float center = GetNoise(x, z) / 4.0f;
	return corners + sides + center;
}

float HeightGenerator::GetNoise(int x, int z) {
	// Hash function to generate noise value
	std::srand(m_seed + x*53100 + z*28000);
	float randomFloat = float(std::rand())/RAND_MAX;
	return 2*randomFloat-1;
}
