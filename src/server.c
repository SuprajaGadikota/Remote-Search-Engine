/***************************************************************************************************
 *
 *                                       HEADER FILES
 *
 ****************************************************************************************************/
#include <utility.h>

int connfd = -1;
int sd = -1;

void signalHandler(int sig)
{
    printf("Recieved Signal %d\n", sig);
    close(sd);
    close(connfd);
    exit(sig);
}
void exitfunc()
{
    close(sd);
}

/*****************************************************************************************************
 *
 *       FUNCTION NAME : main()
 *       DESCRIPTION : This is the server side main function.
                       This server socket is used to connect with the client socket.
                       We will first create a socket, then we will bind the address,
                       after that we will listen for the connections and connect it
                       to the client socket.
                       In this main function we use 7 functions, which are given below,
                        1. int read_data(int sd, char buf[])
                        2. int write_data(int sd, char buf[])
                        3. search_word_in_file(char * fname, char * str)
                        4. int list_files_recursively(int fd, const char * dirname, char * str)
                        5. char * read_contents(char * buffer, char * file)
                        6. char * read_file_contents(char file_contents[], int num)
                        7. long int findSize(char file_name[])
                       This server will be connected to the client, reads input string,
                       searches for the string in the directories, list out all the files in
                       the directories which contains the string and send them to the client.
                       Then if file number is sent, it displays the conetent of that file.
                       If a filename along with an absloute path is given, it display the
                       contents of the file.
 *       RETURNS : SUCCESS OR FAILURE
 *
 ****************************************************************************************************/

