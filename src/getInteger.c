#include <stdio.h>
#include <stdlib.h>

int checkErr(const char *endptr, const char *buf, const long number) {
    if (errno == ERANGE)
    {
        puts("the number is too small or too large.");
        return 0;
    }
    else if (endptr == buf)
    {
        puts("the number isn't the integer.");
        return 0;
    }
    else if (*endptr && *endptr != '\n')
    {
        puts("wrong symbols were entered. "
               "Fractional number or odd space after the number may have been entered.");
        return 0;
    }
    else if (errno != 0 && number == 0)
    {
        puts("unspecified error occurred.");
        return 0;
    }
    return 1;
}

long getInteger(const char *outputString)
{
    char buf[1024];
    int successFlag;
    long number;
    do
    {
        printf("%s\n", outputString);
        if (!fgets(buf, 1024, stdin))
        {
            puts("reading input error.");
            exit(1);
        }

        char *endptr = NULL;
        errno = 0;
        number = strtol(buf, &endptr, 10);
        successFlag = checkErr(endptr, buf, number);
    } while (!successFlag);
    return number;
}
