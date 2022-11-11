/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "client.h"
#include "bmp.h"

///////////////////////////////////////////////////////////////////////////////////////////////


int isjson = 0;


int envoie_recois_calcul(int socketfd, char *argument)
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));
  strcpy(data, "calcule: ");

  char calcul[1024];

  if (!isjson) {
      // Demandez à l'utilisateur d'entrer un message

    printf("Votre calcul (A opération B): ");
    fgets(calcul, sizeof(calcul), stdin);
    calcul[strlen(calcul)] = '\0';

    strcat(data, calcul);
  } else {
    strcat(data, argument);
  }

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // lire les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Résultat: %s\n", data);

  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */


int envoie_recois_message(int socketfd, char *argument)
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));
  strcat(data, "message: ");

  char message[1000];


  if (!isjson) {
      // Demandez à l'utilisateur d'entrer un message

    printf("Votre message (max 1000 caracteres): ");
    fgets(message, sizeof(message), stdin);
    message[strlen(message)] = '\0';
    strcat(data, message);
  } else {
    strcat(data, argument);
  }

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // lire les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu: %s\n", data);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////

/*
* 
*/

void analyse(char *pathname, char *data, int colors_nb)
{
  // Comptage et triage des couleurs uniques d'une image
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  char temp_string[10];
  sprintf(temp_string, "%d,", colors_nb);
  if (cc->size < 10)
  {
    sprintf(temp_string, "%d,", cc->size);
  }
  strcat(data, temp_string);

  // choisir les colors_nb premières couleurs
  for (count = 1; count < (colors_nb + 1) && cc->size - count > 0; count++)
  {
    if (cc->compte_bit == BITS32)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc24[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    if (cc->compte_bit == BITS24)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc32[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    strcat(data, temp_string);
  }

  // enlever le dernier virgule
  data[strlen(data) - 1] = '\0';
}


///////////////////////////////////////////////////////////////////////////////////////////


int envoie_couleurs(int socketfd, char *pathname)
{
  char data[1024];
  memset(data, 0, sizeof(data));
  strcat(data, "couleurs: ");

  if (!isjson) {
    // Choix du nombre de couleurs
    int colors_nb = 10;
    printf("Nombre de couleurs à afficher: ");
    scanf("%d", &colors_nb);

    // Analyse de l'image (retourne les X premières couleurs de l'image)
    analyse(pathname, data, colors_nb);

    printf("\nMessage final:\n%s\n", data);
  } else {
    strcat(data, pathname); //pathname variable is here used to send direct data
  }

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////


int readfile(char *pathname, int socketfd) 
{

  int fd = open(pathname, O_RDONLY);

  char message[1024];
  memset(message, 0, sizeof(message));

  char letter = 'A';
  char scan_string[16];
  char *scanptr = scan_string;
  memset(scan_string, 0, sizeof(scan_string));

  int messagetype = 0;
  // 0: message
  // 1: calcul
  // 2: couleurs

  int table[4][4] = {
    {0,1,0,0}, //attente de code
    {1,2,1,1}, // lecture du code
    {2,2,3,2}, // attente d'argument
    {3,3,3,0} // lecture d'argument
  };
  int conditionswitch = 0;
  int state = 0;
  int prevstate = 0;

  int readingmessage = 0;

  // Scanning loop
  while (read(fd, &letter, 1)) {
    
    // Ignored characters
    if (state != 3) {
      if (letter == ' ' || letter == '\n') { 
        continue; 
      }
    }

    switch (letter) {
      case '"':
        conditionswitch = 1;
        break;
      
      case '[':
        conditionswitch = 2;
        break;
      
      case ']':
        conditionswitch = 3;
        break;
      
      default:
        conditionswitch = 0;
    }

    prevstate = state;
    state = table[state][conditionswitch];

    /*
    if (prevstate != state) {
      printf("NEW STATE: %d->%d (letter: %c)\n", prevstate, state, letter);
    }
    */



    // code has been read, proceeds to compare the code
    if (state == 2 && prevstate == 1) { 
      if (strcmp(scan_string, "message") == 0) {
        printf("CODE MESSAGE: '%s'\n", scan_string);
        messagetype = 0;
      }

      else if (strcmp(scan_string, "calcule") == 0) {
        printf("CODE CALCULE: '%s'\n", scan_string);
        messagetype = 1;
      }

      else if (strcmp(scan_string, "couleurs") == 0) {
        printf("CODE COULEURS: '%s'\n", scan_string);
        messagetype = 2;
      }

      else {
        state = 0; //if code not valid, reset
        printf("INVALID CODE: '%s'\n", scan_string);
        continue;
      }
    }
    
    // reset scan buffer to prepare for next scan
    if ( (state == 1 && prevstate == 0) || (state == 3 && prevstate == 2)) {
        printf("RESET SCAN BUFFER: ");
        //memset(scan_string, 0, sizeof(scan_string));
        for (int i=0; i <= (int) sizeof(scan_string); i++) {
            scan_string[i] = '\0';
          }
        scanptr = scan_string;
        printf("'%s'\n", message);
    }

    // writing string buffers
    if (state == 1) {
      if ( letter == '"' || letter == '[' 
            || letter == ']' || letter == ' ') {
        continue;
      }
      // read code
      *(scanptr) = letter;
      scanptr ++;
    }

    if (state == 3) {
      // used to supress spaces outside ou quotes
      if (letter  == '"') {
        readingmessage = !readingmessage;
        continue;
      }
      if (!readingmessage && letter == ' ') {
        continue;
      }
      
      if (letter == '[' || letter == ']') {
        continue;
      }

      strcat(message, &letter);
    }

    // argument have been read, sending message
    if ( state == 0 && prevstate == 3 ) {

      switch (messagetype) {
        case 0: //message
          printf("SENDING MESSAGE: '%s'\n", message);
          envoie_recois_message(socketfd, message);
          break;


        case 1: // calcul
          for (int i=0; i < (int) strlen(message); i++) {
            if (message[i] == ',') {
              message[i] = ' ';
            }
          }
          
          printf("SENDING CALCUL: '%s'\n", message);
          envoie_recois_calcul(socketfd, message);
          break;


        case 2: //couleurs
          char data[1024];
          memset(data, 0, sizeof data);
          
          // count different colors for the length prefix
          // number of colors = number of separators + 1
          int colours_count = 1;
          for (int i=0; i < (int) strlen(message); i++) {
            if (message[i] == ',') {
              colours_count ++;
            }
          }
          // adds prefix and initial '#' for the first color
          char countstr[8];
          memset(data, 0, sizeof countstr);
          sprintf(countstr, "%d,#", colours_count);
          strcpy(data, countstr);


          char formatted_data[1024];
          char *fdata_ptr = formatted_data;
          memset(formatted_data, 0, sizeof formatted_data);

          
          // adds '#' in front of every color
          for (int i = 0; i < (int) strlen(message); i++) {
            *(fdata_ptr++) = message[i];
            if (message[i] == ',') {
              *(fdata_ptr++) = '#';
            }
          }
          

          strcat(data, formatted_data);

          printf("SENDING COULEURS: '%s'\n", data);
          envoie_couleurs(socketfd, data);
          break;
      }
      printf("MESSAGE SENT\n");
    }
  
  //scan end
  }
    return 0;

}

/////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
  int socketfd;

  struct sockaddr_in server_addr;

  if (argc < 2)
  {
    printf("usage: command argument\n");
    return (EXIT_FAILURE);
  }

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }


  if (strcmp(argv[1], "json") == 0) {
    isjson = 1;
  }


  if (isjson) {
    readfile(argv[2], socketfd);
  }

  else if (*argv[1] == 'c') //calculate
  {
    envoie_recois_calcul(socketfd, argv[2]);
  }
  else if (*argv[1] == 'p') //plot
  {
    // envoyer et recevoir les couleurs prédominantes
    // d'une image au format BMP (filepath = argv[2])
    envoie_couleurs(socketfd, argv[2]);
  }
  else //message
  {
    // envoyer et recevoir un message
    envoie_recois_message(socketfd, argv[2]);
  }

  close(socketfd);
}
