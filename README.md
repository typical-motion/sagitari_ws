# Sagitari Workspace

中维动力战队 RM2021 赛季自瞄代码框架，代号 Sagitari。


> 本项目仍在整理中。后续我们会重构本项目的部分代码，并补上相关文档，以提高可读性。  
> 我们非常欢迎你和我们讨论这方面的问题，一起进步。你可以在 **福建视觉交流群** 找到我们，我们的QQ群号是：938286676。


## 代码框架

本项目的各个模块代码均在 `src/` 下。
* `uart_process_2` 串口通信部分代码
* `camera_pkg_dahua` 大华相机驱动源码
* `camera_pkg_daheng` 大恒驱动相机源码
* `camera_file` 读取视频驱动源码
* `camera_usb_v4l` USB相机驱动源码
* `sagitari` 自瞄部分源码
* `sagitari_debug` 自瞄效果GUI源码


## 构建
1. 开发环境  
本项目基于 ROS kinetic 开发。运行的操作系统是 Ubuntu 18.04。  

2. 前置依赖  

编译 camera_pkg_dahua 包，你需要安装大华相机SDK：
```shell
wget http://download.huaraytech.com/pub/sdk/Ver2.1.0/Linux/MVViewer_2.1.0_Build20180129.run  
sudo ./MVViewer_2.1.0_Build20180129.run
```

编译 camera_pkg_daheng 包，你需要大恒相机SDK：
```shell
wget  http://gb.daheng-imaging.com/CN/Software/Cameras/Linux/Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122.tar.gz
tar xf Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122.tar.gz
cd Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122
sudo ./Galaxy_camera.run
```

安装 Eigen3
```
sudo apt-get install libeigen3-dev
```