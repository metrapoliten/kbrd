#include <stdio.h>

#include "getInteger.h"
#include "ite8291.h"

int run(hid_device *dev)
{
    int userInput;

    puts("Available options:\n"
         "1. Change brightness\n"
         "2. Change color\n");
    userInput = getInteger("Choose option:");

    switch (userInput)
    {
        case 1:
            setBrightness(dev);
            break;
#if 0
            case 2:
            setColor();
            break;
        case 3:
            setEffect();
#endif
        default:
            puts("No such option");
            break;
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

}