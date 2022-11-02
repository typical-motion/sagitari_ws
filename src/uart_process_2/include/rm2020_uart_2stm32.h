#ifndef _RM2020_UART_2STM32_H
#define _RM2020_UART_2STM32_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    uint8_t Head;//头
    uint8_t CmdID;//命令码
    uint16_t Datalength;//长度
}__attribute__((packed,aligned(1))) Frame_hearder;//帧头

typedef struct
{
    float x; //YAW
    float y; //PITCH
    float z; //距离
    float Time_Interval;	//延迟时间	
	uint8_t Goal_State;	//目标状态
}__attribute__((packed,aligned(1))) Auto_Aim_MOD;//自动瞄准

typedef struct
{
    float yaw;//单片机回传yaw角度
    float pitch;//单片机回传pitch角度
    uint8_t Mod_set_over;//模式设定
    uint8_t Red_Blue;
    uint8_t shoot_speed_mod;
}__attribute__((packed,aligned(1))) Reply_MOD;//单片机回传

typedef struct
{
    uint8_t Target_state;
}__attribute__((packed,aligned(1))) Error_MOD;//错误信息反馈

typedef struct
{
    Frame_hearder FH_data;//帧头
    union
    {
    Auto_Aim_MOD Am_data;//自瞄
    Reply_MOD Re_data;//回传
    Error_MOD Err_data;//错误
    }Data;
    uint16_t CRC16;//CRC16校验码
}__attribute__((packed,aligned(1))) Date_message;//整个数据帧

void send_message_AM(float xdata, float ydata, float zdata, float tdata,uint8_t Cmdata);
#endif 