#ifndef HEIGHTGENERATOR_HPP
#define HEIGHTGENERATOR_HPP

class HeightGenerator {
public:
	HeightGenerator(unsigned int gridX, unsigned int gridZ, int seed);
	~HeightGenerator();
	
	float GetAmplitude();
	float GenerateHeight(int x, int z);

private:
	float GetInterpolatedNoise(float x, float z);
	float Interpolate(float a, float b, float blend);
	float GetSmoothNoise(int x, int z);
	float GetNoise(int x, int z);

	float m_amplitude;
	int m_octaves;
	float m_roughness;
	float m_seed;
	unsigned int m_xoffset;
	unsigned int m_zoffset;
};

#endif
