# Community Support - Example of handling AppLoader OTA DFU from a (previously) bonded device

Original Community thread: [Using Apploader after bonding](https://community.silabs.com/s/question/0D5Vm0000057hOkKAI/using-apploader-after-bonding)

This application implements a protected OTA function.  The OTA Control
chracteristic is left unprotected, but attempts to activate OTA by
writing will be ignored unless the device attempting to initiate OTA meets the following conditions:
* It has previously been bonded with the device.  When wishing to perform OTA DFU using EFR Connect, the device should first forget the device, then connect.
* After connecting, the push button is pressed.

The first condition is established by recognizing the resolvable device address of the mobile device.  A malicious party could spoof this condition by using an address which the trusted mobile device has previously used.
The second condition requires that  only trusted parties have access to the push button.

If the two conditions above are met, the device deletes the trusted mobiles bonding information, then rebooots into AppLoader.  Since the mobile has already deleted its bonding data, this operation should work normally.  Once the OTA is complete, the next time the device connects it will need to be rebonded.  Since the bonding data was deleted before OTA, the device will no longer remember the mobil and so pressing the button will establish a new bonding relationship between the two devices.

This project has be tested on BRD4311A.  It should be compatible with
BGM220 and EFR32BG22 devices.

The application logs to VCOM.  If this is not compatible with a custom board, simply removing the Application / Utility / Log component and the vcom instance of the IO Stream USART component should result in all logging calls being ignored (log.h).
