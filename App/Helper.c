#include "include.h"

#define CMD_WARE     3
//����ͼ����λ����ʾ
//��ͬ����λ������ͬ������
void vcan_sendware(uint8 *wareaddr, uint32 waresize)
{

    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    uart_putbuff(UART4, cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    uart_putbuff(UART4, wareaddr, waresize);    //��������
    uart_putbuff(UART4, cmdr, sizeof(cmdr));    //���ͺ�����

}