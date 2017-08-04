# Current projects:

I'm currently working on a very major cleanup of all the garbage software that the meathead manufacturer has polluted these devices with, with the purpose of making a software set that actually works, fast, reliably, and correctly. The problem I'm facing, however, is that the work that needs to be done is pretty radical. I'd like to build AOSP from source (7.1 would be nice...), but at the same time, I need the unit in my car to actually work, which limits me to fairly small steps.<br />
<br />
In order to deal with this limitation, I really need a second unit to do my more radical work on. This has a cost of $265 Canadian, on Amazon.ca.<br />
<br />
I've also had a few people ask about a donation link so they could "buy me a beer". Its a fair process, I suppose, for people who don't have the technical skills to assist in the actual work to do what they can (but only if they feel like it!) to help out with the project. So to this end, I think that maybe a good solution would be to let people help out in purchasing that second unit I need to do the real work on.<br />
<br />
Amazon offers something they call an "e-gift card". You log in to Amazon, and just below the search bar is a button that says "gift cards". Choose e-gift, select a denomination (you can use the "other amount" field to select a value less than their smallest "suggested" amount, like $5... or bigger than the biggest one :D). For the recipient email address, put in lbdroidman AT gmail DOT com.<br />
<br />
NOW THERE IS ONE CATCH to this, which is that Amazon gift cards are REGION LOCKED. This means that a gift card purchased on Amazon.com, or Amazon.co.uk cannot be redeemed on Amazon.ca. I need to be able to redeem it on Amazon.ca. BUT THE GOOD NEWS is that any Amazon account can be used to log in to ANY region, and it carries in your already set up billing configuration. So just point your browser over to Amazon.ca, log in, and buy me a gift card.<br />
<br />
I'm not asking anyone to pay for my work, but if you are compelled to help out with the project, it would be appreciated very much.<br />
<br />

# Bluetooth Tethering Controller:

BTTether.apk: Used to automatically establish a bluetooth data connection between the car radio and a data source like a cellular phone. Install this on BOTH devices.<br />
*** NOTE: On the car radio, you need to install it into a privileged location, or the crappy software on the car radio will disable it and prevent it from responding to bluetooth state change intents. Copy it into the path /system/priv-app/BTTether/
Use: Your phone and your car radio must be PAIRED with each other first. This can be done either through the crappy car radio interface, OR through the HIDDEN standard android bluetooth settings menu, accessible by pressing the "launch bluetooth settings" button. On the car radio, select your phone from the spinner and enable the setting "Auto Connect PAN". On your PHONE, enable the setting "Auto Bluetooth Tethering" at the bottom of the screen. From here onward, whenever you start your car, a bluetooth PAN connection should automatically be established, providing data access to the phone.<br />
<br />
SOURCE CODE REPOSITORY: https://github.com/lbdroid/BlutoothTethering

