#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "KEY.h"
#include "adc.h"
#include "malloc.h"
#include "Camera.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
//PWDN ����ģʽ�ߵ�ƽ��Ч
//HREF ��ͬ���ź�
//VSYNC ֡ͬ���ź�
//PCLK����ͬ���ź� OV2640�Դ�����ֱ������Ϊ����

//GND	SCL	SDA	D0  D2  D4  D6   PCLK PWDN
//GND PC1 PC0 PA0 PA2 PA4 PA6  PB10	PC3

//3.3 VSYNC HREF RST D1  D3  D5  D7   NC 
//3.3 PC13  PB11 PC2 PA1 PA3 PA5 PA7
#define JPEG_TEST
#define RGB_TEST

#ifdef JPEG_TEST
//JPEG�ߴ�֧���б�
const u16 jpeg_img_size_tbl[][2]=
{
	176,144,	//QCIF
	160,120,	//QQVGA
	352,288,	//CIF
	320,240,	//QVGA
	640,480,	//VGA
	800,600,	//SVGA
	1024,768,	//XGA
	1280,1024,	//SXGA
	1600,1200,	//UXGA
}; 
u8* jpeg_buf;
#define jpeg_buf_size 42*1024  			//����JPEG���ݻ���jpeg_buf�Ĵ�С(*4�ֽ�)
volatile u32 jpeg_data_len=0; 			//buf�е�JPEG��Ч���ݳ��� 
/* ����1�������� */
void JPEG_DMA_SendArray()
{
		uint16_t sendLen =jpeg_buf_size;	// ��ֹԽ��
    while (DMA_GetCurrDataCounter(DMA1_Channel4));  // ���DMA����ͨ�����Ƿ�������
    // DMA��������-Ҫ�ȹ� ���÷��ͳ��� ����DMA
    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel4, sendLen);   // ����д��Ҫ�������������
    DMA_Cmd(DMA1_Channel4, ENABLE);     // ����DMA����  
}
//JPEG����
//JPEG����,ͨ������1���͸�����.
void jpeg_test(void)
{
	u32 i; 
	u8 *p;
	u8 key;
	u8 effect=0,expose=0;
	u8 size=5;		//Ĭ����QVGA 320*240�ߴ�
	u8 msgbuf[15];	//��Ϣ������ 
         u8 j,k;
	float t=0;
    
    
    
	mem_init();	
	jpeg_buf=mymalloc(jpeg_buf_size);//32K����
	while(!jpeg_buf)	{
		printf("MALLOC DATA\n");
		delay_ms(200);
	}
	
	OV2640_JPEG_Mode();		//JPEGģʽ  
	OV2640_OutSize_Set(jpeg_img_size_tbl[size][0],jpeg_img_size_tbl[size][1]);//��������ߴ� 
		while(1)
		{
            if(key<2)
            {
                delay_ms(100);
                key++;
            }
//key=KEY_Scan(0);
    if(key==2)
    {
        for(i=0;i<1;i++)		//����10֡���ȴ�OV2640�Զ����ںã��ع��ƽ��֮��ģ�
	{
		while(OV2640_VSYNC==1);	 
		while(OV2640_VSYNC==0);	  
	}  
        
				while(OV2640_VSYNC==0);//�ȴ�֡�ź�
					 while(OV2640_VSYNC==1){
							while(OV2640_HREF)
							{ 
								while(OV2640_PCLK==0);
									jpeg_buf[jpeg_data_len++]=OV2640_DATA; 
//									if(jpeg_data_len>jpeg_buf_size){
//										JPEG_DMA_SendArray();
//										jpeg_data_len=0;	
//                                        key=0;
//									}
								while(OV2640_PCLK==1);
							}
						}
                     JPEG_DMA_SendArray();
                    jpeg_data_len=0;
                        key=0;
                        
                        
		for(j=0;j<3;j++)
		{
			for(k=0;k<6;k++)
			{
				LCD_ShowPicture(40*k,120+j*40,40,40,gImage_1);
			}
		}
                    }
//    	LCD_ShowChinese(0,0,"�о�԰",RED,WHITE,32,0);
//		LCD_ShowString(0,40,"LCD_W:",RED,WHITE,16,0);
//		LCD_ShowIntNum(48,40,LCD_W,3,RED,WHITE,16);
//		LCD_ShowString(80,40,"LCD_H:",RED,WHITE,16,0);
//		LCD_ShowIntNum(128,40,LCD_H,3,RED,WHITE,16);
//		LCD_ShowString(80,40,"LCD_H:",RED,WHITE,16,0);
//		LCD_ShowString(0,70,"Increaseing Nun:",RED,WHITE,16,0);
		LCD_ShowFloatNum1(128,70,t,4,RED,WHITE,16);
		t+=0.11;

                    
		 } 
}

#endif


#ifdef RGB_TEST


u8* ov2640_framebuf;	
void rgb565_test(void)
{
 	u8 key;
	u8 effect=0,expose=0;
	int i=0,j=0;
	u16 pixcnt=0;				//����ͳ��
	u32 pix=0;
	u16 linepix=0;
	u16 linecnt=0;				//����ͳ��	
	mem_init();	
	ov2640_framebuf=mymalloc(128*128*2);//32K����
	while(!ov2640_framebuf)	{
		printf("MALLOC DATA\n");
		delay_ms(200);
	}
	OV2640_RGB565_Mode();
	OV2640_OutSize_Set(128,128); 
	while(1)
	{
				key=KEY_Scan(0);
				if(key==KEY0_PRES){
					effect++;
					effect%=7;
					OV2640_Special_Effects(effect);
				}
				if(key==WKUP_PRES){
					expose++;
					expose%=5;					
					OV2640_Auto_Exposure(expose);
				}
		pix=0;
		while(OV2640_VSYNC)			//�ȴ�֡�ź�
		{	
		}
		pixcnt=0;								//���ؼ���������
		linecnt=0;					//��ͳ������
		while(linecnt<128)	
		{
			while(OV2640_HREF)
			{                                                                                                                         
				while(OV2640_PCLK==0);
				ov2640_framebuf[256*linecnt+linepix]=OV2640_DATA; 
				pix++;
				linepix++;
				while(OV2640_PCLK==1); 
				while(OV2640_PCLK==0); 
				ov2640_framebuf[256*linecnt+linepix]=OV2640_DATA; 
				pix++;
				linepix++;
				while(OV2640_PCLK==1);
			}  
			if(pix!=pixcnt)
			{
				pixcnt=pix;
				linepix=0;
				linecnt++;
			}
		}	
			for(i=0;i<128;i++)
			for(j=0;j<128;j++)
			{
						LCD_DrawPoint(j,i,(u16)(ov2640_framebuf[2*128*i+1+2*j]<<8|ov2640_framebuf[2*128*i+2*j]));		
			}
			
	}
}
#endif


 int main(void)
 {
     u8 key_value=0;
     
	delay_init();	    	 //��ʱ������ʼ��	  
	uart1_init(921600); 
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	KEY_Init();
	while(OV2640_Init())			//��ʼ��OV2640
	{
		//printf("Camera ERROR\n");
		delay_ms(200);
	}


	ov2640_speed_ctrl();
#ifdef RGB_TEST
	rgb565_test();
#else
  
        //jpeg_test();
    
#endif
}
