BTTether.apk: Used to automatically establish a bluetooth data connection between the car radio and a data source like a cellular phone. Install this on BOTH devices.
*** NOTE: On the car radio, you need to install it into a privileged location, or the crappy software on the car radio will disable it and prevent it from responding to bluetooth state change intents. Copy it into the path /system/priv-app/BTTether/
Use: Your phone and your car radio must be PAIRED with each other first. This can be done either through the crappy car radio interface, OR through the HIDDEN standard android bluetooth settings menu, accessible by pressing the "launch bluetooth settings" button. On the car radio, select your phone from the spinner and enable the setting "Auto Connect PAN". On your PHONE, enable the setting "Auto Bluetooth Tethering" at the bottom of the screen. From here onward, whenever you start your car, a bluetooth PAN connection should automatically be established, providing data access to the phone.

SOURCE CODE REPOSITORY: https://github.com/lbdroid/BlutoothTethering

