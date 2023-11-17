#pragma once

#include "hidapi.h"

/*! \brief
 * print error info if you need to call hid_error(NULL) and hid_exit()
 */
void hidNullErr();

/*! \brief
 * initialize HIDAPI library and open ite8291 device
 * \return
 * Returns hid_device *dev on success and NULL on error. Call hidNullErr to get the failure reason.
 */
hid_device *initDevice();

/*! \brief
 * Get level of brightness from stdin and send Feature Report to ite8291 to change level of brightness
 * \param dev A device handle returned from initDevice()
 * \return
 * Returns 0 on success and -1 if level of brightness not between 0 and 100 inclusively
 */
int setBrightness(hid_device *dev);

/*! \brief
 * Close a device and finalize HIDAPI library
 * @param dev A device handle returned from initDevice()
 */
void finalizeHidApi(hid_device *dev);
