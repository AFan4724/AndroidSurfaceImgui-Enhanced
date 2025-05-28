LOCAL_PATH := $(call my-dir)


# 引入freetype静态库 #
include $(CLEAR_VARS)
LOCAL_MODULE := lib_git_freetype
LOCAL_SRC_FILES := src/ImGui/misc/git_freetype/$(TARGET_ARCH_ABI)/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := AndroidSurfaceImguiEnhanced

LOCAL_CFLAGS := -std=c17
LOCAL_CFLAGS += -fvisibility=hidden
LOCAL_CPPFLAGS := -std=c++17
LOCAL_CPPFLAGS += -fvisibility=hidden
LOCAL_CPPFLAGS += -fexceptions

LOCAL_CPPFLAGS += -DVK_USE_PLATFORM_ANDROID_KHR
LOCAL_CPPFLAGS += -DIMGUI_IMPL_VULKAN_NO_PROTOTYPES
LOCAL_CPPFLAGS += -DIMGUI_DISABLE_DEBUG_TOOLS #禁用imgui调试工具
LOCAL_CPPFLAGS += -DIMGUI_ENABLE_FREETYPE     #启用imgui的freetype支持

#引入头文件到全局#
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Android_draw
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Android_Graphics
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Android_my_imgui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Android_touch
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/My_Utils
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ImGui/backends
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ImGui/misc/freetype
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ImGui/misc/git_freetype



LOCAL_SRC_FILES := src/main.cpp
LOCAL_SRC_FILES += src/Android_draw/draw_Gui.cpp
LOCAL_SRC_FILES += src/Android_touch/TouchHelperA.cpp
LOCAL_SRC_FILES += src/Android_Graphics/GraphicsManager.cpp
LOCAL_SRC_FILES += src/Android_Graphics/OpenGLGraphics.cpp
LOCAL_SRC_FILES += src/Android_Graphics/VulkanGraphics.cpp 
LOCAL_SRC_FILES += src/Android_Graphics/vulkan_wrapper.cpp
LOCAL_SRC_FILES += src/Android_my_imgui/AndroidImgui.cpp
LOCAL_SRC_FILES += src/Android_my_imgui/my_imgui.cpp
LOCAL_SRC_FILES += src/Android_my_imgui/my_imgui_impl_android.cpp
LOCAL_SRC_FILES += src/ImGui/imgui.cpp
LOCAL_SRC_FILES += src/ImGui/imgui_demo.cpp
LOCAL_SRC_FILES += src/ImGui/imgui_draw.cpp
LOCAL_SRC_FILES += src/ImGui/imgui_tables.cpp
LOCAL_SRC_FILES += src/ImGui/imgui_widgets.cpp
LOCAL_SRC_FILES += src/ImGui/backends/imgui_impl_android.cpp
LOCAL_SRC_FILES += src/ImGui/backends/imgui_impl_opengl3.cpp
LOCAL_SRC_FILES += src/ImGui/backends/imgui_impl_vulkan.cpp
LOCAL_SRC_FILES += src/ImGui/misc/freetype/imgui_freetype.cpp
LOCAL_SRC_FILES += src/My_Utils/stb_image.cpp
    


LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3
LOCAL_LDLIBS += -lz #freetype需要
LOCAL_STATIC_LIBRARIES := lib_git_freetype

include $(BUILD_EXECUTABLE) #可执行文件
