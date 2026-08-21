# Water meter firmware for HARDWARIO Core Module

This firmware uses a Sensus HRI-A4 pulse sensor connected to Sensor Module
channel A to measure and report water usage.

## Wiring

Connect the HRI-A4's two reed-switch leads to the HARDWARIO Sensor Module:

| HRI-A4 lead | Sensor Module terminal |
| --- | --- |
| White (I1)  | `A` |
| Brown (GND) | `GND` |

The reed switch is polarity independent, so the two leads can be interchanged.
Do not connect the sensor to `VCC`; it is a passive dry contact and does not
need a power supply. The firmware enables channel A's internal pull-up. Closing
the contact therefore pulls channel A to ground and records one falling-edge
impulse.

Disconnect power before changing the wiring. If the cable or supplied
installation sheet identifies different electrical connections, follow the
manufacturer's instructions for that specific HRI variant.

The pulse input uses the internal pull-up and counts falling edges. By default,
one impulse represents one liter. Change the compile-time definition in
`src/application.h` when the meter has a different impulse weight:

```c
#define WATER_METER_LITERS_PER_IMPULSE 1.0f
```

Reported totals and relative usage are always in cubic meters:

- `usage/-/total` - total water usage in m3
- `usage/-/relative` - water used since the preceding report in m3

The firmware reports when an impulse is detected. It listens for total-usage
configuration for one minute after boot or a button press. Configure the
initial meter state in m3 using either a floating point value on
`usage/-/total/float` or an integer value on `usage/-/total/set`. The configured
m3 value is converted to the corresponding impulse count.

## Development

### Init

```bash
git submodule update --init sdk
```

### Upgrade SDK version

```bash
git submodule update --remote --merge sdk
```
