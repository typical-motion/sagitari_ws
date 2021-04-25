# Catkin Workspace
This is where everything happens.

## Build
1. Prerequisites 
To build camera_pkg, you will need 
```shell
wget http://download.huaraytech.com/pub/sdk/Ver2.1.0/Linux/MVViewer_2.1.0_Build20180129.run  
sudo ./MVViewer_2.1.0_Build20180129.run
```

To build camera_pkg_daheng, you will need
```shell
wget  http://gb.daheng-imaging.com/CN/Software/Cameras/Linux/Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122.tar.gz
tar xf Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122.tar.gz
cd Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122
sudo ./Galaxy_camera.run
```

Install Eigen3
```
sudo apt-get install libeigen3-dev
```