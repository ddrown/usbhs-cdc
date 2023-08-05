This client waits for the pps message over the serial port and then sends it to chrony via a unix socket

Example chrony.conf snippet:

```
refclock SOCK /var/run/chrony/chrony.ttyACM1.sock refid USB offset 0.000068 poll 4
```

The suggested offset of 68us is a measurement against my local stratum 1 ntp servers with hardware timestamps
