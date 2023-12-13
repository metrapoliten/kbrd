#pragma once

#include "../lib/hidapi.h"

/*! *\brief
 * Runs user command-line interface which helps to change keyboards mods
 * \param dev
 */
int runUserInterface(hid_device *dev);
