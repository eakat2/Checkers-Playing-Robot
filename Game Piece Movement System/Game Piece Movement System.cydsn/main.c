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

/* [] END OF FILE */