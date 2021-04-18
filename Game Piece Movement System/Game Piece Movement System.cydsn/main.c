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

#define PI 3.14159265

void initalize();
void setServo_1(float degrees);
void setServo_2(float degrees);
void setServo_3(float degrees);
void setServo_4(float degrees);
float * inverse_Kinematics(float *coord);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    initalize();
    
    float coords[3] = {10, 0, 5};
    float *angles;
    
    angles = inverse_Kinematics(coords);
    
    setServo_1(angles[0]);
    setServo_2(angles[1]);
    setServo_3(angles[2]);
    setServo_4(angles[3]);
    
    for(;;)
    {
        /* Place your application code here. */
        
    }
}

void initalize() {
    PWM_1_Start();
    PWM_2_Start();
    PWM_3_Start();
    PWM_4_Start();
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
    
    // Theta 3
    float r = sqrt(x*x+y*y);
    float Z = z + L4 - L1;
    angles[2] = acos((r*r+Z*Z - L2*L2 - L3*L3) / (2*L2*L3));

    // Theta 2
    angles[1] = atan2(Z,r) - atan2((L3*sin(angles[2])),(L2+L3*cos(angles[2])));
    
    // Theta 4
    angles[3] = phi - angles[1] - angles[3];

    return angles;
}

void setServo_1(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000;

    PWM_1_WriteCompare(val);
}

void setServo_2(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000;

    PWM_2_WriteCompare(val);
}

void setServo_3(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000;

    PWM_3_WriteCompare(val);
}

void setServo_4(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000;

    PWM_4_WriteCompare(val);
}

/* [] END OF FILE */