#pragma once

#include "../lib/hidapi.h"

//#define DEBUG_MSG

/*! \brief
 * Gets users input about new level of brightness and sets it
 * \param dev A device handle returned from initDevice()
 * \return
 * Returns -1 if value not in [0; 100], 0 in success
 */
int handleBrightness(hid_device *dev);

/*! \brief
 * Gets user input about new monocolor for all keymaps and sets it
 * \param dev A device handle returned from initDevice()
 */
void handleMonocolor(hid_device *dev);

#ifdef DEBUG_MSG
/*! \brief
 * Gets user input about custom sequence
 * \param dev A device handle returned from initDevice()
 */
void sendDebug(hid_device *dev);
#endif
