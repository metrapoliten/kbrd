#include "ite8291.h"
#include "getInteger.h"
#include <stdlib.h>
#include <stdio.h>

int sendBrightness(hid_device *dev)
{
    unsigned char brightness = getInteger("value [0, 100]: ");
    if (brightness > 100)
    {
        return -1;
    }
    setBrightness(dev, brightness);
    return 0;
}

void sendMonocolor(hid_device *dev)
{
    char colorBuf[14];
    (void) fputs("[red green blue]: ", stdout);
    (void) fgets(colorBuf, 14, stdin);
    char *pEnd;
    unsigned char red = strtol(colorBuf, &pEnd, 10);
    unsigned char green = strtol(pEnd, &pEnd, 10);
    unsigned char blue = strtol(pEnd, NULL, 10);
    setColor(dev, 0x01, 0x01, red, green, blue);
}

void sendDebug(hid_device *dev)
{
    unsigned char payload[8];
    char inputBuf[32];
    (void) fgets(inputBuf, 32, stdin);
    char *pEnd;
    for (int i = 0; i < 8; ++i)
    {
        payload[i] = (char) strtol(inputBuf, &pEnd, 16);
    }
    sendFeatureReport(dev, payload[0], payload[1], payload + 2, 5);
}
