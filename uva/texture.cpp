#define _CRT_SECURE_NO_WARNINGS
#include "texture.h"
#include "Utils.h"

unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;

		//转码成rgb
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}

		return pixelData;
	}
	else
	{
		return nullptr;
	}
}

void Texture::Init(const char* imagePath)
{
	//加载图片文件到内存中
	unsigned char* imageFileContent = LoadFileContent(imagePath);

	//解码
	int width = 0, height = 0;
	unsigned char* pixelData = DecodeBMP(imageFileContent, width, height);
	//生成opengl图片
	glGenTextures(1, &mTextureID);

	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//纹理从内存传到显存
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete imageFileContent;
}