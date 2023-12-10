#pragma once

#include "hidapi.h"

int sendBrightness(hid_device *dev);

void sendMonocolor(hid_device *dev);

void sendDebug(hid_device *dev);
