#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <string>
#include <algorithm>

class Perlin {
public:
	//1-D Noise
	float *fNoiseSeed1D = nullptr; //array for random noise
	float *fPerlinNoise1D = nullptr; //array for output perlin noise values
	int nOutputSize;

	//2-D Noise
	float *fNoiseSeed2D = nullptr; //array for random noise
	float *fPerlinNoise2D = nullptr; //array for output perlin noise values
	int nOutputWidth;
	int nOutputHeight;

	Perlin() {
		nOutputSize = 256;
		fNoiseSeed1D = new float[nOutputSize];
		fPerlinNoise1D = new float[nOutputSize];

		for (int i = 0; i < nOutputSize; i++) {
			fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
		}

		PerlinNoise1D(nOutputSize, fNoiseSeed1D, 7, 3.0f, fPerlinNoise1D);
	}

	Perlin(int x, int y) {
		nOutputWidth = 256;
		nOutputHeight = 256;
		fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
		fPerlinNoise2D = new float[nOutputWidth * nOutputHeight];


		for (int i = 0; i < nOutputWidth * nOutputHeight; i++) {
			fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
		}

		PerlinNoise2D(nOutputWidth, nOutputHeight, fNoiseSeed2D, 7, 3.0f, fPerlinNoise1D);
	}

	void PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float fBias, float *fOutput) {
		// Used 1D Perlin Noise
		for (int x = 0; x < nCount; x++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nCount >> o;
				int nSample1 = (x / nPitch) * nPitch;
				int nSample2 = (nSample1 + nPitch) % nCount;

				float fBlend = (float)(x - nSample1) / (float)nPitch;

				float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

				fScaleAcc += fScale;
				fNoise += fSample * fScale;
				fScale = fScale / fBias;
			}

			// Scale to seed range
			fOutput[x] = fNoise / fScaleAcc;
		}
	}

	void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput) {
		for(int x = 0; x < nWidth; x++)
			for (int y = 0; y < nHeight; y++) {
				float fNoise = 0.0f;
				float fScaleAcc = 0.0f;
				float fScale = 1.0f;

				for (int o = 1; o < nOctaves; o++)
				{
					int nPitch = nWidth >> o;
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;

					int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
					int nSampleY2 = (nSampleY1 + nPitch) % nWidth;


					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];


					fScaleAcc += fScale;
					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScale = fScale / fBias;
				}

				// Scale to seed range
				fOutput[y * nWidth + x] = fNoise / fScaleAcc;
			}

			
	}
};

#endif