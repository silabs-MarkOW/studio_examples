# This is a simple implementation of the behavior of U-Blox C209 AOA tag,

It is based of Bluetooth - SoC Empty example project with the following changes:

* Add Extended Advertising component
* Add Periodic advertising component
* Increase maximum number of advertisers to 2
* Decrease maximum number of conections to 1 --- not necessary

This application expects to have a Bootloader - Bluetooth AppLoader
OTA DFU Since it uses a static random addresss for connectable legacy
advertising, this will not work well with EFR Connect.

If calls setting random address are removed, the device address will
be used instead.  Random addresses were used to more closely copy
C209 behavior.

