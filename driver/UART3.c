  #include "includes.h"
  #include "UART3.H" 
  #include <stdarg.h>
	
	
uint8_t Uart3_Rx[Uart3_Rx_LEN];	
  void Uart3_Init(void)
{
   
        GPIO_InitTypeDef  GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
        DMA_InitTypeDef  DMA_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);              
        RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC   , ENABLE);   // 使能GPIOB端口
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3   , ENABLE); // 使能串口2时钟
	    
        GPIO_PinAFConfig(GPIOC ,GPIO_PinSource4, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOC ,GPIO_PinSource5, GPIO_AF_1);                           
/////////////////////////////////////////////////////////////////////////////////////        
        /* PC4==TX PC5-RX  */  
                                      
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;                 
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        GPIO_Init(GPIOC, &GPIO_InitStructure); 

        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
	      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
        GPIO_Init(GPIOC , &GPIO_InitStructure); 
///////////////////////////////////////////////////////////////////////////////////// 
           
        USART_InitStructure.USART_BaudRate = 115200;                 		      
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;     	       
        USART_InitStructure.USART_StopBits = USART_StopBits_1;                         
        USART_InitStructure.USART_Parity = USART_Parity_No;                            
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               
        USART_Init(USART3, &USART_InitStructure); 	//串口配置
        
        USART_Cmd(USART3, ENABLE);//使能串口3
				USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);

        DMA_DeInit(DMA1_Channel6);
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART3->RDR);
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart3_Rx;
				DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
				DMA_InitStructure.DMA_BufferSize = Uart3_Rx_LEN;
				DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
				DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
				DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
				DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
				DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
				DMA_InitStructure.DMA_Priority = DMA_Priority_High;
				DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
				DMA_Init(DMA1_Channel6, &DMA_InitStructure);
  
        DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);
  
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_5_6_7_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority =3;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        DMA_Cmd(DMA1_Channel6, ENABLE);
          
          
	
}

