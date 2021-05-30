/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "math.h"
#include <stdbool.h>

#define PI 3.14159265
float board_coords[8][8][2] = {
    {{  0,   0}, {96, 324}, { 0,   0}, {19, 324}, {  0,   0}, {-57, 324}, {  0,   0}, {-135, 285}},
    {{135, 285}, { 0,   0}, {57, 285}, { 0,   0}, {-19, 285}, {  0,   0}, {-96, 285}, {   0,   0}},
    {{  0,   0}, {96, 246}, { 0,   0}, {19, 246}, {  0,   0}, {-57, 246}, {  0,   0}, {-135, 246}},
    {{135, 208}, { 0,   0}, {57, 208}, { 0,   0}, {-19, 208}, {  0,   0}, {-96, 208}, {   0,   0}},
    {{  0,   0}, {96, 170}, { 0,   0}, {19, 170}, {  0,   0}, {-57, 170}, {  0,   0}, {-135, 170}},
    {{135, 132}, { 0,   0}, {57, 132}, { 0,   0}, {-19, 132}, {  0,   0}, {-96, 132}, {   0,   0}},
    {{  0,   0}, {96,  95}, { 0,   0}, {19,  95}, {  0,   0}, {-57,  95}, {  0,   0}, {-135,  95}},
    {{135,  57}, { 0,   0}, {57,  57}, { 0,   0}, {-19,  57}, {  0,   0}, {-96,  57}, {   0,   0}}
};

float dead_coords[6][4][2] = {
    {{243, 285}, {207, 285}, {-207, 285}, {-243, 285}},
    {{243, 246}, {207, 246}, {-207, 246}, {-243, 246}},
    {{243, 208}, {207, 208}, {-207, 208}, {-243, 208}},
    {{243, 170}, {207, 170}, {-207, 170}, {-243, 170}},
    {{243, 132}, {207, 132}, {-207, 132}, {-243, 132}},
    {{243,  95}, {207,  95}, {-207,  95}, {-243,  95}}
};

void initalize();
float angle_1_to_compare(float angle);
float angle_2_to_compare(float angle);
float angle_3_to_compare(float angle);
float angle_4_to_compare(float angle);
float rad2deg(float rad);
void jump_to(float servo1, float servo2, float servo3, float servo4);
void move_to(float servo[]);
float *get_coords(int row, int col, bool king, bool zone);
float * inverse_Kinematics(float *coord);



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    initalize();
    
    float *angles;
    float *coords;
    
    float home[] = {90, 29, 120, 108.2};
    jump_to(90, 90, 180, 90);
//    coords = get_coords(1,2,1,1);
//    coords = inverse_Kinematics(coords);
//        UART_1_PutString("Moving to 1,2\n");
//    move_to(coords);
//
//    //angles = inverse_Kinematics(coords);
//    
//    coords = get_coords(7,8,1,1);
//    coords = inverse_Kinematics(coords);
//    char tmpstr[15];
//    sprintf(tmpstr, "%f, %f, %f, %f\n", coords[0], coords[1], coords[2], coords[3]); 
//    UART_1_PutString(tmpstr);
//    UART_1_PutString("Moving to 7,8\n");
//    move_to(coords);
//
//    
//    CyDelay(1000);
//    coords[0] = 90;
//    coords[1] = 90;
//    coords[2] = 90;
//    coords[3] = 0;
//    move_to(coords);
//    
//    CyDelay(1000);
//    
//    move_to(home);
    
    CyDelay(1000);
    
    for(;;)
    {
        /* Place your application code here. */
        
    }
}

void initalize() {
    UART_1_Start();
    
    SPI_Start();
    jump_to(90, 29, 120, 108.2);
    PWM_1_Enable();
    PWM_2_Enable();
    PWM_3_Enable();
    //PWM_4_Enable();
    
    
    
}

float *get_coords(int row, int col, bool king, bool zone) {
    int piece_height = 1;
    int king_height = 2* piece_height;
    float base_offset = 60.625;
    static float coords[3];
    if(zone) {
        coords[0] = board_coords[row][col][0];
        coords[1] = board_coords[row][col][1] + base_offset;
    } 
    else {
        coords[0] = dead_coords[row][col][0];
        coords[1] = dead_coords[row][col][1] + base_offset;
    }
    coords[2] = (king?king_height:piece_height) - 9.928;
    
    return coords;   
}

