#include <utility.h>
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
******************************************************************************************************************************************************************************************************/
int read_data(int sd, char buf[])
{
    int len = 0;
    int ret = -1;
    int bytes = 0;

    ret = read(sd, &len, sizeof(int));
    if (-1 == ret)
    {
        perror("\n READ ERROR!!!\n");
        return FAILURE;
    }

    len = ntohs(len);

    while (bytes < len)
    {
        ret = read(sd, (buf + bytes), (len - bytes));
        if (-1 == ret)
        {
            perror("\n READ ERROR!!!\n");
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
        perror("\n READ ERROR!!!\n");
        return FAILURE;
    }

    while (bytes < len)
    {
        ret = write(sd, (buf + bytes), (len - bytes));
        if (-1 == ret)
        {
            perror("\n WRITE ERROR!!!\n");
            return FAILURE;
        }
        bytes = bytes + ret;
    }

    return bytes;
}
