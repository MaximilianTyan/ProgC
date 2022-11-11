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

#include "client.h"
#include "bmp.h"

///////////////////////////////////////////////////////////////////////////////////////////////

int envoie_recois_calcul(int socketfd)
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demandez à l'utilisateur d'entrer un message
  char calcul[1024];
  printf("Votre calcul (A opération B): ");
  fgets(calcul, sizeof(calcul), stdin);
  strcpy(data, "calcule: ");
  strcat(data, calcul);

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


int envoie_recois_message(int socketfd)
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demandez à l'utilisateur d'entrer un message
  char message[1024];
  printf("Votre message (max 1000 caracteres): ");
  fgets(message, sizeof(message), stdin);
  strcpy(data, "message: ");
  strcat(data, message);

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

  // Choix du nombre de couleurs
  int colors_nb = 10;
  printf("Nombre de couleurs à afficher: ");
  scanf("%d", &colors_nb);

  strcat(data, "couleurs: ");

  // Analyse de l'image (retourne les X premières couleurs de l'image)
  analyse(pathname, data, colors_nb);

  printf("\nMessage final:\n%s\n", data);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////


int readfile(char *pathname, int client_socket_fd) 
{ 

  int fd = open(pathname, O_RDONLY);

  // Scanning flags
  //int openQuote = 0;
  //int openBracket = 0;
  //int codeflag = 0;

  char letter = "A";
  char scan_string[32];
  char *scanptr = scan_string;
  memset(scan_string, 0, sizeof(scan_string));

  int table[][] = {
    {},
    {},
    {},
    {}
  }



  while (letter != NULL) {
    read(fd, letter, 1);
    
    // Ignored characters
    if (letter == ' ' || letter == '\n' || letter == ',') { 
      continue; 
    }


    if ""









    /*
    // Opening / Closing characters
    else if (letter == '[') {
      openBracket = 1;
    }
    else if (letter == ']') {
      openBracket = 0;
    }

    else if (letter == '"') {
      // NOT operator
      openQuote = (1 & ~openQuote);

      if (openQuote) { //  opening quote: reset string buffer
          memset(scan_string, 0, sizeof scan_string);
          scanptr = scan_string;
      }
      else {  // closing quote, compare stored buffer
        // "code" field
        if (strncmp(scan_string, "code", sizeof "code") == 0) {
          codeflag = 1;
        }


        else if (codeflag && strncmp(scan_string, "message", sizeof "message")) {

        }

        else if (codeflag && strncmp(scan_string, "calcule", sizeof "calcule")) {

        }

        else if (codeflag && strncmp(scan_string, "couleurs", sizeof "couleurs")) {

        }


     
        


      }
    }

    if (openQuote) {
        // saves characters in buffer for comparison
        *(scanptr) = letter;
        scanptr ++;
      }*/
  } //scan end

  return 0;
}







///////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
  int socketfd;

  struct sockaddr_in server_addr;

  if (argc < 2)
  {
    printf("usage: ./client chemin_bmp_image\n");
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
  if (*argv[1] == 'c') //calculate
  {
    envoie_recois_calcul(socketfd);
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
    envoie_recois_message(socketfd);
  }

  close(socketfd);
}
