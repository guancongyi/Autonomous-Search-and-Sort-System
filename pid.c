#include "pid.h"
#include "system_definitions.h"
int Incremental_PI1(int Encoder,int Target,int check) {
    float Kp=8.2,Ki=2.9,Kd=0;  
    static float Bias,Pwm,Last_bias,Last_Last_bias;
    if (check == 0 || (Target-Encoder) < -10) {
        Pwm = 0;
        Bias = 0; 
        Last_bias = 0;
        Last_Last_bias = 0;
        DRV_OC_PulseWidthSet(DRV_OC_INDEX_0, abs(pwm_limit(Pwm)));
        return 0;
    }
    Bias=Target-Encoder - 0.11;
    if (abs(Bias) > 0) {
        Pwm = Pwm + Kp*Bias + Ki*(Bias-Last_bias)+Kd*(Bias-2*Last_bias+ Last_Last_bias);
        DRV_OC_PulseWidthSet(DRV_OC_INDEX_0, abs(pwm_limit(Pwm)));
    }
    Last_Last_bias=Last_bias;
    Last_bias=Bias;
    return Pwm;
}
int Incremental_PI2(int Encoder,int Target,int check) {
    float Kp=8.2,Ki=2.9,Kd=0;  
    static float Bias,Pwm,Last_bias,Last_Last_bias;
    if (check == 0 || (Target-Encoder) < -10) {
        Bias = 0; 
        Last_bias = 0;
        Last_Last_bias = 0;
        Pwm = 0;
        DRV_OC_PulseWidthSet(DRV_OC_INDEX_1, abs(pwm_limit(Pwm)));
        return 0;
    }
    Bias=Target-Encoder;
    if (abs(Bias) > 0) {
        Pwm = Pwm + Kp*Bias + Ki*(Bias-Last_bias)+Kd*(Bias-2*Last_bias+ Last_Last_bias);
        DRV_OC_PulseWidthSet(DRV_OC_INDEX_1, abs(pwm_limit(Pwm)));
    }
    Last_Last_bias=Last_bias;
    Last_bias=Bias;
    return Pwm;
}
int Distance_PI1(int Error, int check) {
    float Kp=0.0116,Ki=0.000001;  
   // float Kp=6,Ki=10,Kd=0;   
    static int integral;
    if (check == 0) {
        integral = 0;
        return 0;
    }
    int speed;
    speed = Kp * Error + Ki * integral;
    integral = integral + Error * 0.1;
    return speed;
}
int Distance_PI2(int Error, int check) {
    float Kp=0.0116,Ki=0.0001;  
   // float Kp=6,Ki=10,Kd=0;   
    static int integral;
    if (check == 0) {
        integral = 0;
        return 0;
    }
    int speed;
    speed = Kp * Error + Ki * integral;
    integral = integral + Error * 0.1;
    return speed;
}
int pwm_limit(int Encoder){
    int amplitude = 20000;
    if (Encoder < -amplitude) {
        return -amplitude;
    }
    else if (Encoder > amplitude) {
        return amplitude;
    }
    else {
        return Encoder;
    }
}
int abs(int val)
{          
    int temp;
    if(val<0) {
        temp = -val;
    }
    else {
        temp = val;
    }
    return temp;
}
float moveForward(float distance) {
    static float travel;
    if (travel <= 0) {
        travel = distance;
    }
    travel = travel - 0.78;
    return travel;
}