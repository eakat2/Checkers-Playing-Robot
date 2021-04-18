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

void initalize();
void setServo_1(float degrees);
void setServo_2(float degrees);
void setServo_3(float degrees);
void setServo_4(float degrees);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

int angle_to_pwm(float angle) {
    // 1 ms is compare value of 4559
    // 2 ms is compare value of 4319

    // compare value (CV) for angles (A) of -90 to 90 is found with ~~ CV = -4A/3 + 4439 
    float CV = 4439 - (4 * angle) / 3
    
    return round(CV)
}

void initalize() {
    PWM_1_Start();
    PWM_2_Start();
    PWM_3_Start();
    PWM_4_Start();
}

void setServo_1(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000);

    PWM_1_WriteCompare(val)
}

void setServo_2(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000);

    PWM_2_WriteCompare(val)
}

void setServo_3(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000);

    PWM_3_WriteCompare(val)
}

void setServo_4(float degrees) {
    unsigned int val;
    val = degrees/180*2000 + 2000);

    PWM_4_WriteCompare(val)
}

/* [] END OF FILE */