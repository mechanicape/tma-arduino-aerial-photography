// KiteControl V 0.1
// Arduino based device for remote controlled operation of cameras used for Kite Aerial Photography
// Written by Rein Velt (http://mechanicape.com)
//
// PROTOCOL SPECIFICATIONS
//
// Hardware:
//          Serial TTL  
//          Speed: 57600bps 
//          wired or wireless (XBEE)
//
// Request: <addressbyte> <valuebyte> <terminationbyte>
//          addressbyte = (0..255) of internal address of the device
//          valuebyte   = (0..255)command or value to send
//          terminationbyte = (10) always 10 (EOLN)
//
// Response <addressbyte> <messagelengthbyte> (<valuebyte>) <terminationbyte> 
//          addressbyte = address (0.255) 
//          messagenlengthbyte = integer (0..255)
//          valuebyte = returndata (has messagelengthbyte occurences)
//          terminationbyte (10)

// The Groundcontrol Arduino is the master and sends a request to the kite Arduino.
// The kite Arduino receives and decodes the messages and resends the message to one
// of the attached sensors and actuators. The actuator returns a value or a statuscode 
// and this will be send back to the ground Arduino. This request and response messages 
// are specified above

// Addresses:
//   *device      *address  *responsebytes                                               *response 
//   Battery      32         <voltage hi> <voltage lo>                                   int millivolts
//   GPS          33         <latitude hi> < latitude lo> <longitude hi> <longitude lo>  lat+lon
//   Compass      34         <compass hi> <compass lo>                                   int degrees
//   Accel        35         
//   Temperature  36         <temperature hi> <temperature lo>                           int degrees kelvin
//   Pressure     37         <pressure hi> <pressure lo>                                 int hPa
//   Windspeed    38         <speed hi> <speed lo>                                       int km/h

//   ServoPan     128        <servo hi> <servo lo>                                       int degrees
//   ServoTilt    129        <servo hi> <servo lo>                                       int degrees
//   ServoZ       130        <servo hi> <servo lo>                                       int degrees
//   Shutter      132        <shutterstatus>                                             int
//   Zoom         133        <zoom hi>                                                   int


// We are using a minimal setup with a batterusensor and a compass sensor and pan/tilt servos

//address definitions
const int addrBattery=    32;
const int addrCompass=    34;
const int addrServoPan=   128;
const int addrServoTilt=  129;

//pin definitions
const int pinBattery=0;
const int pinServoPan=12;
const int pinServoTilt=13;

//statusCodes
const int statusError=0;
const int statusOk=1;


//global variables
int request[2];


void setup()
{
  delay(1000);
  Serial.begin(57600);
}


void loop()
{
    int isValid=readRequest();
    if (isValid==statusOk)
    {
       //process request
       int statusCode=dispatchRequestToSubDevice();
       if (statusCode==statusOk)
       {
          //ok..send data resposne 
       }
       else
       {
          //send error response
       }
       
    }
    else
    {
        //request was not valid
    }
}

int dispatchRequestToSubDevice()
{
   //look at the address and send the data to the specified subdevice
   int subdeviceResponse=statusError;
   switch (request[0])
   {
       case addrBattery:     subdeviceResponse=getBattery(request[1]);   break;
       case addrCompass:     subdeviceResponse=getCompass(request[1]);   break; 
       case addrServoPan:    subdeviceResponse=setServoPan(request[1]);  break;
       case addrServoTilt:   subdeviceResponse=setServoTilt(request[1]); break;
       default: break;
   }
   return subdeviceResponse;
}


int readRequest()
{
  int statusCode=statusError;
  if (Serial.available()>2)
  {
     int addressByte=Serial.read();
     int valueByte=Serial.read();
     int terminationByte=Serial.read();
     if (terminationByte==10)
     {
        request[0]=addressByte;
        request[1]=valueByte;
        statusCode=statusOk;
     }
  }
  return statusCode;
}






//*********** SUBDEVICE CONTROL CODE ********************

int getBattery(int requestValue)
{
   int millivolts=100;
   return millivolts; 
}

int getCompass(int requestValue)
{
   int millivolts=100;
   return millivolts; 
}

int setServoPan(int angle)
{
   int millivolts=100;
   return millivolts; 
}


int setServoTilt(int angle)
{
   int millivolts=100;
   return millivolts; 
}




