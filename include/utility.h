#ifndef __UTILITY_H__
#define __UTILITY_H__

/******************************************************************************************
 *
 *                                       HEADER FILES
 *
 ****************************************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

/***************************************************************************************************************
 *
 *                                               MACROS
 *
 *************************************************************************************************************/
#define SUCCESS 0
#define FAILURE 1
#define MAX 512
#define MYPORT 60038
#define STRING_CHOICE '1'
#define PATH_CHOICE '2'
#define EXIT_CHOICE '3'
/**********************************************************************************************************
 *
 *                                               FUNCTION PROTOTYPE
 *
 ***********************************************************************************************************/
int read_data(int sd, char buf[]);

int write_data(int sd, char buf[]);

char *read_contents(char *, char *);

int search_word_in_file(char *, char *);

int list_files_recursively(int, const char *, char *);

char *read_file_contents(char *, int);

long int findSize(char file_name[]);


#endif