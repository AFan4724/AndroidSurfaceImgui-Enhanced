#include "draw.h"

#include "My_font/zh_Font.h"
#include "My_font/fontawesome-brands.h"
#include "My_font/fontawesome-regular.h"
#include "My_font/fontawesome-solid.h"
#include "My_font/gui_icon.h"
   
#include "My_icon/pic_ZhenAiKun_png.h"

bool permeate_record = false;
bool permeate_record_ini = false;
struct Last_ImRect LastCoordinate = {0, 0, 0, 0};


std::unique_ptr<AndroidImgui> graphics;
ANativeWindow *window = NULL; 
android::ANativeWindowCreator::DisplayInfo displayInfo;// 屏幕信息
ImGuiWindow *g_window = NULL;// 窗口信息
int abs_ScreenX = 0, abs_ScreenY = 0;// 绝对屏幕X _ Y
int native_window_screen_x = 0, native_window_screen_y = 0;

TextureInfo Aekun_image{};

ImFont* zh_font = NULL;
ImFont* icon_font_0 = NULL;
ImFont* icon_font_1 = NULL;
ImFont* icon_font_2 = NULL;



bool M_Android_LoadFont(float SizePixels) {
    ImGuiIO &io = ImGui::GetIO();
    
    //ImFontConfig config; //oppo字体部分
    //config.FontDataOwnedByAtlas = false;
    //config.SizePixels = SizePixels;
    //config.OversampleH = 1;
    //::zh_font = io.Fonts->AddFontFromMemoryTTF((void *)OPPOSans_H, OPPOSans_H_size, 0.0f, &config, io.Fonts->GetGlyphRangesChineseFull());    
    ////io.Fonts->AddFontDefault(&config);

	static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3.0;
    icons_config.OversampleV = 3.0;		
    icons_config.SizePixels = SizePixels;
    //icons_config.GlyphOffset.y += 7.0f; // 通过 GlyphOffset 调整单个字形偏移量，向下偏移 size 像素
	::icon_font_0 = io.Fonts->AddFontFromMemoryCompressedTTF((const void *)&font_awesome_brands_compressed_data, sizeof(font_awesome_brands_compressed_data), 0.0f, &icons_config, icons_ranges);
	::icon_font_1 = io.Fonts->AddFontFromMemoryCompressedTTF((const void *)&font_awesome_regular_compressed_data, sizeof(font_awesome_regular_compressed_data), 0.0f, &icons_config, icons_ranges);
	::icon_font_2 = io.Fonts->AddFontFromMemoryCompressedTTF((const void *)&font_awesome_solid_compressed_data, sizeof(font_awesome_solid_compressed_data), 0.0f, &icons_config, icons_ranges);

    io.Fonts->AddFontDefault();
    return zh_font != nullptr;
}
void init_My_drawdata() {
    ImGui::StyleColorsDark(); //白色
    ImGui::My_Android_LoadSystemFont(25.0f); //(加载系统字体 安卓15完美适配)
    M_Android_LoadFont(25.0f); //加载字体(还有图标)
    ImGui::GetStyle().ScaleAllSizes(3.25f);
    ::Aekun_image = graphics->LoadTextureFromMemory((void *)picture_ZhenAiKun_PNG_H, sizeof(picture_ZhenAiKun_PNG_H));
}


void screen_config() {
    ::displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
}

void drawBegin() {
    if (::permeate_record_ini) {
        LastCoordinate.Pos_x = ::g_window->Pos.x;
        LastCoordinate.Pos_y = ::g_window->Pos.y;
        LastCoordinate.Size_x = ::g_window->Size.x;
        LastCoordinate.Size_y = ::g_window->Size.y;

        graphics->Shutdown();
        android::ANativeWindowCreator::Destroy(::window);
        ::window = android::ANativeWindowCreator::Create("AImGui", native_window_screen_x, native_window_screen_y, permeate_record);
        graphics->Init_Render(::window, native_window_screen_x, native_window_screen_y);
        ::init_My_drawdata(); //初始化绘制数据
    } 


    static uint32_t orientation = -1;
    screen_config();
    if (orientation != displayInfo.orientation) {
        orientation = displayInfo.orientation;
        Touch::setOrientation((int)displayInfo.orientation);
        if (g_window != NULL) {
            g_window->Pos.x = 100;
            g_window->Pos.y = 125;        
        }        
        //cout << " width:" << displayInfo.width << " height:" << displayInfo.height << " orientation:" << displayInfo.orientation << endl;
    }
}


void Layout_tick_UI(bool *main_thread_flag) {
    static bool show_draw_Line = false;
    static bool show_demo_window = false;
    static bool show_another_window = false;
    { 
        static float f = 0.0f;
        static int counter = 0;
        static int style_idx = 0;
        static ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        ImGui::Begin("AndroidSurfaceImguiEnhanced", main_thread_flag);  // Create a window called "Hello, world!" and append into it.
        if (::permeate_record_ini) {
            ImGui::SetWindowPos({LastCoordinate.Pos_x, LastCoordinate.Pos_y});
            ImGui::SetWindowSize({LastCoordinate.Size_x, LastCoordinate.Size_y});
            permeate_record_ini = false;   
        }
        ImGui::Text("渲染接口 : %s, gui版本 : %s", graphics->RenderName, ImGui::GetVersion());               // Display some text (you can use a format strings too)
		if (ImGui::Combo("##主题", &style_idx, "白色主题\0蓝色主题\0紫色主题\0")) {
			switch (style_idx) {
				case 0: ImGui::StyleColorsLight(); break;
				case 1: ImGui::StyleColorsDark(); break;
				case 2: ImGui::StyleColorsClassic(); break;
			}
		}
		
        if (ImGui::Checkbox("过录制", &::permeate_record)) {
            ::permeate_record_ini = true;
        }
            
        ImGui::Checkbox("演示窗口", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::SameLine();
        ImGui::Checkbox("绘制射线", &show_draw_Line);
        ImGui::Checkbox("坤坤窗口", &show_another_window);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit4("取色器", (float *) &clear_color); // Edit 3 floats representing a color
        if (ImGui::Button("Button")) {
            counter++;
        }
        
        ImGui::SameLine();
        ImGui::Text("计数 = %d", counter);
        ImGui::Text("窗口集中 = %d", ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "应用平均 %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        g_window = ImGui::GetCurrentWindow();
        ImGui::End();
    }
    
        
    if (show_another_window) { // 3. Show another simple window.
        ImGui::Begin("另一个窗口", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("另一个窗口的 爱坤!");
        ImGui::Image(Aekun_image.DS, ImVec2(170, 170));
        if (ImGui::Button("关闭这个坤口")) {
            show_another_window = false;
        }
        ImGui::End();
    }
            
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    if (show_draw_Line)
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(0,0),ImVec2(displayInfo.width, displayInfo.height),IM_COL32(255,0,0,255),4);

}
