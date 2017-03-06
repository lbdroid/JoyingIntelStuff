/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/*
  This example shows how to send HID Consumer Control Keys,
  ncluding the following control key definitions:

  System Control (works on most systems: Windows/OS X/Android/iOS)
    - Sound Mute
    - Brightness Increase, decrease
  Media Control (works on most systems)
    - PlayPause
    - MediaNext
  Application Launchers (works mainly on Windows 8/10)
    - EmailReader
    - Calculator
  Browser Specific (Firefox, file explorer: mainly on Windows 8/10)
    - Back
    - Forward
    - Refresh
    - Search
*/

#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined(ARDUINO_ARCH_SAMD)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"


/*=========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         0
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
/*=========================================================================*/


// Create the bluefruit object, either software serial...uncomment these lines
/*
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
*/

/* ...or hardware serial, which does not need the RTS/CTS pins. Uncomment this line */
// Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/* ...software SPI, using SCK/MOSI/MISO user-defined SPI pins and then user selected CS/IRQ/RST */
//Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_SCK, BLUEFRUIT_SPI_MISO,
//                             BLUEFRUIT_SPI_MOSI, BLUEFRUIT_SPI_CS,
//                             BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

int buttonsAVal[4] = {0, 100, 550, 900};
int buttonsA[4] = {0, 0, 0, 0};
int buttonsANum = 4;

int buttonsBVal[6] = {0, 100, 550, 650, 750, 900};
int buttonsB[6] = {0, 0, 0, 0, 0, 0};
int buttonsBNum = 6;

int buttonThresh = 50;

int buttonLongPress = 40;

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  while (!Serial);  // Required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit HID Control Key Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Factory reset failed!"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  // This demo only works with firmware 0.6.6 and higher!
  // Request the Bluefruit firmware rev and check if it is valid
  if ( !ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    error(F("This sketch requires firmware version " MINIMUM_FIRMWARE_VERSION " or higher!"));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Services (including Control Key): "));
  if (! ble.sendCommandCheckOK(F( "AT+BLEHIDEN=On"  ))) {
    error(F("Failed to enable HID (firmware >=0.6.6?)"));
  }

  /* Adding or removing services requires a reset */
  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }

  Serial.println();
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
  int i, j, a, b;
  a = analogRead(A1);
  b = analogRead(A2);
  if (a > 1000){
    // buttons A are all released
    //Serial.println("Buttons A Released");
    for (i=0; i<buttonsANum; i++){
      //Serial.print("@");
      //Serial.print(i);
      //Serial.print(":");
      //Serial.println(buttonsA[i]);
      if (buttonsA[i] > buttonLongPress){
        // Channel-A, Button-i was just released, long-press
        sendKey(0, i, 1);
        buttonsA[i] = 0;
      } else if (buttonsA[i] > 0){
        // Channel-A, Button-i was just released, short-press
        sendKey(0, i, 0);
        buttonsA[i] = 0;
      }
    }
  } else {
    for (i=0; i<buttonsANum; i++){
      if (a > buttonsAVal[i] - buttonThresh && a < buttonsAVal[i] + buttonThresh){
        // button is pressed
        Serial.print("Pressed Button A. Value: ");
        Serial.print(a);
        Serial.print(", incrementing counter: ");
        Serial.print(i);
        Serial.print(", currently: ");
        Serial.println(buttonsA[i]);
        buttonsA[i]++;
        for (j=0; j<buttonsANum; j++) if (j!=i) buttonsA[j]=0;
      }
    }
  }

  if (b > 1000){
    Serial.println("Buttons B Released");
    // buttons are all released
    for (i=0; i<buttonsBNum; i++){
      if (buttonsB[i] > buttonLongPress){
        // Channel-B, Button-i was just released, long-press
        sendKey(1, i, 1);
        buttonsB[i] = 0;
      } else if (buttonsB[i] > 0){
        // Channel-B, Button-i was just released, short-press
        sendKey(1, i, 0);
        buttonsB[i] = 0;
      }
    }
  } else {
    for (i=0; i<buttonsBNum; i++){
      if (b > buttonsBVal[i] - buttonThresh && b < buttonsBVal[i] + buttonThresh){
        // button is pressed
        Serial.print("Pressed Button B. Value: ");
        Serial.print(b);
        Serial.print(", incrementing counter: ");
        Serial.print(i);
        Serial.print(", currently: ");
        Serial.println(buttonsB[i]);
        buttonsB[i]++;
        for (j=0; j<buttonsBNum; j++) if (j!=i) buttonsB[j]=0;
      }
    }
  }

  delay(10);
}

void sendKey(int line, int key, int longpress){
  Serial.println("Sending key");

  if(longpress==0/*line==0*/){
    ble.print("AT+BleHidControlKey=");
    ble.println("VOLUME+");
    //ble.println("AT+BLEKEYBOARDCODE=00-00-04-00-00-00-00"); // press "a" button
  } else {
    ble.print("AT+BleHidControlKey=");
    ble.println("VOLUME-");
    //ble.println("AT+BLEKEYBOARDCODE=00-00"); // release
  }
}

