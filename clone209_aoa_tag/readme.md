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

The extended advertiser address is randomized every 10 minutes.

Every 30 seconds the periodic advertisement payload is updated.  The
C209 example I am working with incorrectly implements the Manufacturer
Specific Data.  It formats it as
* [length][0xff][data...]
The correct format is
* [length][0xff][uuid16][data...]
Where uuid16 is the 16-bit UUID of the manufacturer.  For this example
I have corrected this and use Silicon Labs UUID 0x02FF.
