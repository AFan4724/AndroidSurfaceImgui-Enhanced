# AndroidSurfaceImgui C++17 Enhanced

## 项目介绍

本项目基于 [AndroidSurfaceImgui](https://github.com/Bzi-Han/AndroidSurfaceImgui) 进行修改和增强，是一个可以编译成Android可执行文件的项目，通过Android API创建Surface并进行Dear ImGui的绘制。

### 主要改进

- ✅ **C++17兼容性**：完全兼容C++17标准，提供更好的现代C++特性支持
- ✅ **增强的Surface管理**：新增清理Surface函数，确保资源正确释放
- ✅ **修复重创建问题**：解决了关闭后不能重新创建根Surface的问题
- ✅ **防录屏功能**：支持防录屏模式切换，保护敏感内容
- ✅ **广泛系统支持**：支持Android 5.0 - Android 16.0全版本
- ✅ **NDK构建系统**：使用ndk-build进行编译，简化构建流程

## 支持的Android版本

| 版本范围 | 支持状态 | 备注 |
|---------|---------|------|
| Android 5.0 - 5.1 | ✅ 完全支持 | API Level 21-22 |
| Android 6.0 | ✅ 完全支持 | API Level 23 |
| Android 7.0 - 7.1 | ✅ 完全支持 | API Level 24-25 |
| Android 8.0 - 8.1 | ✅ 完全支持 | API Level 26-27 |
| Android 9.0 | ✅ 完全支持 | API Level 28 |
| Android 10.0 | ✅ 完全支持 | API Level 29 |
| Android 11.0 | ✅ 完全支持 | API Level 30 |
| Android 12.0 - 12.1 | ✅ 完全支持 | API Level 31-32 |
| Android 13.0 | ✅ 完全支持 | API Level 33 |
| Android 14.0 | ✅ 完全支持 | API Level 34 |
| Android 15.0 | ✅ 完全支持 | API Level 35 |
| Android 16.0 | ✅ 完全支持 | API Level 36 |

## 环境要求

### 开发环境
- **Android NDK**: r21e 或更高版本
- **编译器**: 支持C++17的GCC/Clang
- **最低API Level**: 22 (Android 5.1)
- **目标架构**: arm64-v8a, armeabi-v7a, x86, x86_64

### 运行环境
- **Android设备**: Android 5.0及以上
- **权限要求**: 需要系统级权限或root权限
- **硬件要求**: 支持OpenGL ES 3.0或Vulkan的设备

## 快速开始

### 1. 克隆项目

```bash
git clone https://github.com/AFan4724/AndroidSurfaceImgui-Enhanced.git
cd AndroidSurfaceImgui-Enhanced
```

### 2. 编译项目

使用ndk-build进行编译：

```bash
# 设置NDK路径（如果未设置环境变量）
export NDK_ROOT=/path/to/your/ndk

# 编译所有架构
ndk-build

# 或编译特定架构
ndk-build APP_ABI=arm64-v8a
```

### 3. 部署到设备

```bash
# 推送到设备
adb push libs/arm64-v8a/imgui_chain_v2-1.0 /data/local/tmp/

# 设置执行权限
adb shell chmod 755 /data/local/tmp/imgui_chain_v2-1.0

# 运行程序
adb shell su -c "/data/local/tmp/imgui_chain_v2-1.0"
```

## 项目结构

```
AndroidSurfaceImgui-Enhanced/
├── jni/                          # NDK源码目录
│   ├── src/                      # 源代码
│   │   ├── main.cpp             # 程序入口
│   │   ├── Android_draw/        # 绘制相关
│   │   ├── Android_Graphics/    # 图形渲染管理
│   │   ├── Android_my_imgui/    # ImGui Android适配
│   │   ├── Android_touch/       # 触摸事件处理
│   │   ├── ImGui/              # Dear ImGui库
│   │   └── My_Utils/           # 工具函数
│   ├── include/                 # 头文件
│   ├── Android.mk              # NDK构建配置
│   └── Application.mk          # 应用配置
├── libs/                        # 编译输出目录
└── README.md                   # 项目文档
```

## 核心功能

### Surface管理

```cpp
// 创建Surface
::window = android::ANativeWindowCreator::Create("test", width, height, permeate_record);

// 清理Surface（新增功能）
android::ANativeWindowCreator::Cleanup();

// 销毁Surface
android::ANativeWindowCreator::Destroy(::window);
```

### 防录屏功能

```cpp
// 启用防录屏模式
bool permeate_record = false;  // false = 防录屏，true = 允许录屏

// 在创建Surface时设置
::window = android::ANativeWindowCreator::Create("test", width, height, permeate_record);
```

## 贡献指南

欢迎提交Issue和Pull Request！

1. Fork本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启Pull Request

## 许可证

本项目基于MIT许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 致谢

- 感谢 [Bzi-Han/AndroidSurfaceImgui](https://github.com/Bzi-Han/AndroidSurfaceImgui) 提供的原始项目基础
- 感谢 [Dear ImGui](https://github.com/ocornut/imgui) 团队提供优秀的GUI库
- 感谢所有贡献者和测试者

## 赞助

- 感谢 花椒鸡 赞助

## 更新日志

### v2.1.0 (当前版本)
- ✅ 升级到C++17标准
- ✅ 新增Surface清理函数
- ✅ 修复重创建Surface问题
- ✅ 添加防录屏功能
- ✅ 修复采集卡画面异常
- ✅ 修复安卓15画面旋转
- ✅ 修复分辨率偏移问题

### v2.0.0
- 基于原始AndroidSurfaceImgui项目
- 支持Android 5.0-16.0
- 基础ImGui绘制功能

---

**注意**: 本项目需要系统级权限才能正常运行，请确保在具有适当权限的环境中使用。 