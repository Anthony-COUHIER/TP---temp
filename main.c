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
    // fonction récupéré sur internet pour ecrire en binaire
    for (unsigned i = 1 << 7; i > 0; i = i / 2)
        (c & i) ? printf("1") : printf("0");
}

void resultTemp(unsigned char c, unsigned char mode, unsigned char diff)
{
    // Permet de faire un OU BINAIRE
    c = mode | diff;
    printf("RESULT : %d, diff : %d\n", c, diff);
    printf("\t%d = 00000000 00000000 00000000 ", c);
    // Afficher en binaire une valeur
    decToBinary(c);
    printf("\n");
}

void onAlarm(void)
{
    int temp = getTemp();
    unsigned char c = 0;
    unsigned char diff = 0;

    printf("Temp : %d°\n", temp);
    // permet de récupèrer la différence entre la temperature de
    // la pièce et la valeur rentrée par l'utilisateur
    if (temp - temp_target == 0) {
        diff = 0;
    } else if (temp - temp_target >= -1 && temp - temp_target <= 1) {
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
    // Initialisation du random, time(0) permet de faire un vrai random
    srand(time(0));
    // Permet de dire "quand je recoit le signal SIGALARM (envoyé par la fonction alarm)
    // alors j'execute cette fonction"
    signal(SIGALRM, handleSigAlarm);

    // permet de récupérer la valeur de l'utilisateur
    printf("Enter temp target :");
    scanf("%d", &temp_target);
    // Init la première alarme
    alarm(ALARM_WAIT);
    while (1);
}
