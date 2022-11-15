


// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "Application_mod.h"
#include <opencv2/opencv.hpp>
#include "image_combine.h"
#include <imfilebrowser.h>

class Dev_app :public Application<Dev_app>
{
private:
    GLuint texture_rgb, texture_alpha, texture_RGBA;
    cv::Mat RGB_image, Alpha_image, RGBA_image;
    ImGui::FileBrowser fileDialog;
public:
    Dev_app() = default;
    ~Dev_app() = default;
    void Startup()
    {
       RGB_image = cv::imread("C://RGB.jpg");
        cv::cvtColor(RGB_image, RGB_image, cv::COLOR_BGR2RGBA);

        Alpha_image = cv::imread("C://OnlyAlpha.png");
        cv::cvtColor(Alpha_image, Alpha_image, cv::COLOR_BGR2RGBA);

        

        GetSomeImages_andMerge(RGB_image, Alpha_image, RGBA_image);

        //!!!!!!
        //GLuint texture_rgb;
        glGenTextures(1, &texture_rgb);
        glBindTexture(GL_TEXTURE_2D, texture_rgb);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RGB_image.cols, RGB_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGB_image.data);

       // GLuint texture_alpha;
        glGenTextures(1, &texture_alpha);
        glBindTexture(GL_TEXTURE_2D, texture_alpha);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Alpha_image.cols, Alpha_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, Alpha_image.data);
        //GLuint texture_RGBA;

        glGenTextures(1, &texture_RGBA);
        glBindTexture(GL_TEXTURE_2D, texture_RGBA);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RGBA_image.cols, RGBA_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGBA_image.data);
    }
    void Update() {
        ImGui::Begin("RG_B", 0, ImGuiWindowFlags_MenuBar);                          // Create a window called "Hello, world!" and append into it.
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::Button("Open.."))
                {
                    fileDialog.Open();
                    /* авыа */ }
                fileDialog.Display();
                if (ImGui::MenuItem("Save")) { /* вар */ }
                if (ImGui::MenuItem("Close")) { /*ры */ }
                ImGui::EndMenu();
            }
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::EndMenuBar();
        }
        fileDialog.Display();
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture_rgb)), ImVec2(RGB_image.cols, RGB_image.rows));
        ImGui::End();

        ImGui::Begin("Alpha");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture_alpha)), ImVec2(Alpha_image.cols, Alpha_image.rows));
        ImGui::End();

        ImGui::Begin("RGBA");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture_RGBA)), ImVec2(RGBA_image.cols, RGBA_image.rows));
        ImGui::End();
        
        if (fileDialog.HasSelected())
        {
            std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
            fileDialog.ClearSelected();
        }
    }

};

int main(int, char**)
{
     
    Dev_app App;
    // create a file browser instance
    
    std::cout << __cplusplus << std::endl;
    
      // Main loop
  

       

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        
        //ImGui::ShowDemoWindow(&show_demo_window);
        ///
         

        


    App.Run();
        



        return 0;
    }
   
   

   

