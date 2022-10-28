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

#include <dirent.h>

#include "client.h"

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

////////////////////////////////
int envoie_operateur_numeros(int socketfd, char *message)
{
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demandez à l'utilisateur d'entrer un message
  char message[1024];
  strcpy(data, "calcule: ");
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


////////////////////////////////

int connect()
{
  int socketfd;

  struct sockaddr_in server_addr;

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

  // appeler la fonction pour envoyer un message au serveur
  //envoie_recois_message(socketfd);

  return socketfd
}

int main() {
	
	char notesPath = "../etudiants/";
	DIR *notesdir = opendir();
	struct dirent *entry;

	if (notesdir == NULL) {
		printf("Impossible d'accéder à ce dossier");
		return 1;
	}

	int stud_count;
	while((entry == readdir(notesdir)) != NULL) {
		stud_count++;
	}

	float stud_mean[stud_count];
	memset(stud_mean, 0, sizeof(stud_mean));

	int i = 0;
	while ((entry = readdir(notesdir)) != NULL ) {
		char dir_name = entry->d_name;
		char stud_dir = malloc(strlen(notesPath) + strlen(entry) + 2);
		while ((file = readdir(notesdir->d_name) != NULL))
	}

	int socketfd = connect()
	
	sum

	close(socketfd)
	return 0;
}

float sum(int socketfd, int *factors, size_t size) {
	float result = *factors;
	char command[256];
	for (int i=0; i < size; i++) {
		sprintf(command, "%d + %d", result, factors[i]);
		envoie_operateur_numeros(command);
	}

	return result
}
