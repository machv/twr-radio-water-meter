# Water meter firmware for HARDWARIO Core Module

This firmware uses a Sensus HRI-A4 pulse sensor connected to Sensor Module
channel A to measure and report water usage.

## Wiring

Connect the HRI-A4's two reed-switch leads to the HARDWARIO Sensor Module:

| HRI-A4 lead | Sensor Module terminal |
| ----------- | --- |
| White (I1)  | `A` |
| Brown (GND) | `GND` |


### Sensor Module R1.1 - 5 pin connector

| A              | GND             | VCC       | GND/C | B    |
|----------------|-----------------|-----------|-------|------|
| HRI White (I1) | HRI Brown (GND) | 1Wire VCC |   -   | 1-wire DATA |


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
#define WATER_METER_LITERS_PER_IMPULSE 1U
```

Totals and relative usage are reported in both cubic meters and liters:

- `usage/-/total` - total water usage in m3 as a native float
- `usage/-/relative` - water used since the preceding report in m3 as a native float
- `usage/-/total-liters` - total water usage in liters as an integer
- `usage/-/relative-liters` - water used since the preceding report in liters as an integer

The firmware blinks the LED when an impulse is detected. It checks for changed
usage every minute and reports it when needed, plus sends a regular report every
30 minutes even without a change. While listening after boot or a button press,
each pulse is reported immediately by default for troubleshooting. Set
`PUBLISH_USAGE_IMMEDIATELY_WHILE_LISTENING` to `0` to disable this behavior.
Configure the
initial meter state in m3 using a numeric value on `usage/-/total/set` (the
legacy `usage/-/total/float` topic is also supported). The configured m3 value
is converted to the corresponding impulse count.

## Development

### Init

```bash
git submodule update --init sdk
```

### Upgrade SDK version

```bash
git submodule update --remote --merge sdk
```
