/****************************************************************************************  
**  This is example LINX firmware for use with the Arduino Uno with the serial 
**  interface enabled.
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
**  BSD2 License.
****************************************************************************************/

//Include All Peripheral Libraries Used By LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>
#include <dht.h>

//Include Device Specific Header From Sketch>>Import Library (In This Case LinxChipkitMax32.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <LinxArduinoUno.h>
#include <LinxSerialListener.h>

dht dht;

#define DHT22_PIN 5
 
//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxArduinoUno* LinxDevice;
//cose
int DHT22();

//Initialize LINX Device And Listener
void setup()
{
  //Instantiate The LINX Device
  LinxDevice = new LinxArduinoUno();
  
  //The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(LinxDevice, 0);
  LinxSerialConnection.AttachCustomCommand(0, DHT22);
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();
  
  //Your Code Here, But It will Slow Down The Connection With LabVIEW
}

int DHT22(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
   int chk = dht.read22(DHT22_PIN);
   response[0] = (unsigned char)dht.humidity;
   response[1] = (unsigned char)dht.temperature;
   *numResponseBytes = 2; //sarebbe meglio assegnare numInputBytes, ma col DHT22 meglio evitare.
   delay(1000); //for stability
   return 0;

   // *response = sensor
}
