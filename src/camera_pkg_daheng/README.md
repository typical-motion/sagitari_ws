# camera_pkg_daheng

#### 介绍
大恒工业相机包<br>
该程序负责人联系方式:<br>
吴佳宗<br>
qq邮箱:676895384@qq.com <br>
qq:676895384<br>
微信:wjz20000918<br>

#### 使用方法
使用之前，需安装大恒工业相机官方SDK[SDK下载链接](http://gb.daheng-imaging.com/CN/Software/Cameras/Linux/Galaxy_Linux-x86_Gige-U3_32bits-64bits_1.2.1911.9122.tar.gz)，将lib文件放置到/usr/lib 下<br>
    可通过修改代码，调节相机曝光、白平衡、图像ROI，并发送ROS图片信息image至话题中<br>
    话题:DahuaCamera/LowDims
    大小:1280*1024
    这两项数据都可通过修改代码调整