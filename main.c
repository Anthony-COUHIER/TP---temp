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

void handleSigAlarm(int sig)
{
    printf("ALARM\n");
}

int getTemp(void)
{
    return rand() % 11 + 15;
}

void onAlarm(void)
{
    printf("Temp : %d°\n", getTemp());
}

int main(void)
{
    srand(time(0));
    signal(SIGALRM, handleSigAlarm);

    while (1) {
        alarm(ALARM_WAIT);
        sleep(10);
        onAlarm();
        printf("\n");
    }
}
