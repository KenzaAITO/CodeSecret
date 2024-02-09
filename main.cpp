/*
Author : M'hammed Baroudi et Vincent Chaumette
*/
#include "mbed.h"

#define TARGET_TX_PIN USBTX
#define TARGET_RX_PIN USBRX
DigitalOut led(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
static UnbufferedSerial serial_p(p9, p10, 9600);

int main(void) {
  char buffer[100]; // Un tampon pour stocker les données reçues
  int randomNum[3] = {3, 4, 5};
  int verif[4] = {0};

  //génération du random
  /*for (int i = 2; i < 3; i++) {
    randomNum[i] = rand() % 10;
  }*/

  int valeurR;
  int tour = 0;

    //Lecture du clavier tant que l'utilisateur n'a pas appuyé sur 3 touches valides
  while (tour < 3) {
    // Lire les données disponibles depuis l'interface série
    int bytesRead = serial_p.read(buffer, sizeof(buffer) - 1);

    if (bytesRead > 0) {
      buffer[bytesRead] = '\0'; // Ajouter le caractère de fin de chaîne
      printf("Trame reçue : %s\n", buffer);

      // Allumer ou éteindre la LED en fonction de la trame reçue
      switch (buffer[0]) {
      case 0xE1:
        valeurR = 1;
        tour++;
        led = !led;
        break;
      case 0xE2:
        led = !led;
        valeurR = 2;
        tour++;
        break;
      case 0xE3:
        led = !led;
        valeurR = 3;
        tour++;
        break;
      case 0xE4:
        led = !led;
        valeurR = 4;
        tour++;
        break;
      case 0xE5:
        led = !led;
        valeurR = 5;
        tour++;
        break;
      case 0xE6:
        led = !led;
        valeurR = 6;
        tour++;
        break;
      case 0xE7:
        led = !led;
        valeurR = 7;
        tour++;
        break;
      case 0xE8:
        led = !led;
        valeurR = 8;
        tour++;
        break;
      case 0xE9:
        led = !led;
        valeurR = 9;
        tour++;
        break;
      /*case 0xEA:
          led = !led;
          valeurR = 11;
          break; // Pour **/
      case 0xEB:
        led = !led;
        valeurR = 0;
        break; // pour 0
        /*case 0xEC:
            led = !led;
            break; // Pour #*/
      }
      verif[tour] = valeurR;
    }
  }

  // vérification de la correspondance avec le code générer
  int s = 0; // nombre de numéro correct
  for (int i = 0; i < 3; i++) {
    if (randomNum[i] == verif[i + 1]) {
      s++;
      led4 = 1;
      // bonne réponse
      printf("Bonne réponse !\n");
    } else if (randomNum[i] != verif[i + 1]) {
      led4 = 0;
      // mauvaise réponse
      printf("Mauvaise réponse.\n");
    }
  }
  if (s == 3) {
    led3 = 1;
    led2 = 0;
  } else {
    led2 = 1;
    led3 = 0;
  }
}