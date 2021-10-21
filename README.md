# SPISRR - SPI Status Register Read

## Function

A simple utility to show status register of spidev device.

## Usage

```
    spirr [device]
```

* `device`: a device to examine. If omitted, `/dev/spidev0.0` is used.

## Build

```
    mkdir build
    cd build
    meson ..
    ninja
    sudo ninja install
```
