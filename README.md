USB High Speed example for a Serial (CDC) device

Uses the CH32V307 dev board, USB High Speed port is the right USB C labeled "P6"

UART is on pins PA2 (TX) PA3 (RX)

PPS input is on pin PA8

warning: all USB ports on the dev board have their voltage connected together, which might lead to bad things happening if you plug two of its ports into different hubs. It'll also happily backfeed the USB C ports.

This code is originally from https://github.com/openwch/ch32v307/tree/main/EVT/EXAM/USB/USBHS/DEVICE/SimulateCDC, adapted to use a Makefile
