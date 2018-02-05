





#include "ANO-Tech.h"

//��������վ��������
u8 data_to_send[50];
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

/**
  **********************************
  * @brief  ����1����1���ֽ�
  * @param  c����������
  * @retval None
  **********************************
*/
void usart1_send_char(u8 c)
{
	while (USART_GetFlagStatus(USART4, USART_FLAG_TC) == RESET); //ѭ������,ֱ���������   
	USART_SendData(USART4, c);
}

/**
  **********************************
  * @brief  �������ݸ�����������λ������(V2.6�汾)
  * @param  fun:������. 0XA0~0XAF  
						data:���ݻ�����,���28�ֽ�!!
						len:data����Ч���ݸ���
  * @retval None
  **********************************
*/
void usart1_niming_report(u8 fun, u8*data, u8 len)
{
	u8 send_buf[32];
	u8 i;
	if (len>28)return;	//���28�ֽ����� 
	send_buf[len + 3] = 0;	//У��������
	send_buf[0] = 0X88;	//֡ͷ
	send_buf[1] = fun;	//������
	send_buf[2] = len;	//���ݳ���
	for (i = 0;i<len;i++)send_buf[3 + i] = data[i];			//��������
	for (i = 0;i<len + 3;i++)send_buf[len + 3] += send_buf[i];	//����У���	
	for (i = 0;i<len + 4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}

/**
  **********************************
  * @brief  ���ͼ��ٶȴ��������ݺ�����������
  * @param  aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ  
						gyrox,gyroy,gyroz:x,y,z�������������������ֵ
  * @retval None
  **********************************
*/
void mpu6050_send_data(short aacx, short aacy, short aacz, short gyrox, short gyroy, short gyroz)
{
	u8 tbuf[12];
	tbuf[0] = (aacx >> 8) & 0XFF;
	tbuf[1] = aacx & 0XFF;
	tbuf[2] = (aacy >> 8) & 0XFF;
	tbuf[3] = aacy & 0XFF;
	tbuf[4] = (aacz >> 8) & 0XFF;
	tbuf[5] = aacz & 0XFF;
	tbuf[6] = (gyrox >> 8) & 0XFF;
	tbuf[7] = gyrox & 0XFF;
	tbuf[8] = (gyroy >> 8) & 0XFF;
	tbuf[9] = gyroy & 0XFF;
	tbuf[10] = (gyroz >> 8) & 0XFF;
	tbuf[11] = gyroz & 0XFF;
	usart1_niming_report(0XA1, tbuf, 12);//�Զ���֡,0XA1
}

/**
  **********************************
  * @brief  ͨ������1�ϱ���������̬���ݸ�����
  * @param  aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
						gyrox,gyroy,gyroz:x,y,z�������������������ֵ
						roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
						pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
						yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
  * @retval None
  **********************************
*/
void usart1_report_imu(short aacx, short aacy, short aacz, short gyrox, short gyroy, short gyroz, short roll, short pitch, short yaw)
{
	u8 tbuf[28];
	u8 i;
	for (i = 0;i<28;i++)tbuf[i] = 0;//��0
	tbuf[0] = (aacx >> 8) & 0XFF;
	tbuf[1] = aacx & 0XFF;
	tbuf[2] = (aacy >> 8) & 0XFF;
	tbuf[3] = aacy & 0XFF;
	tbuf[4] = (aacz >> 8) & 0XFF;
	tbuf[5] = aacz & 0XFF;
	tbuf[6] = (gyrox >> 8) & 0XFF;
	tbuf[7] = gyrox & 0XFF;
	tbuf[8] = (gyroy >> 8) & 0XFF;
	tbuf[9] = gyroy & 0XFF;
	tbuf[10] = (gyroz >> 8) & 0XFF;
	tbuf[11] = gyroz & 0XFF;
	tbuf[18] = (roll >> 8) & 0XFF;
	tbuf[19] = roll & 0XFF;
	tbuf[20] = (pitch >> 8) & 0XFF;
	tbuf[21] = pitch & 0XFF;
	tbuf[22] = (yaw >> 8) & 0XFF;
	tbuf[23] = yaw & 0XFF;
	usart1_niming_report(0XAF, tbuf, 28);//�ɿ���ʾ֡,0XAF
}

/**
  **********************************
  * @brief  �������ݸ���������վ����(V4.0�汾)
  * @param  data:���ݻ�����,���28�ֽ�!!
						len:data����Ч���ݸ���
  * @retval None
  **********************************
*/
void ANO_DT_Send_Data(u8 *data, u8 len)
{
	u8 i;
	if (len>28)return;	//���28�ֽ����� 
	for (i = 0;i<len;i++)usart1_send_char(data[i]);	//�������ݵ�����1
}

/**
  **********************************
  * @brief  ���ͼ��ٶȴ��������ݺ�����������
  * @param  aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ  
						gyrox,gyroy,gyroz:x,y,z�������������������ֵ
  * @retval None
  **********************************
*/
//void ANO_DT_Data_Exchange(void)
//{
//	static u8 cnt = 0;
//	static u8 senser_cnt 	= 10;
//	static u8 status_cnt 	= 15;
//	if((cnt % senser_cnt) == (senser_cnt-1))
//		f.send_senser = 1;	
//	
//	if((cnt % status_cnt) == (status_cnt-1))
//		f.send_status = 1;	
//	
//	if((cnt % rcdata_cnt) == (rcdata_cnt-1))
//		f.send_rcdata = 1;	
//	
//	if((cnt % motopwm_cnt) == (motopwm_cnt-1))
//		f.send_motopwm = 1;	
//	
//	if((cnt % power_cnt) == (power_cnt-1))
//		f.send_power = 1;		
//	
//	cnt++;
///////////////////////////////////////////////////////////////////////////////////////
//	if(f.send_version)
//	{
//		f.send_version = 0;
//		ANO_DT_Send_Version(4,300,100,400,0);
//	}
///////////////////////////////////////////////////////////////////////////////////////
//	else if(f.send_status)
//	{
//		f.send_status = 0;
//		ANO_DT_Send_Status(0,0,0,0,0,0);
//	}	
///////////////////////////////////////////////////////////////////////////////////////
//	else if(f.send_senser)
//	{
//		f.send_senser = 0;
//		ANO_DT_Send_Senser(0,0,0,
//												0,0,0,
//												0,0,0,0);
//	}	
///////////////////////////////////////////////////////////////////////////////////////

//	}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////
//}
void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z)
{
	u8 _cnt=0;
	vs16 _temp;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	
	_temp = a_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = g_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	ANO_DT_Send_Data(data_to_send, _cnt);
}
/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl������Э�����ݽ������������������Ƿ���Э���ʽ��һ������֡���ú��������ȶ�Э�����ݽ���У��
//У��ͨ��������ݽ��н�����ʵ����Ӧ����
//�˺������Բ����û����е��ã��ɺ���Data_Receive_Prepare�Զ�����


void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed)
{
	u8 _cnt=0;
	vs16 _temp;
	vs32 _temp2 = alt;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(angle_rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[_cnt++] = fly_model;
	
	data_to_send[_cnt++] = armed;
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	ANO_DT_Send_Data(data_to_send, _cnt);
}