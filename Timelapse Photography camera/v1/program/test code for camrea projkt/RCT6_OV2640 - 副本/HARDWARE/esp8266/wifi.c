#include "sys.h"
#include "delay.h"
#include "wifi.h"
#include "usart.h"
#include "stdio.h"      //包含需要的头文件
#include "stdarg.h"		//包含需要的头文件 
#include "string.h"     //包含需要的头文件

#include "lcd.h"




void wifi_init(void)
{
    u8 i=0;
    
//            at_cmd_8266("AT+CIFSR\r\n");      
//            while(U2_RECEIVE_STA==0){}
//                           
//            if(strstr(USART2_RX_BUF,"192.168.1.5")!=0) 
//                {
//                    USART2SendStr("connected");
//                    memset(USART2_RX_BUF,0x00,USART2_RX_STA);
//                    USART2_RX_STA=0; 
//                    U2_RECEIVE_STA=0;
//                    return;
//                }
            
    
    at_cmd_8266("AT\r\n"); 
    while(U2_RECEIVE_STA==0){}                    
    while(strstr(USART2_RX_BUF,"OK")==0) {}
    debugmsg(USART2_RX_BUF);
    memset(USART2_RX_BUF,0x00,USART2_RX_STA);   
	USART2_RX_STA=0;       
    U2_RECEIVE_STA=0;
            
    at_cmd_8266("AT+CWMODE=1\r\n"); 
             while(U2_RECEIVE_STA==0){}
          while(strstr(USART2_RX_BUF,"OK")==0) {}
debugmsg(USART2_RX_BUF);
            memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
             
        
            U2_RECEIVE_STA=0;   
                
                
             at_cmd_8266("AT+CWAUTOCONN=1\r\n"); 
     
            while(U2_RECEIVE_STA==0){}
                           
            while(strstr(USART2_RX_BUF,"OK")==0) {}
         
             memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
             
        
            U2_RECEIVE_STA=0; 
                
                
            
        at_cmd_8266("AT+CWJAP=\"Redmi_E6F0\",\"password\"\r\n"); 
            while(U2_RECEIVE_STA==0){}
                          
            while(strstr(USART2_RX_BUF,"OK")==0) {}
            debugmsg(USART2_RX_BUF);
            memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
               
        
            U2_RECEIVE_STA=0; 
               at_cmd_8266("AT+CIFSR\r\n");      
            while(U2_RECEIVE_STA==0){}
                           
            while(strstr(USART2_RX_BUF,"OK")==0) {}
                debugmsg(USART2_RX_BUF);
            memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
                
        
            U2_RECEIVE_STA=0;
        
                   at_cmd_8266("AT+CIPSTART=\"TCP\",\"192.168.1.13\",8000\r\n");      
            while(U2_RECEIVE_STA==0){}
                           
            while(strstr(USART2_RX_BUF,"OK")==0) {}
             debugmsg(USART2_RX_BUF);
            memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
               
        
            U2_RECEIVE_STA=0; 
        
        
            at_cmd_8266("AT+CIPMODE=1\r\n");      
            while(U2_RECEIVE_STA==0){}
                           
            while(strstr(USART2_RX_BUF,"OK")==0) {}
            debugmsg(USART2_RX_BUF);
            memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
                
        
            
        U2_RECEIVE_STA=0;
            at_cmd_8266("AT+CIPSEND\r\n");      
            while(U2_RECEIVE_STA==0){}
                           
            while(strstr(USART2_RX_BUF,"OK")==0) {}
            debugmsg(USART2_RX_BUF);
            memset(USART2_RX_BUF,0x00,USART2_RX_STA);
            
			USART2_RX_STA=0; 
            U2_RECEIVE_STA=0;    
        
           
        
}

