#ifndef _PID_H
#define _PID_H
int Incremental_PI1 (int Encoder,int Target,int check);
int Incremental_PI2 (int Encoder,int Target,int check);
int Distance_PI1(int Error, int check);
int Distance_PI2(int Error, int check);
int pwm_limit(int Encoder);
int abs(int val);
float moveForward(float distance);
#endif