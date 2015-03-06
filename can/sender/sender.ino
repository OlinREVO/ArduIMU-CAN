//#include "mcp_can.h"
//#include <SPI.h>
//
//unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
//MCP_CAN CAN(10);
//
//void setup()
//{
//  delay(5000);  // delay to allow me time to open the serial monitor window to check all is well
//  Serial.begin(9600);
//
//START_INIT:
//
//  if(CAN.begin(CAN_500KBPS) == CAN_OK)  //check the Seeeduino CAN-BUS wiki for more details on code
//  {
//    Serial.print("can init ok!!\r\n");
//      for (int i = 0; i < 9; i = i + 1)
//      {
//        Serial.print(stmp[i], DEC);
//      }
//  }
//  else{ 
//  Serial.print("Can init fail!!\r\n");
//  delay(100);
//  goto START_INIT;
//  }
//}
//void loop()
//{
//  CAN.sendMsgBuf(0x00, 0, 8, stmp);
//  Serial.print("Sending SPI Message");
//  delay(1000);  //
// }

// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN(16);                                      // Set CS to pin 10

void setup()
{
    Serial.begin(9600);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("init fail");
        delay(100);
        goto START_INIT;
    }
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
void loop()
{
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x00, 0, 8, stmp);
    delay(100);                       // send data per 100ms
}
