#pragma once

#include <iostream>
#include <map>
#include <string>

struct TextureInfo {
	TextureInfo() {};
	TextureInfo(unsigned char* T, unsigned int Width, unsigned int Height) {
		ptexture = T;
		tWidth = Width;
		tHeight = Height;
	}

	unsigned char * ptexture;
	unsigned int tWidth;
	unsigned int tHeight;
};

class Textures
{
public:
	Textures();
	~Textures();

public:
	unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight, const std::string tName);
	TextureInfo texture(const std::string tName) { return m_Textures[tName]; }

private:
	std::map<std::string, TextureInfo> m_Textures;

};