int main()
{
    signal(SIGINT, signalHandler);
    struct sockaddr_in server, client;
    int bindret = -1;
    int lisret = -1;
    int ret = -1;
    socklen_t len;
    pid_t childpid;
    char buf[MAX];
    char addr[MAX];
    char choice_buf[2];
    char rec_path[MAX];
    char user_path[MAX];
    int num;

    /***************************************************************************************************
                            Creaing a TCP socket with Family AF_INET, connection based protocal
                            SOCK_STREAM, Protocol TCP.
    ***************************************************************************************************/
    sd = socket(AF_INET, SOCK_STREAM, 0);

    // If socket is not created then an error message will be printed.

    if (-1 == sd)
    {
        perror("\nSERVER: SOCKET ERROR!!!\n");
        return FAILURE;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(MYPORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // Binding the socket to the address.

    bindret = bind(sd, (struct sockaddr *)&server, sizeof(server));

    // If there is an error while binding an error message is displayed and socket will be closed.
    if (-1 == bindret)
    {
        perror("\nSERVER: BINDING ERROR!!!\n");
        return FAILURE;
    }

    // Listening for connections.

    lisret = listen(sd, 5);

    // If there is an error while listening for connections an error message is displayed and socket will be closed.

    if (-1 == lisret)
    {
        perror("\nSERVER: LISTEN ERROR!!! \n");
        return FAILURE;
    }

    for (;;)
    {
        printf("\n ....WAITING FOR CLIENT....\n");
        memset(&client, 0, sizeof(client));
        len = sizeof(client);

        // Accepting a client connection.

        connfd = accept(sd, (struct sockaddr *)&client, &len);

        // If there is an error while accepting a connection an error message will be printed.

        if (-1 == connfd)
        {
            perror("\nSERVER: CONNECTION ERROR!!!\n");
            return FAILURE;
        }
        if ((childpid = fork()) == 0)
        {
            printf("\n CONNECTION FROM : %s\n", inet_ntop(AF_INET, &client.sin_addr, addr, sizeof(addr)));
            recv(connfd, rec_path, sizeof(rec_path), 0);
            DIR *dir = opendir(rec_path);
            if (dir)
            {
                printf("The received path is :%s\n", rec_path);
                strcpy(user_path, rec_path);
            }
            else
            {
                // strncpy(choice_buf, rec_path, 2);
                perror("SERVER : Error Opening Directory\n");
                close(connfd);
                exit(SUCCESS);
            }
            for (;;)
            {

                ret = recv(connfd, choice_buf, sizeof(choice_buf), 0);
                if (FAILURE == ret)
                {
                    perror("\nSERVER: FAILURE IN READING!!!\n");
                    return FAILURE;
                }

                printf("Recv option: %s\n", choice_buf);
                char choice = choice_buf[0];
                char filenum[5], file_contents[BUFSIZ];
                switch (choice)
                {
                case '1':
                    memset(buf, 0, sizeof(buf));
                    ret = read_data(connfd, buf);
                    if (FAILURE == ret)
                    {
                        perror("\nSERVER: FAILURE IN READING SEARCH STRING!!!\n");
                        // return FAILURE;
                    }

                    system("rm files.txt");
                    system("touch files.txt");
                    int fd = open("files.txt", O_RDWR, 0644);
                    printf("Search string is %s\n", buf);
                    printf("The received path is :%s\n", user_path);
                    int ret = list_files_recursively(fd, user_path, buf);
                    if (FAILURE == ret)
                    {
                        perror("\nSERVER: FAILURE IN GETTING FILES!!!\n");
                        continue;
                        // return FAILURE;
                    }

                    strcpy(buf, read_contents(buf, "files.txt"));
                    if (strlen(buf) < 5)
                    {
                        send(connfd, "-1", strlen("-1"), 0);
                        bzero(choice_buf, sizeof(choice_buf));
                        continue;
                    }
                    ret = send(connfd, buf, strlen(buf), 0);
                    if (FAILURE == ret)
                    {
                        perror("\nSERVER: FAILURE IN WRITING FILE NAMES!!!\n");
                        bzero(choice_buf, sizeof(choice_buf));
                        // return FAILURE;
                    }
                    ret = recv(connfd, &filenum, sizeof(filenum), 0);
                    if (filenum[0] == '0')
                    {
                        printf("Denied reading file content from client\n");
                        bzero(choice_buf, sizeof(choice_buf));
                        continue;
                    }
                    if (FAILURE == ret)
                    {
                        perror("\nSERVER: FAILURE IN READING FILE NUMBER!!!\n");
                        bzero(choice_buf, sizeof(choice_buf));
                        continue;
                        // return FAILURE;
                    }
                    printf("\nRecieved file number: %s\n", filenum);
                    num = atoi(filenum);
                    strcpy(file_contents, read_file_contents(file_contents, num - 1));
                    ret = send(connfd, file_contents, strlen(file_contents), 0);
                    if (FAILURE == ret)
                    {
                        perror("\nSERVER: FAILURE IN WRITING FILE CONTENTS!!!\n");
                        // return FAILURE;
                    }
                    fflush(NULL);
                    bzero(buf, sizeof(buf));
                    bzero(filenum, sizeof(filenum));
                    bzero(file_contents, sizeof(file_contents));
                    bzero(choice_buf, sizeof(choice_buf));
                    break;

                case '2':
                    ret = read_data(connfd, buf);
                    if (FAILURE == ret)
                    {
                        perror("\nSERVER: FAILURE IN READING FILE NAME(PATH)!!!\n");
                        // return FAILURE;
                    }
                    // buf[strlen(buf)]='\0';
                    printf("File name is %s", buf);
                    FILE *fpt = fopen(buf, "r");
                    if (fpt)
                    {
                        fclose(fpt);
                        strcpy(file_contents, read_contents(file_contents, buf));
                        // printf("%s", file_contents);
                        file_contents[strlen(file_contents)] = '\0';
                        ret = send(connfd, file_contents, strlen(file_contents), 0);
                        if (FAILURE == ret)
                        {
                            perror("\nSERVER: FAILURE IN WRITING FILE CONTENTS!!!\n");
                            // return FAILURE;
                        }
                    }
                    else
                    {
                        send(connfd, "File Not Found", strlen("File Not Found"), 0);
                    }
                    fflush(NULL);
                    bzero(buf, sizeof(buf));
                    bzero(file_contents, sizeof(file_contents));
                    bzero(choice_buf, sizeof(choice_buf));
                    break;
                case '3':
                    close(connfd);
                    exit(SUCCESS);
                default:
                    printf("Enter valid option\n");
                }
            }
            close(connfd);
        }
    }
    close(sd);
    return SUCCESS;
}
