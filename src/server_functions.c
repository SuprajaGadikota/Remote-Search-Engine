#include <utility.h>

char files[MAX][MAX];
int count = 0;

/******************************************************************************************************************************************************************************************************
*
*
*                               FUNCTION NAME: read_data().
                                ARGUMENTS: Takes two Arguments,
                                           1. Socket discriptor of type int,
                                           2. Buffer of type char*.
*                               DESCRIPTION: It reads data from the given Socket descriptor and copy the contents in to buffer.
                                RETURNS: It returns number of bytes read on success and, FAILURE when any error occurs.
*
*
*
******************************************************************************************************************************************************************************************************/
int read_data(int sd, char buf[])
{
    int len = 0;
    int ret = -1;
    int bytes = 0;

    ret = read(sd, &len, sizeof(int));
    if (-1 == ret)
    {
        perror("\nREAD_DATA():READ ERROR!!!\n");
        return FAILURE;
    }

    len = ntohs(len);

    while (bytes < len)
    {
        ret = read(sd, (buf + bytes), (len - bytes));
        if (-1 == ret)
        {
            perror("\nREAD_DATA():READ ERROR!!!\n");
            return FAILURE;
        }
        bytes = bytes + ret;
    }

    buf[bytes + 1] = '\0';
    return bytes;
}

/******************************************************************************************************************************************************************************************************
*
*
*                                       FUNCTION NAME: write_data().
                                        ARGUMENTS: It takes two arguments,
                                                   1. Socket descriptor of type int,
                                                   2. Buffer of type char*.
*                                       DESCRIPTION: It writes data into the socket descriptor from the buffer given.
                                        RETURNS: On success returns Number of bytes written and FAILURE when an error happen.
*
*
*
********************************************************************************************************************************************************************************************************/
int write_data(int sd, char buf[])
{
    int len = 0;
    int ret = -1;
    int bytes = 0;
    int len2 = 0;

    len = strlen(buf);
    len2 = htons(len);

    ret = write(sd, &len2, sizeof(int));
    if (-1 == ret)
    {
        perror("\nWRITE_DATA(): READ ERROR!!!\n");
        return FAILURE;
    }

    while (bytes < len)
    {
        ret = write(sd, (buf + bytes), (len - bytes));
        if (-1 == ret)
        {
            perror("\nWRITE_DATA(): WRITE ERROR!!!\n");
            return FAILURE;
        }
        bytes = bytes + ret;
    }

    return bytes;
}

/******************************************************************************************************************************************************************************************************
*
*
*                               FUNCTION NAME: search_word_in_file(char *fname, char *str).
                                ARGUMENTS: Takes two arguments,
                                           1. fname of type char *, which is the name of file that we want to open.
                                           2. String of type char*, which is the String that we want to search in the file.
*                               DESCRIPTION: Opens the File with the name given as argument fname of type char*.
                                             If File is not present, gives an error "FILE NOT FOUND".
                                             Else, the file will be opened in read mode("r"), and checks whether the string
                                             is present in the file or not.
                                RETURNS: SUCCESS OR FAILURE.
*
*
*
********************************************************************************************************************************************************************************************************/
int search_word_in_file(char *fname, char *str)
{
    FILE *fp;
    char temp[MAX];

    if ((fp = fopen(fname, "r")) == NULL)
    {
        perror("\nSEARCH_WORD_IN_FILE:FILE NOT FOUND\n");
        return FAILURE;
    }

    while (fgets(temp, MAX, fp) != NULL)
    {
        if ((strstr(temp, str)) != NULL)
        {
            // printf("COMPARED\n");
            return SUCCESS;
        }
    }

    // Close the file if still open.
    if (fp)
    {
        fclose(fp);
    }
    return 1;
}

