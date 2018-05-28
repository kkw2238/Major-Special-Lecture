#include "stdafx.h"
#include "Renderer.h"
#include <random>
#include <chrono>
#include "LoadPng.h"
#include <Windows.h>

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	m_targetPointX = 1.0f;
	m_targetPointY = 0.0f;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_WaveShader = CompileShaders("./Shaders/Wave.vs", "./Shaders/Wave.fs");
	m_FragmentWaveShader = CompileShaders("./Shaders/FragmentWave.vs", "./Shaders/FragmentWave.fs");
	m_RaderShader = CompileShaders("./Shaders/Radar.vs", "./Shaders/Radar.fs");
	m_SamplerShader = CompileShaders("./Shaders/Sampler.vs", "./Shaders/Sampler.fs");
	m_VSWaveShader = CompileShaders("./Shaders/VSWave.vs", "./Shaders/VSWave.fs");
	m_PBOTexture[0] = CreatePngTexture("./Texture/DDing.png");

	CreateVSWaveVertex();

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

void Renderer::CreateVSWaveVertex()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 30;
	int pointCountY = 30;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX*pointCountY * 2];
	float* vertices = new float[(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3];
	gDummyVertexCount = (pointCountX - 1)*(pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y*pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y*pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);
}

void Renderer::DrawSTParticle(int sx, int sy, int ex, int ey, float time)
{
	glUseProgram(m_WaveShader);

	GLuint attribPosition = glGetAttribLocation(m_WaveShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	GLuint timeid = glGetUniformLocation(m_WaveShader, "u_Time");
	glUniform1f(timeid, time);

	GLuint startposid = glGetUniformLocation(m_WaveShader, "u_Startpos");
	glUniform2f(startposid, sx, sy);

	GLuint endposid = glGetUniformLocation(m_WaveShader, "u_Endpos");
	glUniform2f(endposid, ex, ey);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	// glVertexAttribPointer : Draw�� �����͸� �о ������ ũ�� �� ������ ����
		glVertexAttribPointer(attribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glPointSize(2.0f);
	// glDrawArrays : �������� ����
	glDrawArrays(GL_POINT, 0, 500);

	glDisableVertexAttribArray(m_VBORect);
}

void Renderer::DrawWaveParticle(float time)
{
	if (m_pCenterPosition.size() == 0)
		return;
	float newX, newY;
	m_fScale += 0.1f;

	glEnable(GL_BLEND);
	glUseProgram(m_FragmentWaveShader);

	int attribPosition = glGetAttribLocation(m_FragmentWaveShader, "a_Position");
	int attribColor = glGetAttribLocation(m_FragmentWaveShader, "a_Color");
	int upos = glGetUniformLocation(m_FragmentWaveShader, "u_Mid");
	int utime = glGetUniformLocation(m_FragmentWaveShader, "u_Scale");

	glUniform1f(utime, time);
	glUniform2fv(upos, m_pCenterPosition.size() / 2, m_pCenterPosition.data());

	glEnableVertexAttribArray(attribColor);
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);

	// glVertexAttribPointer : Draw�� �����͸� �о ������ ũ�� �� ������ ����
	glVertexAttribPointer(attribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	// glDrawArrays : �������� ����
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::DrawLine()
{
	glUseProgram(m_VSWaveShader);
	int attribPosition = glGetAttribLocation(m_VSWaveShader, "a_Position");
	int uniformTime = glGetUniformLocation(m_VSWaveShader, "u_Time");
	glUniform1f(uniformTime, m_fScale);
	m_fScale += 0.01f;

	unsigned int texID = GL_TEXTURE0;
	for (int i = 0; i < NUM_OF_TEXTURE; ++i) {
		glActiveTexture(texID);
		glBindTexture(GL_TEXTURE_2D, m_PBOTexture[i]);
		texID += 1;
	}

	glEnableVertexAttribArray(attribPosition);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);

	// glVertexAttribPointer : Draw�� �����͸� �о ������ ũ�� �� ������ ����
		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	
	// glDrawArrays : �������� ����
		glDrawArrays(GL_TRIANGLES, 0, gDummyVertexCount);

	glDisableVertexAttribArray(attribPosition);
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::Test(float* centers, float time ) // input 4 
{
	glUseProgram(m_SamplerShader);

	m_UniformID++;
	(m_UniformID %= 5) + 1;

	int uniformTex = glGetUniformLocation(m_SamplerShader, "uTexSampler");
	glUniform1i(uniformTex, 0);

	int uniformIndex = glGetUniformLocation(m_SamplerShader, "uIndex");
	glUniform1i(uniformIndex, m_UniformID);

	unsigned int texID = GL_TEXTURE0;
	for (int i = 0; i < NUM_OF_TEXTURE; ++i) {
		glActiveTexture(texID);
		glBindTexture(GL_TEXTURE_2D, m_PBOTexture[i]);
		texID += 1;
	}

	int attribPosition = glGetAttribLocation(m_SamplerShader, "Position");
	int attribTexPos = glGetAttribLocation(m_SamplerShader, "TexPos");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(attribTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextured);

	// glVertexAttribPointer : Draw�� �����͸� �о ������ ũ�� �� ������ ����
		glVertexAttribPointer(attribPosition,	3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
		glVertexAttribPointer(attribTexPos,		2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));
	// glDrawArrays : �������� ����
		glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribTexPos);
	glDisableVertexAttribArray(attribPosition);

	Sleep(1000);
}

void Renderer::DrawLader(float * centers, float time)
{
	float newX, newY;
	m_fScale += 0.1f;

	glEnable(GL_BLEND);
	glUseProgram(m_RaderShader);

	int attribPosition = glGetAttribLocation(m_RaderShader, "a_Position");
	int attribColor = glGetAttribLocation(m_RaderShader, "a_Color");
	int upos = glGetUniformLocation(m_RaderShader, "u_Mid");
	int utime = glGetUniformLocation(m_RaderShader, "u_Scale");

	glUniform1f(utime, time);
	glUniform2fv(upos, 4, centers);

	glEnableVertexAttribArray(attribColor);
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);

	// glVertexAttribPointer : Draw�� �����͸� �о ������ ũ�� �� ������ ����
	glVertexAttribPointer(attribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	// glDrawArrays : �������� ����
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::FillScreen(float r, float g, float b, float a)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	int attribColor = glGetUniformLocation(m_SolidRectShader, "u_Color");

	glUniform4f(attribColor, r, g, b, a);
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	// glVertexAttribPointer : Draw�� �����͸� �о ������ ũ�� �� ������ ����
	glVertexAttribPointer(attribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	// glDrawArrays : �������� ����
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
	glDisable(GL_BLEND);
}

void Renderer::SetTargetPoint(float x, float y)
{
	m_targetPointX = (x - m_WindowSizeX / 2) / (m_WindowSizeX / 2);
	m_targetPointY = (-y + m_WindowSizeY / 2) / (m_WindowSizeY / 2);

	m_pCenterPosition.push_back(m_targetPointX);
	m_pCenterPosition.push_back(m_targetPointY);
}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}


unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
{
	printf("Reading image %s\n", imagepath);
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;
	// Open the file
	FILE * file;
	fopen_s(&file, imagepath, "rb");
	
	if (!file)
	{
		printf("Image could not be opened\n");
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth * outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];
	
	fread(data, 1, imageSize, file);

	fclose(file);

	return data;
}

GLuint Renderer::CreatePngTexture(char * filePath)

{



	GLuint temp;

	glGenTextures(1, &temp);



	//Load Pngs

	// Load file and decode image.

	std::vector<unsigned char> image;

	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filePath);



	glBindTexture(GL_TEXTURE_2D, temp);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);



	return temp;

}