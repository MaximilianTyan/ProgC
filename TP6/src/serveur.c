/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"

//////////////////////////////////////////////////////////////////////////////////////////

/*
* Afficher les couleurs données sous forme de cercle
*/

int check_val(char val) {
  char filter[] = "0123456789.,;#abcdefghijklmnopqrstuvwxyz";
  for (int i=0; i < (int) strlen(filter); i++) {
      if (val == filter[i]) {
        return 1;
      }
    }
  return 0;
}


void plot(char *rawdata, int nb_colors)
{ 
  char data[1024];
  char *dataptr = data;
  memset(data, 0, sizeof data);

  for (int i=0; i < (int) strlen(rawdata); i++) {
    if (check_val(rawdata[i])) {
      *(dataptr++) = rawdata[i];
    }
  }
  printf("Raw: %lu, Clean: %lu\n", strlen(rawdata), strlen(data));


  printf("Plotting: %s\n", data);
  // Extraire le compteur et les couleurs RGB
  FILE *p = popen("gnuplot -persist", "w");
  printf("Plot\n");
  int count = 0;
  int n;
  char *saveptr = NULL;
  char *str = data;
  fprintf(p, "set xrange [-15:15]\n");
  fprintf(p, "set yrange [-15:15]\n");
  fprintf(p, "set style fill transparent solid 0.9 noborder\n");
  fprintf(p, "set title 'Top %d colors'\n", nb_colors);
  fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
  while (1)
  {
    char *token = strtok_r(str, ",", &saveptr);
    if (token == NULL)
    {
      break;
    }
    str = NULL;
    printf("%d: %s\n", count, token);
    if (count == 1)
    {
      n = atoi(token);
      printf("n = %d\n", n);
    }
    else
    {
      // Le numéro 36, parceque 360° (cercle) / 10 couleurs = 36
      int color_angle = 360/nb_colors;
      fprintf(p, "0 0 10 %d %d 0x%s\n", (count - 1) * color_angle, count * color_angle, token + 1);
    }
    count++;
  }
  fprintf(p, "e\n");
  printf("Plot: FIN\n");
  pclose(p);

}

//////////////////////////////////////////////////////////////////////////////////////////////

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{ 
  printf("----- RESPONSE -----\n");
  printf("%s\n", data);
  int data_size = write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////////////////////

int calculate(int client_socket_fd, char *data) {
  
  float a, b, result;

  char op = data[strlen("calcule: ")];
  //printf("op: %c\n", op);

  char stra[16];
  memset(stra, 0, sizeof stra);
  char *ptra = stra;

  char strb[16];
  memset(strb, 0, sizeof strb);
  char *ptrb = strb;

  int spacecount = 0;
  for (int i=0; i < (int) strlen(data); i++) {

    /* a filter had to be implemented because of parasite
    * values hindering the conversion process
    */
    if (! (data[i] == '0' || 
           data[i] == '1' ||
           data[i] == '2' ||
           data[i] == '3' ||
           data[i] == '4' ||
           data[i] == '5' ||
           data[i] == '6' ||
           data[i] == '7' ||
           data[i] == '8' ||
           data[i] == '9' ||
           data[i] == '.' ||
           data[i] == ',' ||
           data[i] == ' ')) {
            continue;
           }


    if (data[i] == ' ') {
      spacecount++;
      continue;
    }
    
    if (spacecount == 2) {
      *(ptra++) = data[i];
    }
    if (spacecount == 3) {
      *(ptrb++) = data[i];
    }
  }

  sscanf(stra, "%f", &a);
  sscanf(strb, "%f", &b);

  //printf("a: %s -> %f\n", stra, a);
  //printf("b: %s -> %f\n", strb, b);


  printf("Calculating: %c %f %f\n", op, a, b);
  switch (op) {
    case '+':
      result =  a + b;
      break;

    case '-':
      result =  a - b;
      break;

    case '*':
      result = a * b;
      break;

    case '/':
      result = a / b;
      break;

    default:
      printf("'%c' operation not implemented", op);
      break;
  }

  // la réinitialisation de l'ensemble des données
  size_t size = sizeof(data);
  memset(data, 0, size);

  sprintf(data, "%f", result);

  renvoie_message(client_socket_fd, data);
  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd)
{
  struct sockaddr_in client_addr;
  char data[1024];

  unsigned int client_addr_len = sizeof(client_addr);
  while (1) {
    // nouvelle connection de client
    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      return (EXIT_FAILURE);
    }
    printf("CONNECTION ACCEPTED\n");
    
    // la réinitialisation de l'ensemble des données
      memset(data, 0, sizeof(data));
      int data_size = 1;

    while (data_size) {
      data_size = read(client_socket_fd, (void *)data, sizeof(data));
      // lecture de données envoyées par un client
      
      if (data_size == 0) {
        continue;
      }

      if (data_size < 0)
      {
        perror("erreur lecture");
        return(EXIT_FAILURE);
      }
      

      /*
      * extraire le code des données envoyées par le client.
      * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
      * Si le message commence par "plot:", la première valeur sera le nombre de couleurs
      */
      printf("----- REQUEST -----\n");
      printf("%s\n", data);

      // Si le message commence par le mot: 'message:'
      if (strncmp(data, "message:", strlen("message:")) == 0)
      { 
        //printf("Message recieved\n");
        renvoie_message(client_socket_fd, data);
      }
      else if (strncmp(data, "couleurs:", strlen("couleurs:")) == 0)
      { 
        //printf("Colors recieved\n");
        int nb_colors = 0;
        char colors_data[1024];
        sscanf(data, "couleurs:%d,%s", &nb_colors, colors_data);

        plot(colors_data, nb_colors);
      }
      else if (strncmp(data, "calcule:", strlen("calcule:")) == 0) 
      {
        calculate(client_socket_fd, data);
      }
      else
      {
        printf("No matching pattern detected\n");
      }
          // fermer le socket
    } // accept loop
    close(client_socket_fd);
  }
    return(EXIT_SUCCESS);
  } 



///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

  int socketfd;
  int bind_status;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Écouter les messages envoyés par le client
    listen(socketfd, 10);

  // Lire et répondre au client
  recois_envoie_message(socketfd);

  return 0;
}
