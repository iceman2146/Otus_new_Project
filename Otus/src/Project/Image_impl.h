#pragma once
#include "Application_mod.h"
#include <opencv2/opencv.hpp>
#include "image_combine.h"
//#include <imfilebrowser.h>

#include <string>;

class Image
{
private:
	GLuint GL_name;
	cv::Mat Material;
	std::string path;
	void Update_glTexture();
	//static bool showFileBrowser = false;
public:
	Image() = default;
	~Image() = default;
	void Read_image(std::string);
	void PrintImage(const char*);
	cv::Mat GetMaterial();
	void SetMaterial(cv::Mat&);
	void SaveImage(std::string);


};
void Image::Read_image(std::string pathToTexture)
{
	Material = cv::imread(pathToTexture);
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
	
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{

			if (ImGui::MenuItem("Close"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (ImGui::Begin(name, NULL, ImGuiWindowFlags_MenuBar)) 
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				//ifd::FileDialog::Instance().Open("TextureOpenDialog", "Open a shader", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*", true);
				if (ImGui::MenuItem("Load"))
				{
					/*if (ifd::FileDialog::Instance().IsDone("TextureOpenDialog")) {
						if (ifd::FileDialog::Instance().HasResult()) {
							std::string res = ifd::FileDialog::Instance().GetResult().u8string();
							printf("DIRECTORY[%s]\n", res.c_str());
						}
						ifd::FileDialog::Instance().Close();
					}*/
						
				}
				if (ImGui::MenuItem("Close"))
				{
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(GL_name)), ImVec2(Material.cols, Material.rows));
	
	
	}
	ImGui::End();
}
cv::Mat Image::GetMaterial()
{
	return Material;
}
void Image::SetMaterial(cv::Mat &InputMaterialToSet)
{
	Material = InputMaterialToSet;
	Update_glTexture();
}
