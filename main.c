/*
** EPITECH PROJECT, 2021
** temp
** File description:
** main
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define ALARM_WAIT 2

int temp_target = 0;

int getTemp(void)
{
    return rand() % 11 + 15;
}

void decToBinary(unsigned char c)
{
    for (unsigned i = 1 << 7; i > 0; i = i / 2)
        (c & i) ? printf("1") : printf("0");
}

void resultTemp(unsigned char c, unsigned char mode, unsigned char diff)
{
    c = mode | diff;
    printf("RESULT : %d, diff : %d\n", c, diff);
    printf("\t%d = 00000000 00000000 00000000 ", c);
    decToBinary(c);
    printf("\n");
}

void onAlarm(void)
{
    int temp = getTemp();
    unsigned char c = 0;
    unsigned char diff = 0;

    printf("Temp : %d°\n", temp);
    if (temp - temp_target >= -1 && temp - temp_target <= 1) {
        diff = 1;
    } else if (temp - temp_target >= -2 && temp - temp_target <= 2) {
        diff = 2;
    } else {
        diff = 3;
    }
    if (temp_target < temp) {
        printf("REFROIDIR\n");
        resultTemp(c, 128, diff);
    } else if (temp_target == temp) {
        printf("TEMP_OK\n");
        resultTemp(c, 0, diff);
    } else {
        printf("CHAUFFER\n");
        resultTemp(c, 64, diff);
    }
}

void handleSigAlarm(int sig)
{
    printf("\n");
    alarm(ALARM_WAIT);
    printf("ALARM\n");
    onAlarm();
}

int main(void)
{
    srand(time(0));
    signal(SIGALRM, handleSigAlarm);

    printf("Enter temp target :");
    scanf("%d", &temp_target);
    alarm(ALARM_WAIT);
    while (1);
}
