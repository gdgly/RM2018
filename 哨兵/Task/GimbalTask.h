#ifndef __GIMBALTASK_H__
#define __GIMBALTASK_H__

#include <stm32f4xx.h>

#define move_up 0
#define stop 1
#define abs(x) ((x)>0? (x):(-(x)))

#define yawcontrolconfig \
{\
	.Limit = 0,\
	.Encoder_Init = 6000,\
	.Encoder = 0,\
	.Position_kp = 8.3f,\
	.Velocity_kp = 40,\
	.Gyro = 0,\
	.Angle = 0,\
	.ControlData = 0,\
	.output = 0,\
	.time = 0,\
	.Calc = &YawControlCalc,\
}\

#define pitchcontrolconfig \
{\
	.Limit = 0,\
	.Encoder_Init = 2041,\
	.Encoder = 0,\
	.Position_kp = 14,\
	.Velocity_kp = 15,\
	.Gyro = 0,\
	.Angle = 0,\
	.ControlData = 0,\
	.output = 0,\
	.time = 0,\
	.Calc = &PitchControlCalc,\
}\

typedef struct _GIMBALCONTORL
{
	int16_t Limit;
	int16_t Encoder_Init;
	int16_t Encoder;
	float Position_kp;
	float Velocity_kp;
	float Gyro;
	double Angle;
	double ControlData;
	int16_t output;
	int time;
	void (*Calc)(struct _GIMBALCONTORL *YawControl);
}GIMBALCONTORL; 

void YawControlCalc(GIMBALCONTORL *YawControl);
void PitchControlCalc(GIMBALCONTORL *PitchControl);
int16_t FireControlLoop(int16_t SetSpeed);
void FiresSpeedControlLoop(int16_t SetSpeed);


void    Set_Fire_Fre(int16_t fre);
void    Set_Fire_Speed(int16_t speed);
void SetFireSpeddAndFre(int16_t speed,int16_t fre);
void Heat2SetFire(void);


extern u8 GimbalInit;
extern int  catch_angle;
extern GIMBALCONTORL YawControl;
extern GIMBALCONTORL PitchControl;
#endif
