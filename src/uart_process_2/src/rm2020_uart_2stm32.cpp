#include "rm2020_uart_2stm32.h"
#include "rm2020_uart_thread_init.h"
#include <semaphore.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <ros/ros.h>
#include <uart_process_2/uart_send.h>
#include <uart_process_2/uart_receive.h>
#include <dirent.h>
#define PATHNAME "/dev/ttyUSB0"//串口名称
#define RandRate B115200//波特率(B开头)
#define SEND_MESSAGE_LENGTH 23//上传数据长度
#define RECEIVE_MESSAGE_LENGTH 17//下载数据长度
typedef  char u8;

extern ros::Publisher pub;//ros转发
extern uart_process_2::uart_receive uart_Re_data;//ros转发数据
extern uart_process_2::uart_send uart_Se_data;//ros转发数据

int UART_ID;//串口句柄
bool ERROR_UART = false;//串口错误标示
Date_message DOWN_DATA_AM;//上传数据
int DATA_DOWN_Am = SEND_MESSAGE_LENGTH;//上传数据长度
Date_message UP_DATA_RE;//下载数据
int UP_DATA_Re = RECEIVE_MESSAGE_LENGTH;//下载数据长度
static unsigned short int Get_CRC16_Check_Sum( char *pchMessage,  int dwLength,  int wCRC);
void Append_CRC16_Check_Sum_Judge( char * pchMessage,  int dwLength);
bool Verify_CRC16_Check_Sum_Judge(char *pchMessage,  int dwLength);
bool set_uart_mode(speed_t speed, int vtime, int vmin);
bool INIT_UART();
unsigned short int CRC16_INIT_Judge = 0xffff;
bool realtimeFrame = false;


const char CRC8_INIT_Judge = 0xff;
const char CRC8_TAB_Judge[256] =
{
	0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
	0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
	0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
	0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
	0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
	0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
	0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
	0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
	0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
	0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
	0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
	0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
	0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
	0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
	0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
	0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};//CRC8校验表

const unsigned short int CRC16_Table_Judge[256] = 
{
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
	0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
	0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
	0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
	0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
	0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
	0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
	0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
	0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
	0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
	0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
	0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
	0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
	0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
	0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
	0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
	0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
	0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
	0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
	0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
	0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
	0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
	0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
	0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
	0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
	0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
	0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
	0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
	0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
	0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
	0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
	0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78

};//CRC16校验表

static unsigned short int Get_CRC16_Check_Sum( char *pchMessage,  int dwLength,  int wCRC)
{
	char chData;
	if (pchMessage == 0)
	{
		return 0xFFFF;
	}
	while (dwLength--)
	{
		chData = *pchMessage++;
		(wCRC) = (( int)(wCRC) >> 8) ^ CRC16_Table_Judge[(( int)(wCRC) ^
			( int)(chData)) & 0x00ff];
	}
	return wCRC;
}//CRC16算法，此处查表,获得添加在帧尾的CRC16校验码

void Append_CRC16_Check_Sum_Judge( char * pchMessage,  int dwLength)
{
	int wCRC = 0;
	if ((pchMessage == 0) || (dwLength <= 2))
	{
		return;
	}
	wCRC = Get_CRC16_Check_Sum((u8 *)pchMessage, dwLength - 2, CRC16_INIT_Judge);
	pchMessage[dwLength - 2] = (u8)(wCRC & 0x00ff);
	pchMessage[dwLength - 1] = (u8)((wCRC >> 8) & 0x00ff);
}//添加CRC16校验码到帧尾

bool Verify_CRC16_Check_Sum_Judge(char *pchMessage,  int dwLength) //校验回传数据的CRC16校验码
{
	unsigned short int wExpected = 0;
	if ((pchMessage == 0) || (dwLength <= 2))
	{
		return false;
	}
	wExpected = Get_CRC16_Check_Sum(pchMessage, dwLength - 2, CRC16_INIT_Judge);
	if(!((u8)(wExpected & 0x00ff) == pchMessage[dwLength - 2] &&
	 (u8)((wExpected >> 8) & 0x00ff) == pchMessage[dwLength - 1]))
	{
		printf("CRC = %x\n",wExpected);
		return false;
	}
	else
	{
		return true;
	}
	//printf("pchMessage[dwLength - 2] = %x\n", pchMessage[dwLength - 2]);
	//printf("(wExpected == %x\n", (char)(wExpected & 0x00ff) == pchMessage[dwLength - 2] && (char)((wExpected >> 8) & 0x00ff) == pchMessage[dwLength - 1]);
}

