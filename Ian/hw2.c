/*
 * Speed limit - Accepts number of measurements to make, current speed in mph
 * and speed limit in kph. Tells you if you are speeding.
 */

#include <stdio.h>
#define MPH_TO_KPH 1.61

int main(void)
{
    int i, speed_mph, limit_kph, count;
    float speed_kph;

    printf("Number of entries:");
    scanf("%d", &count);
    for (i = 0; i < count; ++i) {
        printf("What's the speed limit in kph? ");
        scanf("%d", &limit_kph);
        printf("What is your speed in mph? ");
        scanf("%d", &speed_mph);
        speed_kph = speed_mph * MPH_TO_KPH;
        if (speed_kph > limit_kph)
            printf("You are speeding! Slow down! You are going %.1f kph "
                   "in a %d kph zone!\n", speed_kph, limit_kph);
    }
    return 0;
}
