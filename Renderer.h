#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "Dependencies\glew.h"

struct float4 {
	float4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	float4(float inx, float iny, float inz, float inw) { x = inx; y = iny; z = inz; w = inw; }
	float x, y, z, w;
};

struct float3 {
	float3() { x = 0.0f; y = 0.0f; z = 0.0f; }
	float3(float inx, float iny, float inz) { x = inx; y = iny; z = inz; }
	float x, y, z;
};

struct VS_INPUT_LAYOUT {
	VS_INPUT_LAYOUT() { position = float4(0.0f, 0.0f, 0.0f, 0.0f); color = float4(0.0f, 0.0f, 0.0f, 0.0f); }
	VS_INPUT_LAYOUT(float x, float y, float z, float w, float r, float g, float b, float a) { 
		position = float4(x, y, z, w); 
		color = float4(r, g, b, a);
	}
	VS_INPUT_LAYOUT(float4 pos, float4 col) { position = pos; color = col; }
	float4 position;
	float4 color;
};

const int NUM_OF_TEXTURE = 1;


class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void Test(float* centers, float time);
	void DrawLader(float* centers, float time);
	void FillScreen(float r, float g, float b, float a);
	GLuint CreatePngTexture(char * filePath);
	void SetTargetPoint(float x, float y);
	unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);
public:
	void CreateVSWaveVertex();
	void DrawSTParticle(int sx, int sy, int ex, int ey, float time);
	void DrawWaveParticle(float time);
	void DrawLine();
	std::vector<float>		m_pCenterPosition;

private:
	bool ReadFile(char* filename, std::string *target);

	void Initialize(int windowSizeX, int windowSizeY);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	void GetGLPosition(float x, float y, float *newX, float *newY);

	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	
private:
	bool m_Initialized = false;

	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	float m_targetPointX, m_targetPointY;

	GLulong* m_tCheckerboard;

	GLuint m_VBORect = 0;
	GLuint m_VBOTextured = 0;
	GLuint m_SolidRectShader = 0;
	GLuint m_WaveShader = 0;
	GLuint m_FragmentWaveShader = 0;
	GLuint m_RaderShader = 0;
	GLuint m_SamplerShader = 0;
	GLuint m_VSWaveShader = 0;
	
	int m_UniformID = 0;

	// Leture2 
public:
	float	m_fScale = 0.0f;
	float*  m_fCenters;

	GLuint  m_VBOColor = 0;
	GLuint  m_VBOIndex = 0;
	GLuint	m_PBOTexture[NUM_OF_TEXTURE];
	
	unsigned int m_nVertexCount = 0;

	float m_StartPos[2] = { 0.0f, 0.0f };

private:
	int gDummyVertexCount = 0;
	unsigned char* texture;
};

