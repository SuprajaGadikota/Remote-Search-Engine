/******************************************************************************************
 *
 *                                       HEADER FILES
 *
 ****************************************************************************************************/
#include <utility.h>


/*****************************************************************************************************
 *
 *       FUNCTION NAME : main()
 *       DESCRIPTION : It is client side main function. 
 *       RETURNS : SUCCESS OR FAILURE
 *
 ****************************************************************************************************/
int sd = -1;

void ClientSignalHandler(int sig){
	printf("Recived Signal\nwith id : %d\n", sig);
	close(sd);
	exit(sig);
}


int main(int argc, char *argv[])
{
	signal(SIGINT, ClientSignalHandler);
    if((argc != 3 || argc != 4) && (argc >4))
    {
	perror("Invalid number of Arguments! Please Enter valid number of arguments...\n");
	return FAILURE;
    }

    struct sockaddr_in server;
    //int sd = -1;
    int connfd = -1;
    int ret = -1;
    char buf[100000];
    char fileC[1000000];
    char file_contents[100000];
    char y_or_n;

/***********************************************************************************************************************************************************     Creating the TCP client socket with Family --> AF_INET, Connection-based protocol SOCK_STREAM .
    The socket function return -1 if socket is not created.
    Returns some positive number if socket is created successfully. 
***********************************************************************************************************************************************************/

    sd = socket(AF_INET, SOCK_STREAM, 0);

/*  Checking wheather socket is created or not.
    If sd == -1 it prints an error message and returns FAILURE. */

    if (-1 == sd)
    {
        perror("\nCLIENT: SOCKET ERROR!!!\n");
        return FAILURE;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    
/***********************************************************************************************************************************************************     Connect() is used to connect the socket to a server socket. 
    It takes the arguments socket descriptor, address, and sizeof the structure we defined. 
    Returns -1 if Connection is not done. 
    Returns some positive value when connection is done properly.  
***********************************************************************************************************************************************************/

    connfd = connect(sd, (struct sockaddr *)&server, sizeof(server));

/*  If return value of connect is -1, print error message. */

    if (-1 == connfd)
    {
        perror("\nCLIENT: CONNECTION ERROR!!\n");
	close(sd);
        return FAILURE;
    }
/***********************************************************************************************************************************************************     Checking Whether There is a Path mentioned by the user as a third argument or not. 
    If Path is present then send that path to the server using send function. 
    send() takes 4 arguments, socket description, char *, sizeof char *, type. 
***********************************************************************************************************************************************************/
    
    if(argv[3]){                        //checking if there is any user given path -RES1
    	send(sd, argv[3], MAX, 0); 
    }
    
    else{
    	send(sd, "/home/", MAX, 0);
    }
    
/***********************************************************************************************************************************************************     Menu Driven Interface. 
    Asks The user to select one option from the three mentioned below. 
    1. Search a String. 
    2. Search by Path. 
    3. Exit. 

    If Option '1' is Selected, User will be asked to Enter a String. 
    If no file Contains the String, it display a message "No Entry of the String ".  
    Else all the Files are Displayed to the user along with the Path where they are present. 
    Then user will be asked whether they want to see the contents of the File or not. 
    If user want to see the contents of a Particular file, he needs to enter 'Y', else 'N'. 
    If 'Y', Then user will be asked to enter the File number. And then it's contents are displayed. 
    Again user will be asked whether they want to continue or not. 
    If 'N', then the Options will be Displayed again. 

    If Option '2' is Selected, User will be asked to enter the file name and absolute path. 
    If the File exists, it will Display the Contents of the File. 
    Else a message is Displayed saying The File does not exits. 
    The Options will be Displayed again. 

    If Option '3' is Selected, The program will be Stopped.
***********************************************************************************************************************************************************/
    while (1)
    {
    	system("clear");


    	printf("**********************************************\n");
    	printf("     WELCOME TO REMOTE SEARCH ENGINE          \n");
    	printf("**********************************************\n\n");
        printf("\n1.Search by String. \n2.Search by PATH. \n3.EXIT. \nEnter your choice: "); //menu driven interface
        char choice;
        scanf(" %c", &choice); //taking user choice of searching
        getchar();
        if(choice=='1'||choice=='2'||choice=='3')
        {
        	char choice_buf[2] = {choice, '\0'};   
        	ret = send(sd, choice_buf, sizeof(choice_buf), 0);
        	if (FAILURE == ret)
        	{
            		perror("\nCLIENT: ERROR IN WRITING OPTION!!!\n");
            		return FAILURE;
        	}
        	char search[MAX],file_search[MAX];
        	fflush(NULL);
        
        	if (choice == STRING_CHOICE)                                          //RSE 2 and 4
        	{
            	printf("Please enter string/word/sentence to search: "); //passing string for searching
            	fgets(search, sizeof(search), stdin);
            	search[strcspn(search, "\n")] = 0;
            	search[strlen(search)] = '\0';
            	ret = write_data(sd, search);
            	if (FAILURE == ret)
            	{
                	perror("\nCLIENT: ERROR IN WRITING SEARCH!!!\n");
					close(sd);
                	return FAILURE;
            	}

            	ret = read(sd, &buf, sizeof(buf));
            	if (-1 == ret)
            	{
                	perror("\nCLIENT: ERROR IN READING BUFF(FILE NAMES)!!\n");
					close(sd);
                	return FAILURE;
            	}
            	if(strcmp("-1", buf) == 0){
            		printf("No Entry of the String\n");
            		printf("Continue? [y/n]\n");      //checking if user wants to continue
        		scanf(" %c", &y_or_n);
        		if(y_or_n == 'n'){
        			send(sd, "3", sizeof("3"), 0);
        			break;
        		}
        		else{
        			continue;
        		}
            	}
            	printf("\nfiles are:\n");
            	printf("%s\n", buf);
            
            	printf("View Contents of File? [y/n]\n");
            	scanf(" %c", &y_or_n);
            	char fileNum[5];
            	if(y_or_n=='y'||y_or_n=='Y'||y_or_n=='n'||y_or_n=='N')
            	{
            		if(y_or_n == 'y' || y_or_n == 'Y'){
            			printf("Enter the file number: "); //showing the content according to the input number
            			scanf("%s", fileNum);
            			ret = send(sd, fileNum, sizeof(fileNum), 0);
            		if (FAILURE == ret)
            		{
                		perror("\nCLIENT: ERROR IN WRITING FILE NUMBER!!!\n");
						close(sd);
                		return FAILURE;
            		}
            		ret = read(sd, &file_contents, sizeof(buf));
            		if (-1 == ret)
            		{
                		perror("\nCLIENT: ERROR IN READING FILE CONTENTS!!\n");
				close(sd);
                		return FAILURE;
            		}
            		printf("\n files contents are: %s\n", file_contents);        //showing file Contents
            
            		}
            	else{
            		send(sd, "0", sizeof("0"), 0);
            	}
            	bzero(search,sizeof(search));
            	bzero(buf,sizeof(buf));
            	bzero(fileNum,sizeof(fileNum));
            	bzero(file_contents,sizeof(file_contents));
            }
            else
            {
            	printf("enter a valid choice\n");
            }

        }

        else if (choice == PATH_CHOICE)
        {
            printf("Enter file name:");
            fgets(file_search, sizeof(file_search), stdin); //taking absolute path rse3
            file_search[strcspn(file_search, "\n")] = 0;
            file_search[strlen(file_search)] = '\0';
            printf("File name:%s", file_search);  
            ret = write_data(sd, file_search);
            if (FAILURE == ret)
            {
                perror("\nCLIENT: ERROR IN WRITING SEARCH(FILENAME)!!!\n");
                close(sd);
		return FAILURE;
            }
            memset(&fileC, 0, sizeof(fileC));
            ret = recv(sd, &fileC, sizeof(fileC), 0);
            if (-1 == ret)
            {
                perror("\nCLIENTERROR IN READING FILE CONTENTS!!\n");
		close(sd);
                return FAILURE;
            }
            printf("\nFiles contents are: %s\n", fileC);
            bzero(file_search,sizeof(file_search));
            bzero(fileC,sizeof(fileC));
        }

        else if (choice == EXIT_CHOICE)
        {
            exit(EXIT_SUCCESS);
        }
        }
        else
        {
            printf("Enter valid option\n");
        }
        printf("Continue? [y/n]\n");
        scanf(" %c", &y_or_n);
        printf("Exiting from the Search engine! \n");
        if(y_or_n == 'n'){
        	send(sd, "3", sizeof("3"), 0);  //exiting file
        	break;
        }
        fflush(NULL);
    }
    close(sd);
    return SUCCESS;
}
