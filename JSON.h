#ifndef _JSON_H 
#define _JSON_H 
#include "cJSON.h"
#include "md5.h"
#include <stdio.h>
#include <math.h>
typedef enum {Motor,Arm,Sensor,Pixel} mode_;
typedef struct UNION {
            mode_ Mode; 
            uint8_t operation;
            uint8_t Motor_Direction; 
            uint8_t Left_Motor_Speed; 
            uint8_t Right_Motor_Speed; 
            int Left_Motor_Distance; 
            int Right_Motor_Distance;
            uint8_t arm_status;
            uint8_t arm_item_count;
            uint8_t Pixel_color;
            uint16_t Pixel_x;
            uint16_t Pixel_y;
            int IsCenter;
            int Sensor_distance;
            int Find_result;
}UNION_;
CJSON_PUBLIC(cJSON *) CreateJSON_Object();
void addStringToJSON(cJSON * const object, const char * const name, const char * const string);
void addNumberToJSON(cJSON * const object, const char * const name, const double number);
CJSON_PUBLIC(char *) JSONtoString(const cJSON *item);
void MD5(const char *data, unsigned char *result);
CJSON_PUBLIC(cJSON *) parsing(const char *value);
CJSON_PUBLIC(char *) getStringTypeObject(cJSON * const object, const char *name);
double getDoubleTypeObject(cJSON * const object, const char *name);
void deleteJSON(cJSON *item);
void sendRequest(cJSON *item, cJSON *json2);
void sendRequest2(cJSON *item);
//void sendRequest3(mode_ Mode,uint8_t operation, uint8_t val1, uint8_t val2, uint8_t val3, int val4, int val5);
void sendRequest3(mode_ Mode,uint8_t operation, uint8_t val1, uint8_t val2, uint8_t val3, int val4, int val5, int val6, uint16_t Pixel_x, uint16_t Pixel_y, int IsCenter);
#endif 