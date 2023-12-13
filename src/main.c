#include "ite8291.h"
#include "userInterface.h"

int main(void)
{
    hid_device *dev = initDevice();
    if (dev == NULL)
    {
        hidNullErr();
        return -1;
    }
    runUserInterface(dev);
    finalizeHidApi(dev);
    return 0;
}
