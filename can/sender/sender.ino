#include "mcp_can.h"
#include <SPI.h>

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void setup()
{
  delay(5000);  // delay to allow me time to open the serial monitor window to check all is well
  Serial.begin(9600);
  if(CAN.begin(CAN_500KBPS) ==CAN_OK)  //check the Seeeduino CAN-BUS wiki for more details on code
  {
    Serial.print("can init ok!!\r\n");
      for (int i = 0; i < 9; i = i + 1)
      {
        Serial.print(stmp[i], DEC);
      }
  }
  else Serial.print("Can init fail!!\r\n");
}

void loop()
{
  CAN.sendMsgBuf(0x00, 0, 8, stmp);
  delay(1000);  //
}
