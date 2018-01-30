#include "include.h"

#define CMD_WARE     3
//发送图像到上位机显示
//不同的上位机，不同的命令
void vcan_sendware(uint8 *wareaddr, uint32 waresize)
{

    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    uart_putbuff(UART4, cmdf, sizeof(cmdf));    //先发送前命令
    uart_putbuff(UART4, wareaddr, waresize);    //发送数据
    uart_putbuff(UART4, cmdr, sizeof(cmdr));    //发送后命令

}