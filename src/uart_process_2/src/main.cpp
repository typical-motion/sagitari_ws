#include <rm2020_uart_2stm32.h>
#include <rm2020_uart_thread_init.h>
#include <iostream>
#include <ros/ros.h>
#include <uart_process_2/uart_send.h>
#include <uart_process_2/uart_receive.h>


extern Date_message DOWN_DATA_AM;
extern int UART_ID;
extern int DATA_DOWN_Am;
extern bool INIT_UART();
extern bool ERROR_UART;
extern void *thread_read(void *arg);
extern void *thread_write(void* arg);
extern void send_message_AM(float xdata, float ydata, float zdata, float tdata, uint8_t Cmdata);//数据发送
ros::Publisher pub; //ros转发
uart_process_2::uart_send uart_Re_data;
void subCallback(uart_process_2::uart_send uart_data)
{
    send_message_AM(uart_data.xdata , uart_data.ydata , uart_data.zdata ,uart_data.tdata , (unsigned char)uart_data.Cmdata);
	// std::cout << (unsigned char )uart_data.Cmdata << std::endl;

	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << uart_data.xdata << std::endl;
	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << uart_data.ydata << std::endl;

}

int main(int argc , char** argv)
{
	ros::init(argc, argv, "uart_process_2");//ros初始化
	ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("uart_send", 1, subCallback);//ros转接
	pub = nh.advertise<uart_process_2::uart_receive>("uart_receive", 1);
    while(!INIT_UART())//done/64
	{
		ERROR_UART = true;
		std::cout<<"open fail!"<<std::endl;
		//return 0;
	}
	ERROR_UART = true;
	int ret;
	pthread_t Read_Uart;
	pthread_t Write_Uart;
	ret = pthread_create(&Read_Uart, NULL, thread_read, NULL);
	if(ret !=  0)
	{
		std::cout<< "read_fail"<<std::endl;
		//return 0;
	}
	ret = pthread_create(&Write_Uart, NULL, thread_write, NULL);
	if(ret != 0)
	{
		std::cout << "write_fail" <<std::endl;
	}
	ros::Rate loop_rate(150);
	while(ros::ok())
	{
		if(ERROR_UART)
		{
			if(INIT_UART())//done
			{
				ERROR_UART = false;
			}
			loop_rate.sleep();
		}
		ros::spinOnce();
	};
    return 0;
}