float *inverse_Kinematics(float *coord) {
    static float angles[4];
    
    // Get Coordinates
    float x = coord[0];
    float y = coord[1];
    float z = coord[2];
    
    // Define Robotic Arm Dimensions
    float L1 = 9.626;
    float L2 = 23.5;
    float L3 = 18.475;
    float L4 = 9;
    float phi = PI/2;
    
    // Theta 1 
    angles[0] = atan2(y,x);
    angles[0] = angles[0] + tan(6/sqrt(x*x+y*y));
    
    // Theta 3
    float r = sqrt(x*x+y*y);
    float Z = z + L4 - L1;
    angles[2] = acos((r*r+Z*Z - L2*L2 - L3*L3) / (2*L2*L3));

    // Theta 2
    angles[1] = atan2(Z,r) - atan2((L3*sin(angles[2])),(L2+L3*cos(angles[2])));
    
    // Theta 4
    angles[3] = phi - angles[1] - angles[3];
    
    angles[0] = rad2deg(angles[0]);
    angles[1] = rad2deg(angles[1]);
    angles[2] = rad2deg(angles[2]);
    angles[3] = rad2deg(angles[3]);
    
    return angles;
}

float rad2deg(float rad) {
    return rad*180/PI;   
}

float angle_1_to_compare(float angle) {
    return angle/180*(5000-1000)+1000;
}

float angle_2_to_compare(float angle) {
    return angle/90*(3000-1200)+1200;
}

float angle_3_to_compare(float angle) {
    return angle/180*3500+1000;
}

float angle_4_to_compare(float angle) {
    return angle/180*2000+2000;
}

void jump_to(float servo1, float servo2, float servo3, float servo4) {
    PWM_1_WriteCompare(angle_1_to_compare(servo1));
    PWM_2_WriteCompare(angle_2_to_compare(servo2));
    PWM_3_WriteCompare(angle_3_to_compare(servo3));
    PWM_4_WriteCompare(angle_4_to_compare(servo4));
}

void move_to(float servo[]) {
    int fin_1 = 0, fin_2 = 0, fin_3 = 0, fin_4 = 0;
    int speed = 10;
    
    float angle1 = angle_1_to_compare(servo[0]);
    float angle2 = angle_2_to_compare(servo[1]);
    float angle3 = angle_3_to_compare(servo[2]);
    float angle4 = angle_4_to_compare(servo[3]);
    
    int target1 = (int)round(angle1);
    int target2 = (int)round(angle2);
    int target3 = (int)round(angle3);
    int target4 = (int)round(angle4);
    
    target1 = target1 - target1%speed;
    target2 = target2 - target2%speed;
    target3 = target3 - target3%speed;
    target4 = target4 - target4%speed;
    
    int current1 = PWM_1_ReadCompare();
    int current2 = PWM_2_ReadCompare();
    int current3 = PWM_3_ReadCompare();
    int current4 = PWM_4_ReadCompare();
    
    current1 = current1 - current1%speed;
    current2 = current2 - current2%speed;
    current3 = current3 - current3%speed;
    current4 = current4 - current4%speed;
    
    while (fin_1+fin_2+fin_3+fin_4 != 4) {
        if (target1 < current1) {
            current1 -= speed;
        } else if (target1 > current1) {
            current1 += speed;
        } else {
            fin_1 = 1;
        }

        if (target2 < current2) {
            current2 -= speed;
        } else if (target2 > current2) {
            current2 += speed;
        } else {
            fin_2 = 1;
        }
        
        if (target3 < current3) {
            current3 -= speed;
        } else if (target3 > current3) {
            current3 += speed;
        } else {
            fin_3 = 1;
        }
        
        if (target4 < current4) {
            current4 -= speed;
        } else if (target4 > current4) {
            current4 += speed;
        } else {
            fin_4 = 1;
        }
        
        PWM_1_WriteCompare(current1);
        PWM_2_WriteCompare(current2);
        PWM_3_WriteCompare(current3);
        PWM_4_WriteCompare(current4);
        
        CyDelay(20);
    }
}


/* [] END OF FILE */