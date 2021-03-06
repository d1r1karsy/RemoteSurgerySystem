#include "Measure.h"                                        //import the header of this function
#include "dataStructs.h"                                    //import the variables
#include <stdio.h>                                          //import necessary header files
#include <stdbool.h>                                        //import necessary header files
#include <stddef.h>                                         //import necessary header files
#define TEM_REQ 13                                          //set the keyword TEM_REQ to represent the number 13
#define SYS_REQ 12                                          //set the keyword SYS_REQ to represent the number 12
#define DIA_REQ 11                                          //set the keyword DIA_REQ to represent the number 11
#define PUL_REQ 10                                          //set the keyword PUL_REQ to represent the number 10

void measureFunction(struct controlMeasureData measureData,
                     int* pTempCount,
                     int* pPulseCount,
                     int* pSysCount,
                     int* pDiaCount) {
    measureData.pTemperatureRaw    = &temperatureRaw;       //assign raw temp's address to temp pointer from stuct
    measureData.pSystolicPressRaw  = &systolicPressRaw;     //assign raw sys's address to sys pointer from stuct
    measureData.pDiastolicPressRaw = &diastolicPressRaw;    //assign raw dia's address to dia pointer from stuct
    measureData.pPulseRateRaw      = &pulseRateRaw;         //assign raw pulse's address to pulse pointer from stuct

    if (digitalRead(TEM_REQ) == HIGH) {                     //if pin 13 is high, execute
        temperatureRawData(pTempCount);                     //call the temperatureRawData function to generate temp data
        Serial.print("VT");                                 //print "VT" on the serial
        if (*measureData.pTemperatureRaw < 10) {            //if value for the raw temp. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pTemperatureRaw < 100) {    //if value for the raw temp. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.println(*measureData.pTemperatureRaw);       //print the value for the raw temp. pointer on the serial
    }
    while (digitalRead(TEM_REQ) == HIGH) {                  //delays function until the pin is low
        delay(100);                                         //this allows only one data to be sent to MEGA
    }                                                       //when pin 13 is high

    if (digitalRead(SYS_REQ) == HIGH) {                     //if pin 12 is high, execute
        systolicPressRawData(pSysCount);                    //call the systolicPressRawData function to generate sys. press. data
        Serial.print("VS");                                 //print "VS" on the serial
        if (*measureData.pSystolicPressRaw < 10) {          //if value for the raw sys. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pSystolicPressRaw < 100) {  //if value for the raw sys. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.println(*measureData.pSystolicPressRaw);     //print the value for the raw sys. pointer on the serial
    }
    while (digitalRead(SYS_REQ) == HIGH) {                  //delays function until the pin is low
        delay(100);                                         //this allows only one data to be sent to MEGA
    }                                                       //when pin 12 is high


    if (digitalRead(DIA_REQ) == HIGH) {                     //if pin 11 is high, execute
        diastolicPressRawData(pDiaCount);                   //call the diastolicPressRawData function to generate dia. press. data
        Serial.print("VD");                                 //print "VD" on the serial
        if (*measureData.pDiastolicPressRaw < 10) {         //if value for the raw dia. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pDiastolicPressRaw < 100) { //if value for the raw dia. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.println(*measureData.pDiastolicPressRaw);    //print the value for the raw dia. pointer on the serial
    }
    while (digitalRead(DIA_REQ) == HIGH) {                  //delays function until the pin is low
        delay(100);                                         //this allows only one data to be sent to MEGA
    }                                                       //when pin 11 is high

    if (digitalRead(PUL_REQ) == HIGH) {                     //if pin 10 is high, execute
        pulseRateRawData(pPulseCount);                      //call the pulseRateRawData function to generate pulse data
        Serial.print("VP");                                 //print "VP" on the serial
        if (*measureData.pPulseRateRaw < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pPulseRateRaw < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.println(*measureData.pPulseRateRaw);         //print the value for the raw pulse. pointer on the serial
    }
    while (digitalRead(PUL_REQ) == HIGH) {                  //delays function until the pin is low
        delay(100);                                         //this allows only one data to be sent to MEGA
    }                                                       //when pin 10 is high
}

void temperatureRawData(int* pCount) {                      //simulates temperature data, takes an int pointer as input
    if (tempBool == 1){                                     //if temperature boolean is 1
        if (*pCount % 2 == 0) {                              //if counter is even
            temperatureRaw += 2;                            //incremenet temp by 2
        } else {                                            //if counter is odd
            temperatureRaw--;                               //decrement temp by 1
        }
    } else {                                                //if temperature boolean is 0
        if (*pCount % 2 == 0){                              //if counter is even
            temperatureRaw -= 2;                            //decrement temp by 2
        } else {                                            //if counter is odd
            temperatureRaw++;                               //incremenet temp by 1
        }
    }
    if (temperatureRaw < 15) {                              //if temperature is less than 15
        tempBool = 1;                                       //set temperature boolean to 1
    } else if (temperatureRaw > 50) {                       //if temperature is greater than 50
        tempBool = 0;                                       //set temperature boolean to 0
    }
    (*pCount)++;                                            //incremenet the value of the counter pointer by 1
}

void systolicPressRawData(int* pCount) {                    //simulates systolic press. data, takes an int pointer as input
    if (systolicPressRaw <= 100) {                          //if systolic press is less than or equal to 100
        if (*pCount % 2 == 0) {                             //if counter is even
            systolicPressRaw += 3;                          //incremenet systolic press. by 3
        } else {                                            //if counter is odd
            systolicPressRaw--;                             //decrement systolic press. by 1
        }
    } else {                                                //if systolic press. is greater than 100
        *pSystolicFunction = 1;                             //set the value of the systolic function pointer to be 1
        if (*pDiastolicFunction) {                          //if the value of diastolic function pointer is 1
            systolicPressRaw = 0;                           //set systolic press to be 0
            (*pCount)--;                                    //decrement the value of the counter pointer by 1
        }
    }
    (*pCount)++;                                            //incremenet the value of the counter pointer by 1
}

void diastolicPressRawData(int* pCount) {                   //simulates diastolic press. data, takes an int pointer as input
    if (diastolicPressRaw >= 40) {                          //if diastolic press. is greater than or equal to 40
        if (*pCount % 2 == 0) {                             //if counter is even
            diastolicPressRaw -= 2;
        } else {                                            //if counter is odd
            diastolicPressRaw++;
        }
    } else {                                                //if diastolic press. is less than 40
        *pDiastolicFunction = 1;                            //set the value of the diastolic function pointer to be 1
        if (*pSystolicFunction) {                           //if the value of the systolic function pointer is 1
            diastolicPressRaw = 0;                          //set diastolic press. to be 0
            (*pCount)--;                                    //decrement the value of the counter pointer by 1
        }
    }
    (*pCount)++;                                            //incremenet the value of the counter pointer by 1
}

void pulseRateRawData(int* pCount) {                        //simulates diastolic press. data, takes an int pointer as input
    if (pulseBool == 1) {                                   //if pulse boolean value is 1
        if (*pCount % 2 == 0) {                             //if counter is even
            pulseRateRaw++;                                 //incremenet pulse by 1
        } else {                                            //if counter is odd
            pulseRateRaw -= 3;                              //decrement pulse by 3
        }
    } else {                                                //if pulse boolean value is 0
        if (*pCount % 2 == 0) {                             //if counter is even
            pulseRateRaw--;                                 //decrement pulse by 1
        } else {                                            //if counter is odd
            pulseRateRaw +=3;                               //incremenet pulse by 3
        }
    }
    if (pulseRateRaw > 40) {                                //if pulse rate is greater than 50
        pulseBool = 1;                                      //set boolean value for pulse to be 1
    }
    if (pulseRateRaw < 15) {                                //if pulse rate is less than 50
        pulseBool = 0;                                      //set boolean value for pulse to be 0
    }
    (*pCount)++;                                            //incremenet the value of the counter pointer by 1
}
