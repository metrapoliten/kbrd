#pragma once

#include "hidapi.h"

/*! *\brief
 * Runs user command-line interface which helps to change keyboards mods
 * \param dev
 */
int userInterface(hid_device *dev);
