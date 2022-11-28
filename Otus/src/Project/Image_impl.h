#pragma once
#include <opencv2/opencv.hpp>
#include "image_combine.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <string>
#include <filesystem>
#include <iostream>

class Image
{
private:
	GLuint GL_name;
	cv::Mat Material;
	std::string path;
	void Update_glTexture();
	//static bool showFileBrowser = false;
	std::string ext;
public:
	Image() {
		Material.create(512, 512, CV_8UC4);
	}
	~Image() = default;
	void Read_image(std::string);
	void PrintImage(const char*);
	cv::Mat GetMaterial();
	void SetMaterial(cv::Mat&);
	void SaveImage(std::string);

	GLuint GetName();

};

void Image::Read_image(std::string pathToTexture)
{
	Material = cv::imread(pathToTexture);
	std::cout<<Material.type()<<std::endl;
	cv::cvtColor(Material, Material, cv::COLOR_BGR2RGBA);
	Update_glTexture();
}

void Image::Update_glTexture()
{
	glGenTextures(1, &GL_name);
	glBindTexture(GL_TEXTURE_2D, GL_name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Material.cols, Material.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, Material.data);


}
void Image::SaveImage(std::string PathToSave)
{
	cv::imwrite(PathToSave, Material);

}
void Image::PrintImage(const char* name)
{
	ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(GL_name)), ImVec2(Material.cols, Material.rows));
}
cv::Mat Image::GetMaterial()
{
	return Material;
}
GLuint Image::GetName()
{
	return GL_name;
}
void Image::SetMaterial(cv::Mat& InputMaterialToSet)
{
	Material = InputMaterialToSet;
	Update_glTexture();
}
