#include <stdio.h>
#include <stdlib.h>

int checkStrtolErrors(const char *endptr, const char *buf, const long number) {
    if (errno == ERANGE) {
        perror("the number is too small or too large.");
        return 0;
    } else if (endptr == buf) {
        perror("the number isn't the integer.");
        return 0;
    } else if (*endptr && *endptr != '\n') {
        perror("wrong symbols were entered. "
               "Fractional number or odd space after the number may have been entered.");
        return 0;
    } else if (errno != 0 && number == 0) {
        perror("unspecified error occurred.");
        return 0;
    }
    return 1;
}

long getInteger(const char *string)
{
    char buf[1024]; //use 1KiB just to be sure
    int successFlag;
    long number;
    do{
        printf("%s\n", string);
        if (!fgets(buf, 1024, stdin)){
            puts("reading input error.");
            exit(1);
        }

        char *endptr = NULL;
        errno = 0;
        number = strtol(buf, &endptr, 10);
        successFlag = checkStrtolErrors(endptr, buf, number);
    } while (!successFlag);
    return number;
}
