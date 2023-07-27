#include "Bluefruit.h"

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

//    READ_BLE_BUFSIZE            Size of the read buffer for incoming packets
#define READ_BLE_BUFSIZE                    (20)

char bleData[BLE_BUFSIZE+1]{};

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

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/**************************************************************************/
/*!
    @brief  callback for RX data
*/
/**************************************************************************/
void bleUartRxCallback(char data[], uint16_t len)
{

  if (len >= BLE_BUFSIZE) {
    Serial.println( F("BLE MSG TOO LARGE!") );
    return;
  }

  memcpy(bleData, data, len);

  bleData[len] = 0; // null term
  return;

}

/**************************************************************************/
/*!
    @brief  callback for connection established
*/
/**************************************************************************/
void bleConnectedCallback(void)
{
  Serial.println( F("BLE CONNECTED!" ) );
  
}

void setupBluefruit(Adafruit_BluefruitLE_SPI *ble)
{
  memset(bleData, 0, BLE_BUFSIZE);

  Serial.println(F("-------------------"));
  Serial.println(F("Bluefruit"));

  Serial.print(F("Init: "));

  if ( !ble->begin(VERBOSE_MODE) )
  {
    error(F("BLE MISSING"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE ) {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("reset: "));
    if ( ! ble->factoryReset() ){
      error(F("failed"));
    }
  }

  ble->echo(false);
  ble->info();
  ble->verbose(false);
  
  ble->setBleUartRxCallback(bleUartRxCallback);
  ble->setConnectCallback(bleConnectedCallback);

  // LED Activity command is only supported from 0.6.6
  if ( ble->isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    ble->sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  ble->setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("COMPLETE"));
  Serial.println(F("-------------------"));

}
