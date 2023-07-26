#include "Bluefruit.h"

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

//    READ_BUFSIZE            Size of the read buffer for incoming packets
#define READ_BUFSIZE                    (20)

/**************************************************************************/
/*!
    @brief  Casts the four bytes at the specified address to a float
*/
/**************************************************************************/
float parsefloat(char* buffer) 
{
  float f;
  memcpy(&f, buffer, 4);
  return f;
}

/**************************************************************************/
/*! 
    @brief  Prints a hexadecimal value in plain characters
    @param  data      Pointer to the byte data
    @param  numBytes  Data length in bytes
*/
/**************************************************************************/
void printHex(char* data, const uint32_t numBytes)
{
  if (!numBytes) return;
  uint32_t szPos;
  for (szPos=0; szPos < numBytes; szPos++) 
  {
    Serial.print(F("0x"));
    // Append leading 0 for small values
    if (data[szPos] <= 0xF)
    {
      Serial.print(F("0"));
      Serial.print(data[szPos] & 0xf, HEX);
    }
    else
    {
      Serial.print(data[szPos] & 0xff, HEX);
    }
    // Add a trailing space if appropriate
    if ((numBytes > 1) && (szPos != numBytes - 1))
    {
      Serial.print(F(" "));
    }
  }
  Serial.println();
}

// no idea why we need this
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/**************************************************************************/
/*!
    @brief  for messages not beginning with '!'
*/
/**************************************************************************/
void handleMessage(char* data, const uint32_t len) {
  Serial.println((char*) data);
  Serial.print("len: ");
  Serial.println(len);
  if (!strncmp((char*) data, "touch", len-1)) { // need to subtract one to ignore line ending
    Serial.println(F("ENABLING TOUCH"));
  }
}

/**************************************************************************/
/*!
    @brief  for messages beginning with '!'
*/
/**************************************************************************/
void handleControl(char* packetbuffer) {
  // Color
  if (packetbuffer[1] == 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    Serial.print(F("RGB #: ")); 
    Serial.print(F("  red:"));
    Serial.print(red);
    Serial.print(F(" green:"));
    Serial.print(green);
    Serial.print(F(" blue:"));
    Serial.println(blue);
    return;
  }

  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    Serial.print(F("Button ")); Serial.print(buttnum);
    if (pressed) {
      Serial.println(F(" pressed"));
    } else {
      Serial.println(F(" released"));
    }
    return;
  }

  // Accelerometer
  if (packetbuffer[1] == 'A') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    Serial.print(F("Accel\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
    return;
  }

  // Magnetometer
  if (packetbuffer[1] == 'M') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    Serial.print(F("Mag\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
    return;
  }

  // Gyroscope
  if (packetbuffer[1] == 'G') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    Serial.print(F("Gyro\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
    return;
  }

  // Quaternions
  if (packetbuffer[1] == 'Q') {
    float x, y, z, w;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    w = parsefloat(packetbuffer+14);
    Serial.print(F("Quat\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.print('\t');
    Serial.print(w); Serial.println();
    return;
  }

  Serial.println(F("Unrecognized Command"));
}

/**************************************************************************/
/*!
    @brief  callback for RX data
*/
/**************************************************************************/
void bleUartRX(char data[], uint16_t len)
{
  Serial.print( F("[BLE]" ) );
  Serial.write(data, len);
  Serial.println();

  if (len && data[0] != '!') {
    handleMessage(data, len);

    return;
  }

  handleControl(data);
}

void setupBluefruit(Adafruit_BluefruitLE_SPI *ble)
{
  Serial.println(F("-----------------------------------------"));
  Serial.println(F("Bluefruit"));

  Serial.print(F("Init: "));

  if ( !ble->begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("reset: "));
    if ( ! ble->factoryReset() ){
      error(F("failed"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble->echo(false);

  Serial.println(F("Requesting info:"));
  /* Print Bluefruit information */
  ble->info();

  ble->verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble->isConnected()) {
      delay(500);
  }

  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble->isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble->sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble->setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));

  ble->setBleUartRxCallback(bleUartRX);

}
