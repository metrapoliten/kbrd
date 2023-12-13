#include <stdio.h>
#include <stdlib.h>

static int checkErr(const char *endptr, const char *buf, const long number) {
    if (errno == ERANGE)
    {
        (void) fprintf(stderr, "\33[31m the number is too small or too large\33[m");
        return 0;
    }
    else if (endptr == buf)
    {
        (void) fprintf(stderr, "\33[31m not a decimal number\33[m");
        return 0;
    }
    else if (*endptr && *endptr != '\n')
    {
        (void) fprintf(stderr, "\33[31m wrong symbols were entered. "
               "Fractional number or odd space after the number may have been entered\33[m");
        return 0;
    }
    else if (errno != 0 && number == 0)
    {
        (void) fprintf(stderr, "\33[31m unspecified error occurred\33[m");
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
            (void) puts("\33[31m reading input error\33[m");
            exit(1);
        }
        char *endptr = NULL;
        errno = 0;
        number = strtol(buf, &endptr, 10);
        successFlag = checkErr(endptr, buf, number);
    } while (!successFlag);
    return number;
}
