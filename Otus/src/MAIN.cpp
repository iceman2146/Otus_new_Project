

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "image_impl.h"
#include <stdio.h>
#include "time.h"

#include "ImFileDialog.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> 


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
//
//
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
static void ShowDockingDisabledMessage()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
	ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
	ImGui::SameLine(0.0f, 0.0f);
	if (ImGui::SmallButton("click here"))
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}
void ShowMYAppDockSpace(bool* p_open)
{


	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		ShowDockingDisabledMessage();
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{

			ImGui::MenuItem("Export", NULL, false, p_open != NULL);

			ImGui::Separator();
			ImGui::MenuItem("Close", NULL, false, p_open != NULL);
			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}

	ImGui::End();
}
void ShowMYApp3dView()
{
	ImGui::Begin("3dView");
	ImGui::End();

}
const char* glfw_init()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		std::exit(1);
	}

	glfwInit();
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	return glsl_version;
}
GLFWwindow* CreateOpenglWindow(int width, int height, std::string name)
{

	GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (window == NULL)
		std::exit(1);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	return window;

}
int main(int, char**)
{

	const char* glsl_version = glfw_init();//инициалиция контекста опенгл
	// Create window with graphics context
	GLFWwindow* window = CreateOpenglWindow(1024, 768, "ImageChanger");
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	io.ConfigViewportsNoTaskBarIcon = true;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	//Объявления для IMFileDialog
	ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void*
	{
		GLuint tex;

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);

		return (void*)tex;
	};
	ifd::FileDialog::Instance().DeleteTexture = [](void* tex) {
		GLuint texID = (GLuint)tex;
		glDeleteTextures(1, &texID);
	};


	// Our state
	static bool show_app_dockspace = true;
	bool show_demo_window = false;
	bool show_another_window = false;
	static bool showFileBrowser = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	Image RGB;
	Image Alpha;
	Image RGBA;
	cv::Mat RGBA_Mat;
	RGB.Read_image("C://RGB.jpg");
	Alpha.Read_image("C://OnlyAlpha.png");
	GetSomeImages_andMerge(RGB.GetMaterial(), Alpha.GetMaterial(), RGBA_Mat);
	RGBA.SetMaterial(RGBA_Mat);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		//!!!!
		ShowMYAppDockSpace(&show_app_dockspace);
		ShowMYApp3dView();
		//ShowMYBaseTextures();
		if (ImGui::Begin("BaseTextures", NULL))
		{


			{
				ImGui::BeginChild("Child", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y),
					false, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
				if (ImGui::BeginTabBar("RGB+Alpha", ImGuiTabBarFlags_Reorderable))
				{

					if (ImGui::BeginTabItem("RGB"))
					{
						if (ImGui::Button("Load.."))
							ifd::FileDialog::Instance().Open("BaseTextureOpenDialog",
								"Open a shader",
								"Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*",
								true);
						ImGui::SameLine();


						RGB.PrintImage("RGB");

						ImGui::EndTabItem();


					}
					if (ImGui::BeginTabItem("A"))
					{
						if (ImGui::Button("Load.."))
							ifd::FileDialog::Instance().Open("AlphaTextureOpenDialog",
								"Open a shader",
								"Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*",
								true);
						ImGui::SameLine();
						Alpha.PrintImage("A");
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
					ImGui::EndChild();
				}

				if (ifd::FileDialog::Instance().IsDone("BaseTextureOpenDialog")) {
					if (ifd::FileDialog::Instance().HasResult()) {
						const std::vector<std::filesystem::path>& res = ifd::FileDialog::Instance().GetResults();
						for (const auto& r : res)
							// ShaderOpenDialog supports multiselection
							printf("OPEN[%s]\n", r.u8string().c_str());
						// std::cout << res.capacity();
						RGB.Read_image(ifd::FileDialog::Instance().GetResult().u8string());
						GetSomeImages_andMerge(RGB.GetMaterial(), Alpha.GetMaterial(), RGBA_Mat);
						RGBA.SetMaterial(RGBA_Mat);
					}
					ifd::FileDialog::Instance().Close();
				}
				if (ifd::FileDialog::Instance().IsDone("AlphaTextureOpenDialog")) {
					if (ifd::FileDialog::Instance().HasResult()) {
						const std::vector<std::filesystem::path>& res = ifd::FileDialog::Instance().GetResults();
						for (const auto& r : res)
							// ShaderOpenDialog supports multiselection
							printf("OPEN[%s]\n", r.u8string().c_str());
						// std::cout << res.capacity();
						Alpha.Read_image(ifd::FileDialog::Instance().GetResult().u8string());
						GetSomeImages_andMerge(RGB.GetMaterial(), Alpha.GetMaterial(), RGBA_Mat);
						RGBA.SetMaterial(RGBA_Mat);
					}
					ifd::FileDialog::Instance().Close();
				}

			}

			ImGui::End();
		}
		if (ImGui::Begin("OptionalTextures", NULL))
			//RGBA.PrintImage("RGBA");
		{


			{
				ImGui::BeginChild("Child", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y),
					false, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
				if (ImGui::BeginTabBar("Alpha", ImGuiTabBarFlags_Reorderable))
				{

					if (ImGui::BeginTabItem("Alpha"))
					{
						if (ImGui::Button("Save.."))
							ifd::FileDialog::Instance().Save("RGBATextureSaveDialog", "SaveTexture",
								"Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
						ImGui::SameLine();


						RGBA.PrintImage("RGBA");

						ImGui::EndTabItem();


					}

					ImGui::EndTabBar();
					ImGui::EndChild();
				}


				if (ifd::FileDialog::Instance().IsDone("RGBATextureSaveDialog")) {
					if (ifd::FileDialog::Instance().HasResult()) {
						std::string res = ifd::FileDialog::Instance().GetResult().u8string();
						printf("SAVE[%s]\n", res.c_str());
						RGBA.SaveImage(ifd::FileDialog::Instance().GetResult().u8string());
					}
					ifd::FileDialog::Instance().Close();
				}

			}
			ImGui::End();
		}



		ImGui::ShowDemoWindow();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
