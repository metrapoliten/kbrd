#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hidapi.h"

//Report ID (first byte) + Setup data (8 bytes) (Windows only)
#define REPORT_LENGTH 9

enum deviceInfo
{
    VENDOR_ID = 0x048d,
    PRODUCT_ID = 0x6006
};

enum command
{
    SET_EFFECT = 0x08,
    SET_BRIGHTNESS = 0x09,
    SET_COLOR = 0x14
};

/* struct of feature report:
 * [0]      obligatory byte for working with windows (no need in linux)
 * [1]      command of report (see 'enum command')
 * [2]      mode of command
 * [3-8]    payload info
*/
// make not static if you want to use debug
static void sendFeatureReport(hid_device *dev, unsigned char command, unsigned char control,
                       unsigned char *payload, unsigned payloadLen)
{
    unsigned char buf[REPORT_LENGTH];
    memset(buf, 0x00, REPORT_LENGTH);
    buf[1] = command;
    buf[2] = control;
    memcpy(buf + 3, payload, payloadLen);

    int res = hid_send_feature_report(dev, buf, REPORT_LENGTH);
    if (res == -1)
    {
        printf("%ls\n", hid_error(dev));
        hid_close(dev);
        hid_exit();
    }
}

void setBrightness(hid_device *dev, unsigned char brightness)
{
    sendFeatureReport(dev, SET_BRIGHTNESS, 0x02, &brightness, sizeof(brightness));
}

void setColor(hid_device *dev, unsigned char control, unsigned char row,
              unsigned char red, unsigned char green, unsigned char blue)
{
    unsigned payloadLen = 6;
    unsigned char payload[] =
            {row, red, green, blue, 0x00, 0x00};
    sendFeatureReport(dev, SET_COLOR, control, payload, payloadLen);
    unsigned char savePayload[] =
            {0x01, 0x0a, 0x64, 0x08, 0x00, 0x01};   //report to save changes in chip;
    sendFeatureReport(dev, SET_EFFECT, 0x02, savePayload, payloadLen);
}

void hidNullErr(void)
{
    printf("%ls\n", hid_error(NULL));
    hid_exit();
}

hid_device *initDevice(void)
{
    int res;
    hid_device *dev;

    res = hid_init();

    if (res == -1)
    {
        return NULL;
    }

    dev = hid_open(VENDOR_ID, PRODUCT_ID, NULL);

    if (dev == NULL)
    {
        return NULL;
    }
    return dev;
}

void finalizeHidApi(hid_device *dev)
{
    int res;
    hid_close(dev);
    res = hid_exit();
    if (res == -1)
    {
        puts("HIDAPI couldn't exit");
        exit(-1);
    }
}