float char_P_2Float(char* data)//16进制字符数组转化为浮点数
{
	float float_data;
	float_data = *(float*)data;
	//for(size_t i = 0; i < 4; i++)
	//{
		//printf("data[%d] = %x\n",i,data[i]);
	//}
	return float_data;
}

void send_message_AM(float xdata, float ydata, float zdata, float tdata, uint8_t Cmdata)//数据发送
{
	memset(&DOWN_DATA_AM,0,sizeof(DOWN_DATA_AM));
	DOWN_DATA_AM.FH_data.Head = 0xA5;
	DOWN_DATA_AM.FH_data.CmdID = 0x01;
	DOWN_DATA_AM.FH_data.Datalength = 17;
	DOWN_DATA_AM.Data.Am_data.x = xdata;
	DOWN_DATA_AM.Data.Am_data.y = ydata;
	DOWN_DATA_AM.Data.Am_data.z = zdata;
	DOWN_DATA_AM.Data.Am_data.Time_Interval = tdata;//延迟时间
	DOWN_DATA_AM.Data.Am_data.Goal_State = Cmdata;//命令码
	Append_CRC16_Check_Sum_Judge(( char *)&DOWN_DATA_AM, DATA_DOWN_Am);//CRC16校验位
	realtimeFrame = true;
}

void receive_message_RE(Date_message* RE_data,char* coordinate_num)
{
	memset(RE_data, 0, sizeof(RE_data));
	RE_data->FH_data.Head = coordinate_num[0];
	//printf("RE_data->FH_data.Head = %x\n",coordinate_num[0]);
	RE_data->FH_data.CmdID = coordinate_num[1];
	char char_y_p[2][4] = {};//定义存储float类型数组
	char _length[2] = {};//定义存储uint16_t类型数组
	size_t n = 0;//获取float时，控制字节移位
	_length[0] = coordinate_num[2];//获取length长度
	_length[1] = coordinate_num[3];
	for(size_t i = 0;i < 2;i++)
	{
		for(size_t j = 0;j < 4;j++)
		{
			char_y_p[i][j] = coordinate_num[n+4];
			//printf("coordinate_num[%d] = %x\n",j,coordinate_num[n+4]);
			n++;
		}
	}
	RE_data->FH_data.Datalength = *(uint16_t*)_length;
	RE_data->Data.Re_data.yaw = char_P_2Float(char_y_p[0]);
	RE_data->Data.Re_data.pitch = char_P_2Float(char_y_p[1]);
	RE_data->Data.Re_data.Mod_set_over = coordinate_num[12];
	RE_data->Data.Re_data.Red_Blue = coordinate_num[13];
	RE_data->Data.Re_data.shoot_speed_mod = coordinate_num[14];
	RE_data->CRC16 = Get_CRC16_Check_Sum(coordinate_num, UP_DATA_Re - 2,CRC16_INIT_Judge);
	//*RE_data.FH_data.Datalength = (uint16_t)(coordinate_num[2] << 8 &
}

bool set_uart_mode(speed_t speed, int vtime, int vmin)//串口终端设置
{
	struct termios newtio;

	if(UART_ID<= 0)
	{
		printf("set_uart_mode failed---fd=%d\n",UART_ID);
		return -1;
	}	
	bzero(&newtio,sizeof(newtio));	 //置0
	newtio.c_iflag |= IGNBRK|BRKINT;	//忽略break或break中断
	newtio.c_cflag |= CLOCAL|CREAD;  //过位掩码的方式激活本地连接和接受使能选项
	newtio.c_cflag &= ~CSIZE;		//设置数据位
	newtio.c_cflag |= CS8;			//数据位为8位
	newtio.c_cflag &= ~PARENB;		//无奇偶校验
	cfsetispeed(&newtio,speed);   //设置波特率
	cfsetospeed(&newtio,speed);  
	newtio.c_cflag &= ~CSTOPB;		//1//  设置1位停止位
	newtio.c_cc[VTIME] = vtime; //等待时间，单位百毫秒 （读）。
	newtio.c_cc[VMIN] = vmin;	//最小字节数 （读）。
	tcflush(UART_ID,TCIFLUSH);	//tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来

	if ((tcsetattr(UART_ID, TCSANOW, &newtio)) != 0)   //激活与终端相关的参数。TCSANOW:立即执行
	{
		printf("set_uart_mode failed\n");
		return false;
	}
	printf("set_uart_mode\n"); 
	return true;
}

