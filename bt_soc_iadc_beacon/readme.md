# Beacon with IADC

Implementation of a low power beacon with the following optimizations:

* Turn of clocking to debug port during EM2
* EM2 RAM retention of last 8k RAM --- note this requires reducing LENGTH of RAM in linker script **this is not performed by this example**
* Low frequency voltage scaling in EM0/1

## IADC operation
<pre>
void init_sampling(float frequency)
</pre>

Once initialized using, IADC is continuously triggered by LETIMER at
the requested frequency (Hz).  Results are transfered to a buffer
(singleBuffer).  Once the LDMA buffer is filled, the same LDMA
descriptor is chain loaded, resulting in next sample over writing
sample at start of buffer.  This can be considered as a circular FIFO.

In order to read data from the FIFO, the /head/ pointer can be
calculated from the LDMA channels XFERCNT (as head moves up through
buffer, XFERCNT decreases.)

<pre>
size_t get_samples(uint16_t *dest, size_t maxlen)
</pre>

Copies up to maxlen samples and returns the number of samples copied.

## Beacon

Each time the device wakes to advertise, before returning to EM2,
app_process_action is called.  Since this function may be called
multiple times per advertising interval, a simple check is made to
prevent the advertisement getting updated more frequently than
necessary.  If at least one advertising interval has passed since
previous setting of the advertising payload, a set of samples are read
from the FIFO (all available samples) and the advertising payload is
updated.  The payload is a Manufacturer Data AdType (id 0xffff) with
the Manufacturer data is structure containing:

* uint16 count : number of samples in set
* uint32 sum   : sum of samples in set
* unit16 max   : maximum sample in set
* uint16 min   : minimum sample in set

It should be noted that since the device wakes up to send the current
advertisement, the data advertised will be from samples during the EM2
duration before the previous advertisement.  This is illustrated
below: The line "sample" indicates individual samples made by IADC.
"Advertised payload" indicates the processed samples contained in the
OTA packet.  "Payload setting" represents the time at which samples
are copied from FIFO and processing into the next advertising payload.

<pre>
sample: 11 12 13 14 15           16 17 18 19 20         21 22 23 24 25 
advertised payload:     [6-10]                  [11-15]                [16-20]
payload setting:                X                        X                      X
</pre>
