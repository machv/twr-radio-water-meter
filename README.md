# Water meter firmware for HARDWARIO Core Module

This firmware uses a Sensus HRI-A4 pulse sensor connected to Sensor Module
channel A to measure and report water usage.

## Wiring

Connect the HRI-A4's two reed-switch leads to the HARDWARIO Sensor Module:

| HRI-A4 lead | Sensor Module terminal |
| ----------- | ----- |
| White (I1)  | `A`   |
| Brown (GND) | `GND` |


### Sensor Module R1.1 - 5 pin connector

| A              | GND             | VCC       | GND/C | B    |
|----------------|-----------------|-----------|-------|------|
| HRI White (I1) | HRI Brown (GND) + 1-wire (GND) black | 1Wire (VCC) red |   -   | 1-wire (DATA) yellow/white |


The reed switch is polarity independent, so the two leads can be interchanged.
Do not connect the sensor to `VCC`; it is a passive dry contact and does not
need a power supply. The firmware enables channel A's internal pull-up. Closing
the contact therefore pulls channel A to ground and records one falling-edge
impulse.

Disconnect power before changing the wiring. If the cable or supplied
installation sheet identifies different electrical connections, follow the
manufacturer's instructions for that specific HRI variant.

The SDK updates the pulse counter immediately on each falling edge, and the
firmware flashes the LED for every detected pulse.

By default, one impulse represents one liter. Change the compile-time definition
in `src/application.h` when the meter has a different whole-liter impulse
weight:

```c
#define WATER_METER_LITERS_PER_IMPULSE 1U
```

## MQTT topics

| Topic | Unit | Payload type | Description |
| --- | --- | --- | --- |
| `usage/-/total` | m3 | Native float | Total water usage |
| `usage/-/relative` | m3 | Native float | Usage since the preceding report |
| `usage/-/total-liters` | l | Unsigned integer | Total water usage |
| `usage/-/relative-liters` | l | Unsigned integer | Usage since the preceding report |

The stock HARDWARIO gateway serializes generic native floats with two decimal
places. Use the integer liter topics when exact whole-liter values are required.

## Reporting schedule

- Every minute (`USAGE_REPORT_INTERVAL`), usage is published only when the
  counter changed since the preceding report.
- Every 30 minutes (`SCHEDULED_REPORT_INTERVAL`), usage is published even when
  the counter did not change.
- If both schedules run at the same time, only one report is published.
- Relative usage is calculated from the last periodic or troubleshooting
  report.

## Setting the current total

The node listens for configuration for one minute after boot and after each
button press. During this period the LED remains on and
`core/-/listening-timeout` reports the timeout in seconds.

Send the current meter value in m3 as a numeric payload to:

```text
usage/-/total/set
```

The legacy `usage/-/total/float` topic is also supported. The value is converted
to the nearest pulse count, stored in the SDK pulse counter, and the new total
is published immediately. This also resets the relative-report baseline.

When `PUBLISH_USAGE_IMMEDIATELY_WHILE_LISTENING` is enabled, per-pulse
troubleshooting reports begin only after the first valid total is received in
the current listening session. This prevents an unconfigured counter value from
being published. Pressing the button starts a new listening session and disables
immediate reports until another valid total is received.

## Compile-time options

Configure these defaults in `src/application.h`:

| Definition | Default | Description |
| --- | --- | --- |
| `WATER_METER_LITERS_PER_IMPULSE` | `1U` | Whole liters represented by one pulse |
| `PUBLISH_USAGE_IMMEDIATELY_WHILE_LISTENING` | `1` | Publish every pulse after configuration while listening |
| `ENABLE_CLIMATE_MODULE` | `1` | Enable the optional Climate Module |

## Development

### Initialize

```bash
git submodule update --init sdk
```

### Build

```bash
cmake -B obj/debug . -G Ninja \
  -DTYPE=debug \
  -DCMAKE_TOOLCHAIN_FILE=sdk/toolchain/toolchain.cmake
ninja -C obj/debug
```

### Upgrade SDK version

```bash
git submodule update --remote --merge sdk
```
