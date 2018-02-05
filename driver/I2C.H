/*********************************Copyright (c)*********************************                                      
  *                                          
  ******************************************************************************
  * �ļ����ƣ�I2C.H
  * ��    ����I2Cģ��ͷ�ļ�
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

#ifndef  __I2C_H__
#define  __I2C_H__

/**********************ͷ�ļ����ü�������������*********************************/
/*  ������Ҫ��ͷ�ļ�  */

/*  �궨��  */

// ��I2C�������߽��в�����
//===========================================================
// PB6--SCL
// PB7--SDA

#define I2C_PRORT         GPIOB
#define I2C_PORT_CLK      RCC_AHBPeriph_GPIOB

#define I2C_SDA_PIN       GPIO_Pin_7
#define I2C_SCL_PIN       GPIO_Pin_6


#define	I2C_SDA_H         GPIO_SetBits(I2C_PRORT, I2C_SDA_PIN)
#define	I2C_SDA_L         GPIO_ResetBits(I2C_PRORT, I2C_SDA_PIN)
#define I2C_SDA_VAL       GPIO_ReadInputDataBit(I2C_PRORT,I2C_SDA_PIN)
#define	I2C_SCL_H         GPIO_SetBits(I2C_PRORT, I2C_SCL_PIN )
#define	I2C_SCL_L         GPIO_ResetBits(I2C_PRORT, I2C_SCL_PIN)



/*  �Ӻ�������        */
extern  void I2C_GPIO_Init(void);
extern  void I2C_SDA_OUT(void);
extern  void I2C_SDA_IN(void);
extern  void I2C_Start(void);
extern  void I2C_Stop(void);
extern  unsigned char I2C_Wait_Ack(void);
extern  void I2C_Ack(void);
extern  void I2C_NAck(void);
extern  void I2C_Write_1(void);
extern  void I2C_Write_0(void);
extern  void I2C_Send_Byte(unsigned char ucData);
extern  unsigned char I2C_Send_NByte(unsigned char * pbuffer, unsigned char n);
extern  unsigned char I2C_Read_Byte(void);
extern  void I2C_Read_NByte(unsigned char * pbuffer, unsigned char n);


#endif  
