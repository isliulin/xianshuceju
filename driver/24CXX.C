/*********************************Copyright (c)*********************************                                      
  *                                                
  ******************************************************************************
  * �ļ����ƣ�24CXX.C
  * ��    ����EEPROM��дģ��
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
#include  "24CXX.H" 
#include  "includes.h"
#include  "I2C.H" 
/* ���Ͷ��� typedef-----------------------------------------------------------*/
/* Ԥ�����ַ�     ------------------------------------------------------------*/
/* �궨��        -------------------------------------------------------------*/
/* ��������          ---------------------------------------------------------*/ 
extern void Delay_Ms(__IO uint32_t nCount);
extern void Delay_Us(__IO uint32_t nCount);

#define Device_Address  0xA0  //24CXX���豸��ַ
/*******************************************************************************
* ��������: 24CXX_Read_Byte()
* ��������: ��24CXX��ָ����ַ��ȡ1���ֽڵ�����
* �������: dataaddress--���ݶ�ȡ�ĵ�ַ
* ���ز���: ��ȡ������
********************************************************************************/
unsigned char EEPROM_Read_Byte(unsigned char dataaddress)
{
        unsigned char temp;
    
	      I2C_Start();                         // ��ʼ����
	      I2C_Send_Byte(Device_Address);       // ������������豸��ַ
	      if(I2C_Wait_Ack()==0)                // ����д�����Ӧ��
            I2C_Send_Byte(dataaddress);      // �������ݵ�ַ
	      else 
             return 0;
	      if(I2C_Wait_Ack()==0) 
	      {
	          I2C_Start();                       // ��ʼ����
	          I2C_Send_Byte((Device_Address|0x01));
	      }
	      else    
             return 0;
	      if(I2C_Wait_Ack()==0)	
             temp = I2C_Read_Byte();
	      else 
             return 0;

	       I2C_NAck();
	       I2C_Stop();
	       return temp;
     	
}
/*******************************************************************************
* ��������: 24CXX_Read_NByte()
* ��������: ��24CXX��ָ����ַ��ȡN���ֽڵ�����
* �������: pbuffer--ָ�򱣴����ݵ�ַ��ָ��
            n--��ȡ���ݵĸ���
            dataaddress--���ݶ�ȡ���׵�ַ
* ���ز���: ��ȡ�����0--�ɹ���1--ʧ��
********************************************************************************/
unsigned char  EEPROM_Read_NByte( unsigned char *pbuffer, unsigned char n, unsigned char dataaddress )
{
        I2C_Start();                         // ��ʼ����
	      I2C_Send_Byte(Device_Address);       // ������������豸��ַ
	      if(I2C_Wait_Ack()==0)                // ����д�����Ӧ��
            I2C_Send_Byte(dataaddress);      // �������ݵ�ַ
	      else 
               return 1;
	      if(I2C_Wait_Ack()==0) 
	      {
	        I2C_Start();                       // ��ʼ����
	        I2C_Send_Byte((Device_Address|0x01));
	      }
      	else      
					    return 1;
	      if(I2C_Wait_Ack()==0)	
               I2C_Read_NByte(pbuffer, n);
	       else 
               return 1;
	
	      return  0;	
}
/*******************************************************************************
* ��������:  24CXX_Write_Byte();
* ��������:  ��24CXX��ָ����ַ��д��1���ֽڵ�����  
* �������:  wdata--д�������
             dataaddress--���ݶ�ȡ���׵�ַ
* ���ز���:  д������0--�ɹ���1--ʧ��
********************************************************************************/
unsigned char  EEPROM_Write_Byte( unsigned char dataaddress, unsigned char wdata )
{
        I2C_Start();                         // ��ʼ����
        I2C_Send_Byte(Device_Address);       // ������������豸��ַ
	      if(I2C_Wait_Ack()==0)                // ����д�����Ӧ��
            I2C_Send_Byte(dataaddress);      // �������ݵ�ַ
	      else 
            return 1;
        if(I2C_Wait_Ack()==0)                // ���������Ӧ��
            I2C_Send_Byte(wdata);            // ����Ҫд�������
        else 
               return 1 ;
        if(I2C_Wait_Ack()==0)                // ���������Ӧ��
               I2C_Stop();                   // ���������Ӧ�� ������ֹͣ����
        else           
               return 1;
    
        Delay_Ms(5);                 //�ȴ�EEPROM����ڲ�д��(��Ҫ)
	      return 0 ; 
}
/*******************************************************************************
* ��������:  24CXX_Write_NByte();
* ��������:  ��24CXX��ָ����ַ��д��1���ֽڵ�����  
* �������:  dataaddress--���ݶ�ȡ�ĵ�ַ
* ���ز���:  д������0--�ɹ���1--ʧ��
********************************************************************************/
unsigned char  EEPROM_Write_NByte( unsigned char *pbuffer, unsigned char n, unsigned char dataaddress )
{
         unsigned char  temp; 
    
	       I2C_Start();                         // ��ʼ����
         I2C_Send_Byte(Device_Address);       // ������������豸��ַ
	       if(I2C_Wait_Ack()==0)                // ����д�����Ӧ��
            I2C_Send_Byte(dataaddress);      // �������ݵ�ַ
	       else 
               return 1;
         if(I2C_Wait_Ack()==0)                // ���������Ӧ��
             temp = I2C_Send_NByte(pbuffer, n);
	       else 
               return 1;
         Delay_Ms(5);                 //�ȴ�EEPROM����ڲ�д��(��Ҫ)
	       if(temp==0)    return 0;
	       else           return 1;

}