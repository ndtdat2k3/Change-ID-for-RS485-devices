# Change-ID-for-RS485-devices
To change the ID for RS-485 devices, you need to:
- Check the user manual of the device.
- Look for the register address that is named "device address".
- Change the ID_Register in #define
- Change the OLD_SLAVE_ID (current ID) and NEW_SLAVE_ID (desired ID)
- Run the code
  
After successfully changing the ID, you should:
-  Unplug the source of the RS-485 device and the code loading cable.
-  Plug again, and you are ready to use the new ID slave.