/******************************************************************************************************************************************************************************************************
*
*
*                               FUNCTION NAME: list_files_recursively(int fd, const char *dirname, char *str).
                                ARGUMENTS: Takes 3 arguments,
                                           1. File descriptor of type int,
                                           2. dirname --> Directory name of type char*,
                                           3. search string str of type char*.
*                               DESCRIPTION: This function takes three arguments.
                                             First it will validate whether there is a directory with given dirname.
                                             If directory is null, prints an error message "ERROR OPENING DIRECTORY".
                                             Else, It will read the contents of the directory.
                                             Entity is defined to check whether the contents inside dirname are
                                             DIRECTORY or FILE type.
                                             If the entity is of type DIRECTORY, then this Function will be called recursively
                                             to list all the files inside the directory, and after reaching any files it
                                             will be opened using the function, search_word_in_file(char *fname, char *str),
                                             and checks whether string is present or not.
                                RETURNS: SUCCESS OR FAILURE
*
*
*
********************************************************************************************************************************************************************************************************/
int list_files_recursively(int fd, const char *dirname, char *str)
{
    DIR *dir = opendir(dirname);

    if (dir == NULL)
    {
        perror("\nLIST_FILES_REC: ERROR OPENING DIRECTORY\n");
        return FAILURE;
    }

    struct dirent *entity; // it can be file or directory
    entity = readdir(dir);

    while (entity != NULL)
    {
        char path[MAX] = {0};

        strcat(path, dirname);
        strcat(path, "/");
        strcat(path, entity->d_name);

        if (entity->d_type == DT_REG)
        {
            if (search_word_in_file(path, str) == SUCCESS)
            {
                // printf("%s\n",path);
                strcpy(files[count], path);
                count++;
                char w_file[MAX];
                sprintf(w_file, "%d", count);
                strcat(w_file, "\t\t");
                strcat(w_file, entity->d_name);
                strcat(w_file, "\t\t");
                strcat(w_file, path);
                strcat(w_file, "\n");
                // w_file[strlen(w_file)] = '\0';
                write(fd, w_file, strlen(w_file));
            }
        }

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0)
        {
            list_files_recursively(fd, path, str);
        }

        entity = readdir(dir);
    }

    closedir(dir);
    return SUCCESS;
}

/******************************************************************************************************************************************************************************************************
*
*
*                               FUNCTION NAME: read_contents(char *buffer, char *file)
*                               ARGUMENTS: Takes two arguments,
                                           1. buffer of type char*,
                                           2. file of type char*.
                                DESCRIPTION: This Function is used to read contents of the given file and copy them
                                             into the buffer.
                                             First, the file name will be validated, if file is not present, an error
                                             message "FILE NOT FOUND" is printed.
                                             If file is present, the contents of the file is read and is copied in to
                                             the buffer.
                                             The buffer is then returned.
                                RETURNS: Return buffer string.
*
*
*
********************************************************************************************************************************************************************************************************/

char *read_contents(char *buffer, char *file)
{
    int c;
    FILE *fp;
    printf("%s\n", file);

    if ((fp = fopen(file, "r")) == NULL)
    {
        perror("\nREAD_CONTENTS: FILE NOT FOUND\n");
        exit(FAILURE);
    }

    long int res = findSize(file);
    printf("res is %ld\n", res);
    for (int i = 0; i < res; ++i)
    {
        c = getc(fp);
        if (c == EOF)
        {
            buffer[i] = 0x00;
            break;
        }
        buffer[i] = c;
    }

    buffer[res + 1] = '\0';
    printf("%ld\n", strlen(buffer));
    fclose(fp);
    return buffer;
}

/******************************************************************************************************************************************************************************************************
*
*
*                               FUNCTION NAME: read_file_contents(char file_contents[], int num).
                                ARGUMENTS: Takes two arguments,
                                           1. file_content of type char[].
                                           2. num of type int.
*                               DESCRIPTION: This function is used to read contents of the file in the files array,
                                             at index num, and copy the contents into the file_contents.
                                RETURNS: Returns the file contents at index num in array files.
*
*
*
********************************************************************************************************************************************************************************************************/
char *read_file_contents(char file_contents[], int num)
{
    char file_name[MAX];
    strcpy(file_name, files[num]);
    strcpy(file_contents, read_contents(file_contents, file_name));
    return file_contents;
}

/******************************************************************************************************************************************************************************************************
*
*
*                               FUNCTION NAME: findSize(char file_name[]).
                                ARGUMENTS: Takes a single argument file_name of type char[].
*                               DESCRIPTION: This function takes the file name and returns size of the file.
                                RETURNS: Returns the file size.
*
*
*
********************************************************************************************************************************************************************************************************/
long int findSize(char file_name[])
{
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("\nFINDSIZE(): FILE NOT FOUND!\n");
        // return -1;
    }

    fseek(fp, 0L, SEEK_END);

    long int res = ftell(fp);

    fclose(fp);

    return res;
}
