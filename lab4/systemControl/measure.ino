#include "Measure.h"                                                                            //import the header of this function
#include "dataStructs.h"                                                                        //import the variables
#include <stdio.h>                                                                              //import necessary header files
#include <stdbool.h>                                                                            //import necessary header files
#include <stddef.h>                                                                             //import necessary header files
#define REQ 22                                                                                  //set REQ to be number 22
#define EXT 53
#define ACK 52

void measureFunction(void* measureDataStruct) {                                                 //function that recieves the raw data from UNO, takes measure struct as input
    struct controlMeasureData *mData = (struct controlMeasureData*) measureDataStruct;          //deference the display struct
    mData->pTemperatureRaw     = &tempRawData;                                               //assign raw temp's address to raw temp pointer from measure struct
    mData->pSystolicPressRaw   = &sysRawData;                                             //assign raw sys's address to raw sys pointer from measure struct
    mData->pDiastolicPressRaw  = &diaRawData;                                            //assign raw dia's address to raw dia pointer from measure struct
    mData->pPulseRateRaw       = &pulseRawData;
    mData->pRespRaw            = &respRawData;                                               //assign raw pulse's address to raw pulse pointer from measure struct
    if (Serial1.read() == 'V') {                                                                //execture if the letter 'V' is read
        Serial1.readBytes(dataTransfered, 20);                                                  //store the next 4 characters written on serial one to dataTranfered character array
        Serial.print(dataTransfered[0]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[1]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[2]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[3]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[4]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[5]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[6]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[7]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[8]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[9]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[10]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[11]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[12]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[13]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[14]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[15]);                                                     //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[16]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[17]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[18]);                                                       //print the charater array on serial for troubleshooting purposes
        Serial.println(dataTransfered[19]);
        unsigned int digit1 = dataTransfered[1] - '0';                                          //convert the characters to digits
        unsigned int digit2 = dataTransfered[2] - '0';                                          //convert the characters to digits
        unsigned int digit3 = dataTransfered[3] - '0';                                          //convert the characters to digits
        unsigned int digit5 = dataTransfered[5] - '0';                                          //convert the characters to digits
        unsigned int digit6 = dataTransfered[6] - '0';                                          //convert the characters to digits
        unsigned int digit7 = dataTransfered[7] - '0';                                          //convert the characters to digits
        unsigned int digit9 = dataTransfered[9] - '0';                                          //convert the characters to digits
        unsigned int digit10 = dataTransfered[10] - '0';                                        //convert the characters to digits
        unsigned int digit11 = dataTransfered[11] - '0';                                        //convert the characters to digits
        unsigned int digit13 = dataTransfered[13] - '0';                                        //convert the characters to digits
        unsigned int digit14 = dataTransfered[14] - '0';                                        //convert the characters to digits
        unsigned int digit15 = dataTransfered[15] - '0';                                        //convert the characters to digits
        unsigned int digit17 = dataTransfered[17] - '0';                                        //convert the characters to digits
        unsigned int digit18 = dataTransfered[18] - '0';                                        //convert the characters to digits
        unsigned int digit19 = dataTransfered[19] - '0';                                        //convert the characters to digits

        if ((dataTransfered[0] == 'T')  && (digit1 < 10)  && (digit2 < 10)  && (digit3 < 10)  &&
            (dataTransfered[4] == 'S')  && (digit5 < 10)  && (digit6 < 10)  && (digit7 < 10)  &&
            (dataTransfered[8] == 'D')  && (digit9 < 10)  && (digit10 < 10) && (digit11 < 10) &&
            (dataTransfered[12] == 'P') && (digit13 < 10) && (digit14 < 10) && (digit15 < 10) &&
            (dataTransfered[16] == 'R') && (digit17 < 10) && (digit18 < 10) && (digit19 < 10)) {//make sure all data revieced is valied
            mData->pTemperatureRaw->push((digit1 * 100) + (digit2 * 10) + (digit3 * 1));                    //assign the value of the temperature raw pointer from the measure struct to corrected buffer
            mData->pSystolicPressRaw->push((digit5 * 100) + (digit6 * 10) + (digit7 * 1));                     //assign the value of the systolic raw pointer from the measure struct to corrected buffer
            mData->pDiastolicPressRaw->push((digit9 * 100) + (digit10 * 10) + (digit11 * 1));                   //assign the value of the diastolic raw pointer from the measure struct to corrected buffer
            mData->pPulseRateRaw->push((digit13 * 100) + (digit14 * 10) + (digit15 * 1));                //assign the value of the pulse raw pointer from the measure struct to corrected buffer
            mData->pRespRaw->push((digit17 * 100) + (digit18 * 10) + (digit19 * 1));                //assign the value of the pulse raw pointer from the measure struct to corrected buffer
            //runCompute = true;                                                                  //set the boolean to run compute true
        } else {
            //runCompute = false;                                                                 //set the boolean to run compute false
        }
    } else {
        //runCompute = false;                                                                     //set the boolean to run compute false
    }

    if (!pinHighPS && (digitalRead(EXT) == HIGH)) {         //check if the request pin turned high
        pinHighNS = true;                                   //if so, make the current state true
    } else if (pinHighPS && (digitalRead(EXT) == HIGH)) {   //if request pin is true and it has been true
        pinHighNS = true;                                   // keep the current state true
    } else {                                                //in any other case
      pinHighNS = false;                                    //make current case false
    }

    if (!pinHighPS && pinHighNS) {
        Serial.println("We are in");
        digitalWrite(ACK, HIGH);

        Serial2.print("VT");                                 //print "VT" on the serial
        if ((int)mData->pTemperatureRaw->last() < 10) {            //if value for the raw temp. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)mData->pTemperatureRaw->last() < 100) {    //if value for the raw temp. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)mData->pTemperatureRaw->last());         //print the value for the raw temp. pointer on the serial
        Serial2.print("S");                                  //print "VS" on the serial
        if ((int)mData->pSystolicPressRaw->last() < 10) {          //if value for the raw sys. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)mData->pSystolicPressRaw->last() < 100) {  //if value for the raw sys. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)mData->pSystolicPressRaw->last());       //print the value for the raw sys. pointer on the serial
        Serial2.print("D");                                  //print "VD" on the serial
        if ((int)mData->pDiastolicPressRaw->last() < 10) {         //if value for the raw dia. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)mData->pDiastolicPressRaw->last() < 100) { //if value for the raw dia. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)mData->pDiastolicPressRaw->last());      //print the value for the raw dia. pointer on the serial                    //call the pulseRateRawData function to generate pulse data
        Serial2.print("P");                                  //print "VP" on the serial
        if ((int)mData->pPulseRateRaw->last() < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)mData->pPulseRateRaw->last() < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)mData->pPulseRateRaw->last());         //print the value for the raw pulse. pointer on the serial
        Serial2.print("R");                                  //print "VP" on the serial
        if ((int)mData->pRespRaw->last() < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)mData->pRespRaw->last() < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.println((int)mData->pRespRaw->last());
        digitalWrite(ACK, LOW);
    }

    pinHighPS = pinHighNS;
}
