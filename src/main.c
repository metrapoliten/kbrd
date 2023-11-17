#include "ite8291.h"
#include "run.h"

int main(void)
{
    hid_device *dev = initDevice();
    if (dev == NULL)
    {
        hidNullErr();
        return -1;
    }
    run(dev);
    finalizeHidApi(dev);
    return 0;
}