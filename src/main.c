#include <stdio.h> // printf
#include <string.h>

#include "hidapi.h"

#define MAX_STR 255

#define VENDOR_ID   0x048d
#define PRODUCT_ID  0x6006

const char *hid_bus_name(hid_bus_type bus_type) {
    static const char *const HidBusTypeName[] = {
            "Unknown",
            "USB",
            "Bluetooth",
            "I2C",
            "SPI",
    };

    if ((int)bus_type < 0)
        bus_type = HID_API_BUS_UNKNOWN;
    if ((int)bus_type >= (int)(sizeof(HidBusTypeName) / sizeof(HidBusTypeName[0])))
        bus_type = HID_API_BUS_UNKNOWN;

    return HidBusTypeName[bus_type];
}

void print_device(struct hid_device_info *cur_dev) {
    printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
    printf("\n");
    printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
    printf("  Product:      %ls\n", cur_dev->product_string);
    printf("  Release:      %hx\n", cur_dev->release_number);
    printf("  Interface:    %d\n",  cur_dev->interface_number);
    printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
    printf("  Bus type: %d (%s)\n", cur_dev->bus_type, hid_bus_name(cur_dev->bus_type));
    printf("\n");
}

void print_hid_report_descriptor_from_device(hid_device *device) {
    unsigned char descriptor[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
    int res = 0;

    printf("  Report Descriptor: ");
    res = hid_get_report_descriptor(device, descriptor, sizeof(descriptor));
    if (res < 0) {
        printf("error getting: %ls", hid_error(device));
    }
    else {
        printf("(%d bytes)", res);
    }
    for (int i = 0; i < res; i++) {
        if (i % 10 == 0) {
            printf("\n");
        }
        printf("0x%02x, ", descriptor[i]);
    }
    printf("\n");
}

void print_hid_report_descriptor_from_path(const char *path) {
    hid_device *device = hid_open_path(path);
    if (device) {
        print_hid_report_descriptor_from_device(device);
        hid_close(device);
    }
    else {
        printf("  Report Descriptor: Unable to open device by path\n");
    }
}

void print_devices(struct hid_device_info *cur_dev) {
    for (; cur_dev; cur_dev = cur_dev->next) {
        print_device(cur_dev);
    }
}

void print_devices_with_descriptor(struct hid_device_info *cur_dev) {
    for (; cur_dev; cur_dev = cur_dev->next) {
        print_device(cur_dev);
        print_hid_report_descriptor_from_path(cur_dev->path);
    }
}

int main(void)
{
    int res;
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    int i;

    res = hid_init();

    if (res == -1) {
        printf("%ls\n", hid_error(NULL));
        hid_exit();
        return 1;
    }

    handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (!handle) {
        printf("%ls\n", hid_error(NULL));
        hid_exit();
        return 1;
    }
    unsigned char buf[9];
    memset(buf,0x00,sizeof(buf));
    // first value for Report ID = 0x00 (only for Windows "feature")
                    //first mode (on, add set-gs) || transfer colour              // set brightness
    buf[1] = 0x14;  //0x08 - init mode            ||  0x14 - init mode            // 0x09 - init mode
    buf[2] = 0x00;  //0x02 - ?, 0x01 - turn off   ||  no matter. 0x00 - 0xff work // seems like only 0x03 work
    buf[3] = 0x01;  //"effect" in use??         // seems like only 0x01           // brightness
    buf[4] = 0xff;  //speed                     || colour
    buf[5] = 0xff;  //brightness                || colour
    buf[6] = 0x00;  //colour from struct        || colour
    buf[7] = 0x00;   // ??
    buf[8] = 0x1;   // save: 0x00 - no, 0x01 - yes

//    res = hid_write(handle, buf, 8 + 1);
//    if (res == -1) {
//        printf("%ls\n", hid_error(handle));
//        hid_close(handle);
//        hid_exit();
//        return 1;
//    }

    res = hid_send_feature_report(handle, buf, 9);
    if (res == -1) {
        printf("%ls\n", hid_error(handle));
        hid_close(handle);
        hid_exit();
        return 1;
    }

    hid_close(handle);

    // Finalize the hidapi library
    res = hid_exit();

    return 0;
}