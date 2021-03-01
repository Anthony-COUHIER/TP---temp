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

int getTemp(void)
{
    return rand() % 11 + 15;
}

void onAlarm(void)
{
    printf("Temp : %d°\n\n", getTemp());
}

void handleSigAlarm(int sig)
{
    alarm(ALARM_WAIT);
    printf("ALARM\n");
    onAlarm();
}

int main(void)
{
    srand(time(0));
    signal(SIGALRM, handleSigAlarm);

    alarm(ALARM_WAIT);
    printf("BEGIN\n\n");
    while (1) {
    }
}
