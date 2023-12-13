#pragma once

#include "hidapi.h"

//#define DEBUG_MSG

/*! \brief
 * print error info if you need to call hid_error(NULL) and hid_exit()
 */
void hidNullErr(void);

/*! \brief
 * initialize HIDAPI library and open ite8291 device
 * \return
 * Returns hid_device *dev on success and NULL on error. Call hidNullErr to get the failure reason.
 */
hid_device *initDevice(void);

/*! \brief
 * Get level of brightness from stdin and send Feature Report to ite8291 to change level of brightness
 * \param dev A device handle returned from initDevice()
 * \param brightness Level of brightness [0; 100]
 * \return
 * Returns 0 on success and -1 if level of brightness not between 0 and 100 inclusively
 */
void setBrightness(hid_device *dev, unsigned char brightness);

/*! \brief
 * Close a device and finalize HIDAPI library
 * \param dev A device handle returned from initDevice()
 */
void finalizeHidApi(hid_device *dev);

/*! \brief
 * Sets new keyboard color (RGB)
 * \param dev A device handle returned from initDevice()
 * \param control Control bit of sequence
 * \param row Row of keyboard
 * \param red Level of red [0; 255]
 * \param green Level of green [0; 255]
 * \param blue Level of blue [0; 255]
 */
void setColor(hid_device *dev, unsigned char control, unsigned char row,
              unsigned char red, unsigned char green, unsigned char blue);

#ifdef DEBUG_MSG
void sendFeatureReport(hid_device *dev, unsigned char command, unsigned char control,
                       unsigned char *payload, unsigned payloadLen)
#endif
