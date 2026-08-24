#ifndef _APPLICATION_H
#define _APPLICATION_H

#ifndef FW_VERSION
#define FW_VERSION "vdev"
#endif

// Volume represented by one pulse from the water meter sensor.
#ifndef WATER_METER_LITERS_PER_IMPULSE
#define WATER_METER_LITERS_PER_IMPULSE 1U
#endif

// Publish every pulse immediately while the radio is listening.
#ifndef PUBLISH_USAGE_IMMEDIATELY_WHILE_LISTENING
#define PUBLISH_USAGE_IMMEDIATELY_WHILE_LISTENING 1
#endif

#include <bcl.h>
#include <twr.h>

#endif // _APPLICATION_H
