

#include "Application_mod.h"
#include <opencv2/opencv.hpp>
#include "image_combine.h"
#include <imfilebrowser.h>
#include <string>;
#include "Image_impl.h"
//static bool show_app_dockspace = true;
//static void ShowDockingDisabledMessage()
//{
//	ImGuiIO& io = ImGui::GetIO();
//	ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
//	ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
//	ImGui::SameLine(0.0f, 0.0f);
//	if (ImGui::SmallButton("click here"))
//		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//}
//void ShowDockSpace(bool* p_open)
//{
//	// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
//	// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
//	// In this specific demo, we are not using DockSpaceOverViewport() because:
//	// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
//	// - we allow the host window to have padding (when opt_padding == true)
//	// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
//	// TL;DR; this demo is more complicated than what you would normally use.
//	// If we removed all the options we are showcasing, this demo would become:
//	//     void ShowExampleAppDockSpace()
//	//     {
//	//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
//	//     }
//
//	static bool opt_fullscreen = true;
//	static bool opt_padding = false;
//	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
//
//	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
//	// because it would be confusing to have two docking targets within each others.
//
//	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
//	if (opt_fullscreen)
//	{
//		const ImGuiViewport* viewport = ImGui::GetMainViewport();
//		ImGui::SetNextWindowPos(viewport->WorkPos);
//		ImGui::SetNextWindowSize(viewport->WorkSize);
//		ImGui::SetNextWindowViewport(viewport->ID);
//		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
//		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
//		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
//	}
//	else
//	{
//		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
//	}
//
//	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
//	// and handle the pass-thru hole, so we ask Begin() to not render a background.
//	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
//		window_flags |= ImGuiWindowFlags_NoBackground;
//
//	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
//	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
//	// all active windows docked into it will lose their parent and become undocked.
//	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
//	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
//	if (!opt_padding)
//		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//	ImGui::Begin("DockSpace Demo", p_open, window_flags);
//	if (!opt_padding)
//		ImGui::PopStyleVar();
//
//	if (opt_fullscreen)
//		ImGui::PopStyleVar(2);
//
//	// Submit the DockSpace
//	ImGuiIO& io = ImGui::GetIO();
//	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
//	{
//		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
//		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
//	}
//	else
//	{
//		ShowDockingDisabledMessage();
//	}
//
//	//if (ImGui::BeginMenuBar())
//	//{
//		//if (ImGui::BeginMenu("Menu"))
//		//{
//			// Disabling fullscreen would allow the window to be moved to the front of other windows,
//			// which we can't undo at the moment without finer window depth/z control.
//		   /* ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
//			ImGui::MenuItem("Padding", NULL, &opt_padding);
//			ImGui::Separator();
//
//			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
//			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
//			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
//			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
//			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
//			ImGui::Separator();
//
//			if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
//				*p_open = false;*/
//			//ImGui::MenuItem("Export", NULL, false, p_open != NULL);
//			//ImGui::Separator();
//			//ImGui::MenuItem("Close", NULL, false, p_open != NULL);
//			//ImGui::EndMenu();
//		//}
//
//
//		//ImGui::EndMenuBar();
//	//}
//
//	//ImGui::End();
//}
class Dev_app :public Application<Dev_app>
{
private:

	//GLuint texture_rgb, texture_alpha, texture_RGBA;
	GLuint texture_RGBA;
	//cv::Mat RGB_image, Alpha_image, RGBA_image;
	cv::Mat RGBA_image;
	ImGui::FileBrowser fileDialog;
	Image RGB, OnlyAlpha, RGBA;
public:
	Dev_app() = default;
	~Dev_app() = default;
	void Startup()
	{

		RGB.Read_image("C://RGB.jpg");
		OnlyAlpha.Read_image("C://OnlyAlpha.png");


		GetSomeImages_andMerge(RGB.GetMaterial(), OnlyAlpha.GetMaterial(), RGBA_image);


		GLuint texture_RGBA;
		glGenTextures(1, &texture_RGBA);
		glBindTexture(GL_TEXTURE_2D, texture_RGBA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RGBA_image.cols, RGBA_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGBA_image.data);
	}
	void Update() {
		//ShowDockSpace(&show_app_dockspace);
		ImGui::Begin("RGB+A", 0, ImGuiWindowFlags_NoBackground);
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Menu"))
				{
					ImGui::MenuItem("Export", NULL, false, 1 != NULL);
					ImGui::Separator();
					ImGui::MenuItem("Close", NULL, false, 1 != NULL);
					ImGui::EndMenu();
				}


				ImGui::EndMenuBar();


				//ImGui::BeginMenuBar();
				//if (ImGui::Button("Open.."))
				//{
				//	//fileDialog.Open();
				//	/* авыа */
				//}
				////fileDialog.Display();
				//if (ImGui::MenuItem("Save")) { /* вар */ }
				//if (ImGui::MenuItem("Close")) { /*ры */ }
				//ImGui::EndMenu();

			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			}
			//fileDialog.Display();
			ImGui::End();
			RGB.PrintImage("RGB");

			OnlyAlpha.PrintImage("Alpha");

			/*ImGui::Begin("RGBA");
			ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture_RGBA)), ImVec2(RGBA_image.cols, RGBA_image.rows));
			ImGui::End();*/

			/*if (fileDialog.HasSelected())
			{
				std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;

				fileDialog.ClearSelected();
			}*/
			//RGBA.PrintImage("RGBA");
			ImGui::ShowDemoWindow();
		}

	};
	//void Test() {
	//	Image RGB, OnlyAlpha, RGBA;
	//	RGB.Read_image("C://RGB.jpg");
	//	OnlyAlpha.Read_image("C://OnlyAlpha.png");
	//
	//}

	int main(int, char**)
	{

		Dev_app App;

		std::cout << __cplusplus << std::endl;

		App.Run();




		return 0;
	}




};
