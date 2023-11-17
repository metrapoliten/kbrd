#include <stdio.h>
#include <string.h>
#include "getInteger.h"
#include "stdlib.h"

#include "hidapi.h"

#define VENDOR_ID   0x048d
#define PRODUCT_ID  0x6006

#define REPORT_LENGTH 9 //Report ID (first byte) + Setup data (8 bytes) (Windows only)

// #define SET_EFFECT      0x08
#define SET_BRIGHTNESS  0x09
// #define SET_COLOR       0x14

void transferReport(hid_device *handle, unsigned char *buf)
{
    int res = hid_send_feature_report(handle, buf, REPORT_LENGTH);
    if (res == -1) {
        printf("%ls\n", hid_error(handle));
        hid_close(handle);
        hid_exit();
    }
}

void buildRequest(unsigned char *buf, unsigned char type, unsigned char control,
                  unsigned char *payload, unsigned char payloadLen)
{
    memset(buf,0x00,REPORT_LENGTH);
    // buf[0] = 0x00    (ReportID) (Windows only)
    buf[1] = type;
    buf[2] = control;
    memcpy(buf + 3, payload, payloadLen);
}

void sendFeatureReport(hid_device *handle, unsigned char type, unsigned char control,
                       unsigned char *payload, unsigned char payloadLen)
{
    unsigned char buf[REPORT_LENGTH];
    buildRequest(buf, type, control, payload, payloadLen);
    transferReport(handle, buf);
}

int setBrightness(hid_device *handle)
{
    unsigned char brightness = getInteger("Enter the brightness value (from 1 to 100 inclusive): ");

    if ((brightness < 0) || (brightness > 100)) {
        perror("Brightness must be between 0 and 100 inclusively\n");
        return -1;
    }
    sendFeatureReport(handle, SET_BRIGHTNESS, 0x02, &brightness, 1);
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

void printNullErr()
{
    printf("%ls\n", hid_error(NULL));
    hid_exit();
}

void *init()
{
    int res;
    hid_device *handle;

    res = hid_init();

    if (res == -1) {
        printNullErr();
        return NULL;
    }

    handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);

    if (!handle) {
        printNullErr();
        return NULL;
    }
    return handle;
}

void finalizeHidApi(hid_device *handle)
{
    int res;
    hid_close(handle);
    res = hid_exit();
    if (res == -1){
        perror("HIDAPI couldn't exit");
        exit(-1);
    }
}

int main(void)
{
    int userInput;

    hid_device *handle = init();
    if (!handle)
    {
        return -1;
    }

    puts("Available options:\n1. Change brightness.");
    userInput = getInteger("Choose option:");

    switch (userInput) {
        case 1:
            setBrightness(handle);
            break;
#if 0
        case 2:
            setColor();
            break;
        case 3:
            setEffect();
#endif
        default:
            perror("No such option.");
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

    finalizeHidApi(handle);
    return 0;
}