//*************************************************
//第一部分 申明引用函数文件
#include "mbed.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Picture.h"


unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
int SecondLeft;
int Total=24*3600*3600;

void Redraw_Mainmenu(void){

    Lcd_Clear(GRAY0);

    DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
    Gui_DrawFont_GBK16(16,40,BLUE,GRAY0,"Nucleo TFT");

    DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
    Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"EE-design");

    DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
    Gui_DrawFont_GBK16(16,100,BLUE,GRAY0,"mHealth LAB");


    Gui_DrawFont_GBK16(16,140,RED,GRAY0, "Count down:");
    
    Gui_DrawFont_Num32(100,125,RED,GRAY0,Num[5]);
    wait_ms(1000);
    Gui_DrawFont_Num32(100,125,RED,GRAY0,Num[4]);
    wait_ms(1000);
    Gui_DrawFont_Num32(100,125,RED,GRAY0,Num[3]);
    wait_ms(1000);
    Gui_DrawFont_Num32(100,125,RED,GRAY0,Num[2]);
    wait_ms(1000);
    Gui_DrawFont_Num32(100,125,RED,GRAY0,Num[1]);
    wait_ms(1000);
    Gui_DrawFont_Num32(100,125,RED,GRAY0,Num[0]);   
}


void Num_Test(void)
{
    u8 i=0;
    Lcd_Clear(GRAY0);
    Gui_DrawFont_GBK16(16,65,RED,GRAY0,"Num Test");
    wait_ms(1000);
    Lcd_Clear(GRAY0);

    for(i=0;i<10;i++)
    {
    Gui_DrawFont_Num32((i%3)*40,32*(i/3)+30,RED,GRAY0,Num[i+1]);
    wait_ms(100);
    }
    
}

void Font_Test(void){
    Lcd_Clear(BLACK);
    Gui_Circle(64,80,60,RED);
    wait_ms(200);
    showhanzi(48,40,YELLOW,BLACK,0); //显示hanzi数组中的第0个数字
    wait_ms(200);
    showhanzi(48,80,YELLOW,BLACK,1); //显示hanzi数组中的第1个数字
    wait_ms(200);
    Gui_Circle(64,80,45,RED);
    wait_ms(200);
    Gui_Circle(64,80,30,RED);
    wait_ms(200);
    Gui_Circle(64,80,10,RED);
    wait_ms(1500);  
}


void Pic_Test(){
    Lcd_Clear(WHITE);
    Gui_DrawFont_GBK16(20,65,BLACK,WHITE,"Picture Test");
    wait_ms(500);
    show_pic(gImage_PKU,0,12,128,145); //参数 图片变量,起始x坐标,终止x坐标,终止y坐标
    wait_ms(2000);
}

void Color_Test(void){
    u8 i=1;
    Lcd_Clear(BLACK);
    
    Gui_DrawFont_GBK16(20,65,WHITE,BLACK,"Color Test");
    wait_ms(500);

    while(i--)  {
        Lcd_Clear(WHITE);
        Lcd_Clear(BLACK);
        Lcd_Clear(RED);
        Lcd_Clear(GREEN);
        Lcd_Clear(BLUE);
    }       
}



void ShowTime(u8 hour,u8 min,u8 sec){
		Gui_DrawFont_GBK24(20,20,BLUE,BLACK,"Current Time:");
    u8 n6,n5,n4,n3,n2,n1;
		n6 = hour/10;
		n5 = hour%10;
    n4 = min/10;
    n3 = min%10;
    n2 = sec/10;
    n1 = sec%10;
		Gui_DrawFont_Num32(8,65,WHITE,BLACK,Num[n6]);
    Gui_DrawFont_Num32(32,65,WHITE,BLACK,Num[n5]);
    Gui_DrawFont_Num32(69,65,WHITE,BLACK,Num[n4]);
    Gui_DrawFont_Num32(93,65,WHITE,BLACK,Num[n3]);
		Gui_DrawFont_GBK24(60,70,WHITE,BLACK,":");
    //Gui_DrawFont_Num32(69,65,BLUE,BLACK,Num[n2]);
    //Gui_DrawFont_Num32(93,65,BLUE,BLACK,Num[n1]);
}

void CountDown(){
		int H,M,S;
		H=SecondLeft/3600;
    M = (SecondLeft-H*3600)/60;
    S = SecondLeft%60;
		printf("%d:%d\r\n",M,S);
    ShowTime(H,M,S);
    if(SecondLeft<Total){SecondLeft++;}
		else{SecondLeft=0;}
}

int Convert_time(u8 hour,u8 min,u8 sec){
	return hour*60*60+min*60+sec;
}

void ShowWellcome(){
    Lcd_Clear(WHITE);
    show_pic(gImage_PKU,0,0,128,113);
		Gui_DrawFont_GBK16(10,120,BLACK,WHITE,"Blood-Pressure");
    wait_ms(2000);
}

int main(){
    Lcd_Init(0); //驱动IC:ST7735R
    Lcd_On();
		ShowWellcome();
		Lcd_Clear(BLACK);
		SecondLeft=Convert_time(13,23,31);
    while(1){
			CountDown();
			wait_ms(1000);
		}
        //printf("the x is: m/s2\r\n");
        //Redraw_Mainmenu();      
        //Font_Test();  //汉字测试
        //Pic_Test();   //图片测试
        //wait_ms(500);
        //Color_Test(); //简单纯色填充测试
        
        //显示字符串:参数:起始x坐标,起始y坐标,字体颜色,背景色,字符串
        //Gui_DrawFont_GBK16(10,70,WHITE,BLUE,"Hello ARM 2016"); 
        
}

