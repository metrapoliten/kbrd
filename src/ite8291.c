#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getInteger.h"
#include "hidapi.h"

#define VENDOR_ID   0x048d
#define PRODUCT_ID  0x6006

#define REPORT_LENGTH 9 //Report ID (first byte) + Setup data (8 bytes) (Windows only)

/* #define SET_EFFECT      0x08 */
#define SET_BRIGHTNESS  0x09
/* #define SET_COLOR       0x14 */

static void sendFeatureReport(hid_device *dev, unsigned char type, unsigned char control,
                              unsigned char *payload, unsigned char payloadLen)
{
    unsigned char buf[REPORT_LENGTH];
    memset(buf,0x00,REPORT_LENGTH);
    // buf[0] = 0x00    (ReportID) (Windows only)
    buf[1] = type;
    buf[2] = control;
    memcpy(buf + 3, payload, payloadLen);

    int res = hid_send_feature_report(dev, buf, REPORT_LENGTH);
    if (res == -1) {
        printf("%ls\n", hid_error(dev));
        hid_close(dev);
        hid_exit();
    }
}

int setBrightness(hid_device *dev)
{
    unsigned char brightness = getInteger("Enter the brightness value (from 0 to 100 inclusive):");

    if ((brightness < 0) || (brightness > 100)) {
        puts("Brightness must be between 0 and 100 inclusively\n");
        return -1;
    }
    sendFeatureReport(dev, SET_BRIGHTNESS, 0x02, &brightness, 1);
    return 0;
}

#if 0
void setColor(unsigned char standardColor)
{

}

void getFeatureReport(unsigned char *buf)
{

}
#endif

void hidNullErr()
{
    printf("%ls\n", hid_error(NULL));
    hid_exit();
}

hid_device *initDevice()
{
    int res;
    hid_device *dev;

    res = hid_init();

    if (res == -1) {
        return NULL;
    }

    dev = hid_open(VENDOR_ID, PRODUCT_ID, NULL);

    if (dev == NULL) {
        return NULL;
    }
    return dev;
}

void finalizeHidApi(hid_device *dev)
{
    int res;
    hid_close(dev);
    res = hid_exit();
    if (res == -1){
        puts("HIDAPI couldn't exit");
        exit(-1);
    }
}