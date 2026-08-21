#ifndef _APPLICATION_H
#define _APPLICATION_H

#ifndef FW_VERSION
#define FW_VERSION "vdev"
#endif

// Volume represented by one pulse from the water meter sensor.
#ifndef WATER_METER_LITERS_PER_IMPULSE
#define WATER_METER_LITERS_PER_IMPULSE 1.0f
#endif

#include <bcl.h>
#include <twr.h>

#endif // _APPLICATION_H
