
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* 
 The following program changes the ownership of the file  named  in  its
       second  command-line  argument to the value specified in its first com‐
       mand-line argument.  The new owner can be specified either as a numeric
       user  ID,  or  as  a username (which is converted to a user ID by using
       getpwnam(3) to perform a lookup in the system password file).
 */

int main(int argc, char *argv[])
{
    uid_t uid;
    struct passwd *pwd;
    char *endptr;

    if (argc != 3 || argv[1][0] == '\0')
    {
        fprintf(stderr, "%s <owner> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    uid = strtol(argv[1], &endptr, 10); /* Allow a numeric string */
    if (*endptr != '\0')
    {                            /* Was not pure numeric string */
        pwd = getpwnam(argv[1]); /* Try getting UID for username */
        if (pwd == NULL)
        {
            perror("getpwnam");
            exit(EXIT_FAILURE);
        }
        uid = pwd->pw_uid;
        printf("pwd: %s\n", pwd->pw_passwd);
    }

    // if (chown(argv[2], uid, -1) == -1)// -1,not changed.
    if (chown(argv[2], uid, uid) == -1)
    {
        perror("chown");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
