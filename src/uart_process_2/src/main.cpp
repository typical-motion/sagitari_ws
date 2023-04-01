#include <rm2020_uart_2stm32.h>
#include <rm2020_uart_thread_init.h>
#include <iostream>
#include <ros/ros.h>
#include <uart_process_2/uart_send.h>
#include <uart_process_2/uart_receive.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>

extern Date_message DOWN_DATA_AM;
extern int UART_ID;
extern int DATA_DOWN_Am;
extern bool INIT_UART();
extern bool ERROR_UART;
extern void *thread_read(void *arg);
extern void *thread_write(void *arg);
extern void send_message_AM(float xdata, float ydata, float zdata, float tdata, uint8_t Cmdata); //数据发送
ros::Publisher pub;																				 //ros转发
uart_process_2::uart_receive uart_Re_data;
uart_process_2::uart_send uart_Se_data;
bool predictingFrame = false;
void subCallback(uart_process_2::uart_send uart_data)
{
	send_message_AM(uart_data.curYaw, uart_data.curPitch, uart_data.curDistance, uart_data.time, (unsigned char)uart_data.attackFlag);

	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! yaw" << uart_data.curYaw << std::endl;
	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! pitch" << uart_data.curPitch << std::endl;

	uart_Se_data = uart_data;
	predictingFrame = false;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "uart_process_2"); //ros初始化
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("uart_send", 1, subCallback); //ros转接
	pub = nh.advertise<uart_process_2::uart_send>("uart_send", 1);

	//////////////////////////////////
	// static tf::TransformBroadcaster br;
	// tf::Transform transform;
	// //geometry_msgs::Quaternion qw;
	// tf::Quaternion q;
	//////////////////////////////////

	// while (!INIT_UART()) //done/64
	// {
	// 	ERROR_UART = true;
	// 	std::cout << "open fail!" << std::endl;
	// 	return -1;
	// }
	ERROR_UART = true;
	int ret;
	pthread_t Read_Uart;
	pthread_t Write_Uart;
	ret = pthread_create(&Read_Uart, NULL, thread_read, NULL);
	if (ret != 0)
	{
		std::cout << "read_fail" << std::endl;
		//return 0;
	}
	ret = pthread_create(&Write_Uart, NULL, thread_write, NULL);
	if (ret != 0)
	{
		std::cout << "write_fail" << std::endl;
	}
	ros::Rate loop_rate(200);
	while (ros::ok())
	{
		// if (ERROR_UART)
		// {
		// 	if (INIT_UART()) //done
		// 	{
		// 		ERROR_UART = false;
		// 	}
		// 	loop_rate.sleep();
		// }

		////////////////////////
		// transform.setOrigin(tf::Vector3(tvec_x,tvec_y,tvec_z));
		// transform.setRotation(q);
		// std::cout<<"发布tf变换: sendTransform函数"<<std::endl;
		// br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"base_link","link1"));
		// std::cout<<"输出的四元数为： w="<<q[3]<<",x="<<q[0]<<",y="<<q[1]<<",z="<<q[2]<<std::endl;
		////////////////////////

		pub.publish(uart_Se_data);
		uart_Se_data.curYaw ++;
		ros::spinOnce();
	};
	return 0;
}