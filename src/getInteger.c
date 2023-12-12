#include <stdio.h>
#include <stdlib.h>

static int checkErr(const char *endptr, const char *buf, const long number) {
    if (errno == ERANGE)
    {
        (void) fprintf(stderr, "the number is too small or too large.");
        return 0;
    }
    else if (endptr == buf)
    {
        (void) fprintf(stderr, "not a decimal number");
        return 0;
    }
    else if (*endptr && *endptr != '\n')
    {
        (void) fprintf(stderr, "wrong symbols were entered. "
               "Fractional number or odd space after the number may have been entered.");
        return 0;
    }
    else if (errno != 0 && number == 0)
    {
        (void) fprintf(stderr, "unspecified error occurred.");
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
        printf("%s", outputString);
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