bool INIT_UART()//串口初始化
{
	static bool cout_flag = true;//显示错误信息
	UART_ID = open(PATHNAME,O_RDWR | O_NOCTTY);//打开文件的方式打开串口
	if(UART_ID < 0)
	{
		close(UART_ID);
		if(cout_flag)
		{
			printf("open UART3 fail\n");
			cout_flag = false;
		}
		usleep(100000);
		return false;
	}
	cout_flag = true;
	printf("open UART3 success\n");
	set_uart_mode(RandRate, 0, RECEIVE_MESSAGE_LENGTH * 2);//串口终端设置
	return true;
}//初始化

void *thread_read(void *arg)//数据读取线程
{
	int ret;
	while(true)
	{
		if(ERROR_UART == false)
		{
			char coordinate_num_temp[RECEIVE_MESSAGE_LENGTH * 2] = {};//定义数据帧
			char coordinate_num[RECEIVE_MESSAGE_LENGTH];
			ret = read(UART_ID,coordinate_num_temp,sizeof(coordinate_num_temp));
			for(int i = 0; i < RECEIVE_MESSAGE_LENGTH * 2 - RECEIVE_MESSAGE_LENGTH; i++)
			{
				if((unsigned char)coordinate_num_temp[i] == 0xA5 && (unsigned char)coordinate_num_temp[i+1] == 0x05)
				{
					for(int j = 0; j < RECEIVE_MESSAGE_LENGTH; j++)
					{
						coordinate_num[j] = coordinate_num_temp[i+j];
					}
					break;
				}
			}
		
			//std::cout << coordinate_num << std::endl;
			if((unsigned char)coordinate_num[0] == 0xA5 && (unsigned char)coordinate_num[1] == 0x05)
			{
				//printf("debug\n");
				//for(size_t i = 0; i < UP_DATA_Re; i++)
				//{
				//	printf("%x ",coordinate_num[i]);
				//}
				//std::cout << std::endl;
				if(Verify_CRC16_Check_Sum_Judge(coordinate_num,UP_DATA_Re))
				{
					receive_message_RE(&UP_DATA_RE,coordinate_num);
					//printf("get_message:\n");
					/*printf("pitch:%.4f\t yaw:%.4f \t Mod:%x\n\t Red_Blue:%x\n\t shoot_speed_mod:%x\n\t",
					UP_DATA_RE.Data.Re_data.pitch,
					UP_DATA_RE.Data.Re_data.yaw,
					UP_DATA_RE.Data.Re_data.Mod_set_over,
					UP_DATA_RE.Data.Re_data.Red_Blue,
					UP_DATA_RE.Data.Re_data.shoot_speed_mod);*/
					uart_Re_data.yaw = UP_DATA_RE.Data.Re_data.yaw;
					uart_Re_data.pitch = UP_DATA_RE.Data.Re_data.pitch;
					uart_Re_data.mod = UP_DATA_RE.Data.Re_data.Mod_set_over;
					uart_Re_data.red_blue = UP_DATA_RE.Data.Re_data.Red_Blue;
					uart_Re_data.shoot_speed_mod = UP_DATA_RE.Data.Re_data.shoot_speed_mod;
					pub.publish(uart_Re_data);
				}
			}
		}
		else
		{
			uart_Re_data.yaw = 0;
			uart_Re_data.pitch = 0;
			uart_Re_data.mod = 0;
			uart_Re_data.red_blue = 0;
			uart_Re_data.shoot_speed_mod = 0;
			pub.publish(uart_Re_data);
		}
	}
}

void *thread_write(void* arg)
{
	int ret;
	while(true)
	{
		//std::cout << "debug" << std::endl;
		//send_message_AM(1.5, 1.5, 2.0,  0.01,0);
		if(ERROR_UART == false)
		{
			ret = write(UART_ID,(char*)&DOWN_DATA_AM,DATA_DOWN_Am);
			if(ret < 0)
			{
				close(UART_ID);
				ERROR_UART = true;
			}
		}
		realtimeFrame = false;
		usleep(3000);
		if(uart_Se_data.predictLatency) {
			uart_Se_data.predictLatency = 0;
			double unitYaw = uart_Se_data.predictYaw - uart_Se_data.curYaw;
			double unitPitch = uart_Se_data.predictPitch - uart_Se_data.curPitch;
			double predictYaw = uart_Se_data.curYaw;
			double predictPitch = uart_Se_data.curPitch;
			for(int i = 0; i < uart_Se_data.predictLatency && realtimeFrame; i+= 3) {
				predictYaw += unitYaw;
				predictPitch += unitPitch;
				send_message_AM(predictYaw, predictPitch, uart_Se_data.curDistance, uart_Se_data.time + 3, (unsigned char)uart_Se_data.attackFlag);
				write(UART_ID,(char*)&DOWN_DATA_AM,DATA_DOWN_Am);
				usleep(3000);
			}
		}
	}
}


