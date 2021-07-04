//*************************************************
//第一部分 申明引用函数文件
#include "mbed.h"

//第二部分 申明接口主要接口列表如下
/*
        LED1        = PA_5,       LED1
    LED2        = PA_5,       LED2 
    LED3        = PA_5,       LED3
    LED4        = PA_5,       LED4
    USER_BUTTON = PC_13,      用户按键
    SERIAL_TX   = PA_2,       串口发送
    SERIAL_RX   = PA_3,       串口接受
    USBTX       = PA_2,       USB发送
    USBRX       = PA_3,       USB接收
    I2C_SCL     = PB_8,       IIC的时钟线
    I2C_SDA     = PB_9,       IIC的数据线
    SPI_MOSI    = PA_7,       SPI的主设备输出/从设备输入
    SPI_MISO    = PA_6,       SPI的主设备输入/从设备输出
    SPI_SCK     = PA_5,       SPI的时钟
    SPI_CS      = PB_6,       SPI的片选信号
    PWM_OUT     = PB_3,       PWM输出
*/
//DigitalOut myled(LED1);           //定义LED1为输出
//InterruptIn key_init(USER_BUTTON);   //定义了用户按键为中断

//中断函数
int ended;
int count;
int timeout;
Timer t;
int buf[200];
void get_reply();
int flag[] = {31,32,33,34,35,36};
double vals[] = {12.5,1.324,1.456};
Serial outS1(PA_11,PA_12,9600);
void led_turn()
{
    //myled=!myled;
}

//主函数 通过按键切换LED灯的亮暗
int main(){
    //当按键电平产生下降沿 进入中断 
    //key_init.fall(&led_turn); 
		int x;
    while(1){
			get_reply();
			for(int i=0;i<6;++i){
					x = buf[i];
					printf("%d",x);
					
			}
			
				outS1.printf("123456");
			
			printf("\n");
		}
}
void get_reply()
{    

		while(!outS1.readable()){}
		timeout =1;
    memset(buf, '\0', sizeof(buf));//buf��ʼ��
    t.start();
    ended=0;count=0;
		
    while(!ended) {
        if(outS1.readable()) {
            buf[count] = outS1.getc();count++;
            }
        if(t.read() > timeout) {
                ended = 1;t.stop();t.reset();
            }
        }   
}    
