# 更新日志

本文档记录项目的版本发布内容。

## v2.1.2

- 修复 Android 15 在 `getDisplayState` 中重复减少显示令牌引用计数导致的崩溃。
- 不再缓存 `GetDisplayInfo()` 返回的显示令牌，避免跨调用复用私有 `sp<>` 对象。

## v2.1.1

- 兼容 Android 16 的 `SurfaceComposerClient::mirrorSurface` 新符号签名。
- 镜像 Surface 按 LayerStack 正确释放，避免清理后遗留引用。
- 修复创建 Surface 时高度误用长边导致的横屏尺寸与触摸坐标异常。
- 增加镜像创建、销毁和缓存访问的互斥保护。

## v2.1.0

- 升级到 C++17 标准。
- 新增 Surface 清理函数。
- 修复重创建 Surface 问题。
- 添加防录屏功能。
- 修复采集卡画面异常。
- 修复 Android 15 画面旋转。
- 修复分辨率偏移问题。

## v2.0.0

- 基于原始 AndroidSurfaceImgui 项目。
- 支持 Android 5.0-16.0。
- 提供基础 ImGui 绘制功能。
