/*********************************Copyright (c)*********************************                                      
  *                                                    
  ******************************************************************************
  * �ļ����ƣ�SYSTICK.C
  * ��    ����ϵͳ�δ�ʱ��--ʵ��ϵͳ��ȷ��ʱ
  * �� �� ��:  
  * ��������:   
  * �� �� ��:             
  * �޸�����:   
  * ��    ��: 
  ******************************************************************************
  * attention
  *
  ******************************************************************************
  */
/*Includes --------------------------------------------------------------------*/
#include "includes.h"
#include "SYSTICK.H"
/* ���Ͷ��� typedef-----------------------------------------------------------*/
/* Ԥ�����ַ�     ------------------------------------------------------------*/
/* �궨��        -------------------------------------------------------------*/
/* ��������          ---------------------------------------------------------*/

/*******************************************************************************
* ��������: Systick_Init();
* ��������: �δ�ʱ����ʼ��
* �������: void
* ���ز���: ��
********************************************************************************/
void Systick_Init(void)
{    
	  
    if (SysTick_Config(SystemCoreClock / 1000))  //��ʱ1����
    { 
     /* Capture error */ 
      while (1);
    }
		
   
}








