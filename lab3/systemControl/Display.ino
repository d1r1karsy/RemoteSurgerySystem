#include "Display.h"                                                                        //import the header of this function
#include "dataStructs.h"                                                                    //import the variables
#include <stdio.h>                                                                          //import necessary header files
#include <stdbool.h>                                                                        //import necessary header files
#include <stddef.h>                                                                         //import necessary header files

boolean annunciation;
boolean bool_T = false;
boolean bool_S = false;
boolean bool_D = false;
boolean bool_P = false;

void displayFunction(void* displayDataStruct){                                              //function that display the data on the TFT LCD display, takes display struct as input
    struct controlDisplayData *dData = (struct controlDisplayData*) displayDataStruct;        //deference the display struct
    dData->pTempCorrectedBuf          = &tempCorrectedBuffer;                                         //assign corrected temp's address to corrected temp pointer from display struct
    dData->pBloodPressCorrectedBuf    = &systolicCorrectedBuffer;
    dData->pBloodPressCorrectedBuf    = &diastolicCorrectedBuffer;                             //assign corrected dia's address to corrected dia pointer from display struct
    dData->pPulseRateCorrected        = &pulseRateCorrectedBuffer;                                    //assign corrected pulse's address to corrected pulse pointer from display struct
    dData->pBatteryState              = &batteryState;                                          //assign battery state's address to battery state pointer from display struct

    if (annunciate.justPressed()) {
        annunciate.drawButton(true);  // draw invert!
        tft.fillScreen(BLACK);
        menu.drawButton();
        annunciate.drawButton();
        annunciation = true;
        Serial.println("annunciation is pressed");
    }

    if (menu.justReleased()) {
        // Serial.print("Released: "); Serial.println(b);
        menu.drawButton();  // draw normal
    }

    if (annunciate.justReleased()) {
        // Serial.print("Released: "); Serial.println(b);
        annunciate.drawButton();  // draw normal
    }

    if (menu.justPressed()) {
        menu.drawButton(true);  // draw invert!
        tft.fillScreen(BLACK);
        annunciate.drawButton();
        menu.drawButton();
        annunciation = false;
    }

    if (annunciation) {
        tft.setCursor(0, 0);                                                                      //move cursor to the begining of the display
        tft.setTextSize(2);                                                                       //set font size to be 2
        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.println("results from patient");                                                      //print "results from patient" on display
        tft.print("Temp: ");                                                                      //print "Temp:" on display
        if (tempGoodBool) {                                                                       //if temperature is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if temperature is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(BufferRead(dData->pTempCorrectedBuf));                                                        //print the value of the corrected temp pointer that is in the display struct on the display
        tft.println(" C   ");                                                                     //print "C" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Syst: ");                                                                      //print "Syst:" on display
        if (sysGoodBool) {                                                                        //if systolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if sys is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(BuffferRead(dData->pBloodPressCorrectedBuf.frontList));                                               //print the value of the corrected syst pointer that is in the display struct on the display
        tft.println(" mm Hg ");                                                                   //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Dias: ");                                                                      //print "Dias:" on display
        if (diaGoodBool) {                                                                        //if diastolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if dia is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(BufferRead(dData->pBloodPressCorrectedBuf.endList));                                              //print the value of the corrected dia pointer that is in the display struct on the display
        tft.println(" mm Hg ");                                                                   //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Puls: ");                                                                      //print "Puls:" on display
        if (prGoodBool) {                                                                         //if pulse is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if pulse is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(BufferRead(dData->pPulseRateCorrected));                                                   //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.println(" BPM ");                                                                     //print "BPM" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Batt: ");                                                                      //print "Batt:" on display
        if (batteryGoodBool) {                                                                    //if battery is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if battery is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print((*dData->pBatteryState) / 2);                                                   //print half of the value of the battery state pointer that is in the display struct on the display
        tft.println("%      ");                                                                   //print "%" on display
    } else {
        tft.setTextSize(3);
        tft.setTextColor(RED, BLACK);
        tft.setCursor(75, 5);
        tft.print("MENU");
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 8);
        an_T.drawButton();
        if (an_T.justReleased()) {
            an_T.drawButton();  // draw normal
        }
        if (an_T.justPressed()) {
            menu.drawButton(true);  // draw invert!
            bool_T = !bool_T;
        }
        if (bool_T) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 38);
        tft.print(BufferRead(dData->pTempCorrectedBuf));                                                        //print the value of the corrected temp pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 45);
        tft.print(" C ");                                                                     //print "C" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 75);
        an_S.drawButton();
        if (an_S.justReleased()) {
            an_S.drawButton();  // draw normal
        }
        if (an_S.justPressed()) {
            menu.drawButton(true);  // draw invert!
            bool_S = !bool_S;
        }
        if (bool_S) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 75);
        tft.print(BuffferRead(dData->pBloodPressCorrectedBuf.frontList));                                               //print the value of the corrected syst pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 82);
        tft.print(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 112);
        an_D.drawButton();
        if (an_D.justReleased()) {
            an_D.drawButton();  // draw normal
        }
        if (an_D.justPressed()) {
            menu.drawButton(true);  // draw invert!
            bool_D = !bool_D;
        }
        if (bool_D) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 112);
        tft.print(BuffferRead(dData->pBloodPressCorrectedBuf.endList));                                              //print the value of the corrected dia pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 119);
        tft.print(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 149);
        an_P.drawButton();
        if (an_P.justReleased()) {
            an_P.drawButton();  // draw normal
        }
        if (an_P.justPressed()) {
            menu.drawButton(true);  // draw invert!
            bool_P = !bool_P;
        }
        if (bool_P) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 149);
        tft.print(*dData->pPulseRateCorrected);                                                   //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 156);
        tft.print(" BPM ");
    }

}
