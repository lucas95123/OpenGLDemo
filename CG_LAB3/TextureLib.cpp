#include "TextureLib.h"


TextureLib::TextureLib()
{
}


TextureLib::~TextureLib()
{
}

int TextureLib::getTextureID(std::string textureName)
{
	return textureMap[textureName];
}

int TextureLib::addTexture(std::string textureName)
{
	int width, height;
	byte *image, t;          //����ͼ������
	FILE *fp;            //�ļ�ָ��
	BITMAPFILEHEADER FileHeader;    //����λͼ�ļ�ͷ
	BITMAPINFOHEADER InfoHeader;    //����λͼ��Ϣͷ
	fp = fopen(textureName.c_str(), "rb");
	if (fp == NULL)
	{
		perror("LoadBitmap");        //���ļ�ʧ��
		return -1;
	}
	fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	if (FileHeader.bfType != 0x4D42)  //ȷ���ļ���һ��λͼ�ļ���Ч���ļ�����
	{
		printf("Error: This file is not a bmp file!");
		fclose(fp);
		return -1;
	}
	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	width = InfoHeader.biWidth;
	height = InfoHeader.biHeight;
	if (InfoHeader.biSizeImage == 0)          //ȷ��ͼ�����ݵĴ�С
	{
		InfoHeader.biSizeImage = width*height * 3;
	}
	fseek(fp, FileHeader.bfOffBits, SEEK_SET);  //���ļ�ָ���ƶ���ʵ��ͼ�����ݴ�
	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage); //����ռ�
	if (image == NULL)
	{
		free(image);
		printf("Error: No enough space!");
		return -1;
	}
	fread(image, 1, InfoHeader.biSizeImage, fp);
	for (unsigned int i = 0; i < InfoHeader.biSizeImage; i += 3)
	{
		t = image[i];
		image[i] = image[i + 2];
		image[i + 2] = t;
	}
	fclose(fp);
	unsigned int ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width,
		height, GL_RGB, GL_UNSIGNED_BYTE,
		image);
	textureMap[textureName] = ID;
	return ID;
}
