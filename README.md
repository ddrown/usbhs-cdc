USB High Speed example for a Serial (CDC) device

Uses the CH32V307 dev board, USB High Speed port is the right USB C labeled "P6"

UART is on pins PA2 (TX) PA3 (RX)

warning: all USB ports on the dev board have their voltage connected together, which might lead to bad things happening if you plug two of its ports into different hubs. It'll also happily backfeed the USB C ports.
