#include <stdio.h>

#include "handler.h"

//#define DEBUG_MSG

enum options
{
    CHANGE_COLOR = 'c',
    CHANGE_BRIGHTNESS = 'b',
    HELP = 'h',
    LIST_OPTIONS = 'l',
    QUIT = 'q',
#ifdef DEBUG_MSG
    DEBUG_OPTION = 'd',
#endif
};

static void clearStdin(void)
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

void runUserInterface(hid_device *dev)
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
                    res = handleBrightness(dev);
                    if (res == -1)
                    {
                        (void) fprintf(stderr,
                                       "\33[31m level of brightness must be from 0 to 100 inclusively\33[m\n");
                    }
                    break;
                case CHANGE_COLOR:
                    handleMonocolor(dev);
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
                    (void) fprintf(stderr, "\33[31m check your input\33[m\n");
                    break;
            }
        }
    }
}
