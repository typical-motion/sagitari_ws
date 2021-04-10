    在工作空间中编译该包。
    节点：rm2020_uart_2stm32
    使用方法：在自己项目的包中，添加该依赖包。在需要使用通信的项目头文件中，包含
    #include <uart_process_2/uart_send.h>
    #include <uart_process_2/uart_receive.h>
    msg信息介绍：
        uart_send #上位机向下位机传输数据所用msg
            float32 xdata #yaw角度
            float32 ydata #pitch角度
            float32 zdata #距离
            float32 tdata #时间
            uint8 Cmdata #攻击标记
        uart_receive #下位机传输给上位机的msg
            float32 yaw #yaw角度
            float32 pitch #pitch角度
            uint8 mod #模式设置
            uint8 red_blue #红方蓝方
    话题使用：
        uart_send:发送瞄准数据到此话题
        uart_receive:在此话题中接收单片机数据
具体项目请到通信协议中查看.
