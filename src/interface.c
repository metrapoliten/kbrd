#include <stdio.h>

#include "doStuff.h"

#define DEBUG_MSG

enum options
{
    ON = 's',
    OFF = 'o',
    CHANGE_COLOR = 'c',
    CHANGE_BRIGHTNESS = 'b',
    HELP = 'h',
    LIST_OPTIONS = 'l',
    QUIT = 'q',
#ifdef DEBUG_MSG
    DEBUG_OPTION = 'd',
#endif
};

void clearStdin(void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}

static void printHelp(void)
{
    (void) puts("\n\33[1m Help\33[m\n"

                "  \33[1m set brightness:\33[m\n"

                "brightness value is defined by number in range [0, 100]\n"
                "0 - minimum brightness (actually without light)"
                "100 - maximum brightness\n"

                "  \33[1m set color:\33[m\n"

                "color (RGB) is defined by three numbers separated by spaces, "
                "e.g. type \"255 0 0\" for pure red\n"
                "also, you can define only red or green, "
                "e.g. type \"255 255\" for yellow\n"
                "be careful if you type number more than 255 color will change to undefined\n");
}

static void printOptions(void)
{
    (void) puts("\33[1m available commands:\33[m\n"
                "  s     on\n"
                "  o     off\n"
                "  b     set brightness\n"
                "  c     set color\n"
                "  h     usage help\n"
                "  l     list commands\n"
                "  q     quit\n");
}

int run(hid_device *dev)
{
    char optionBuf[4] = {0};
    int res;

    printOptions();
    while (optionBuf[0] != QUIT)
    {
        (void) fputs("command (l for list): ", stdout);
        (void) scanf(" %4s", optionBuf);
        if (optionBuf[0] == '\n' || (optionBuf[1] != '\n' && optionBuf[1] != 0))
        {
            (void) fprintf(stderr, "\33[31m check your input\33[m\n");
            optionBuf[0] = '\0';
            clearStdin();
        }
        else
        {
            clearStdin();
            switch (optionBuf[0])
            {
                case CHANGE_BRIGHTNESS:
                    res = sendBrightness(dev);
                    if (res == -1)
                    {
                        (void) fprintf(stderr,
                                       "\33[31m level of brightness must be from 0 to 100 inclusively\33[m\n");
                    }
                    break;
                case CHANGE_COLOR:
                    sendMonocolor(dev);
//                    clearStdin();
                    break;
                case HELP:
                    printHelp();
                    break;
                case LIST_OPTIONS:
                    printOptions();
                    break;
                case QUIT:
                    break;
#ifdef DEBUG_MSG
                case DEBUG_OPTION:
                    sendDebug(dev);
                    break;
#endif
                default:
                    fprintf(stderr, "\33[31m check your input\33[m\n");
                    break;
            }
        }
    }

#if 0
    unsigned char buf_get[256];
    memset(buf_get,0,sizeof(buf));

    res = hid_get_feature_report(handle, buf, sizeof(buf));
    if (res < 0) {
        printf("Unable to get a feature report: %ls\n", hid_error(handle));
    }
    else {
        // Print out the returned buffer.
        printf("Feature Report\n   ");
        for (i = 0; i < res; i++)
            printf("%02x ", (unsigned int) buf[i]);
        printf("\n");
    }
#endif
    return 0;
}
