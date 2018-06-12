#include "main.h"
//#include "autofunctions.h"
#include "LCD.h"
//#include "drive.h"
//#include "intake.h"
//#include "chainbar.h"
//#include "mogo.h"
//#include "arm.h"
#define Left 1
#define Center 2
#define Right 4
void LCD_Disabled(void *ignore){

  int screen = 0;
  int screenCap = 4;
  int buttonDelay = 100;
  int screenDelay = 75;
  currentAuto = 7; //was int
  lcdClear(uart1);

  while(true){
    delay(25);

    if(!isEnabled()){
      switch(screen){
        case 0:
          lcdPrint(uart1, 1, "Backlight Setup");
          lcdPrint(uart1, 2, "<-ON ENTER OFF->");
          if (lcdReadButtons(uart1) == Center){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Please wait...");
            delay(buttonDelay);
            screen += 1;
          }
          if (lcdReadButtons(uart1)==Left){
            lcdSetBacklight(uart1, true);
          }
          if(lcdReadButtons(uart1)==Right){
            lcdSetBacklight(uart1, false);
          }
        case 1:
        lcdPrint(uart1, 1, "Auto  %d ", currentAuto);
          if(lcdReadButtons(uart1) == Center){
              lcdClear(uart1);
              lcdSetText(uart1, 1, "Please wait...");
              delay(buttonDelay);
              screen += 1;}
          if(lcdReadButtons(uart1) == Left){
              lcdClear(uart1);
              lcdSetText(uart1, 1, "Please wait...");
              delay(buttonDelay);
              currentAuto -= 1;}
          if(lcdReadButtons(uart1) == Right){
              lcdClear(uart1);
              lcdSetText(uart1, 1, "Please wait...");
              delay(buttonDelay);
              currentAuto += 1;}
        break;

        case 2:
        lcdPrint(uart1, 1, "Pot1 = %d", analogRead(Pot1));
        lcdPrint(uart1, 2, "Pot2 = %d", analogRead(Pot2));
          if(lcdReadButtons(uart1) == 2){
              lcdClear(uart1);
              lcdSetText(uart1, 1, "Please wait...");
              delay(buttonDelay);
              screen += 1;}

        break;

        case 3:
        lcdPrint(uart1, 1, "Encoder R = %d", encoderGet(EncoderR));
        lcdPrint(uart1, 2, "Encoder L = %d", encoderGet(EncoderL));
          if(lcdReadButtons(uart1) == Center){
              lcdClear(uart1);
              lcdSetText(uart1, 1, "Please wait...");
              delay(buttonDelay);
              screen += 1;}
        break;

        case 4:
        lcdPrint(uart1, 1, "Gyro = %d", gyroGet(gyro));
        lcdPrint(uart1, 2, "Nothing Here...");
          if(lcdReadButtons(uart1) == Center){
              lcdClear(uart1);
              lcdSetText(uart1, 1, "wait");
              delay(buttonDelay);
              screen += 1;}

        break;

        default:
          lcdClear(uart1);
          lcdSetText(uart1, 1, "DEFAULT");
          delay(screenDelay);
          screen = 1;
        break;
        }

      //screen cap reset
      if(screen > screenCap){screen = 1;}

      //auto line dispalby
      if(screen == 1){
        switch(currentAuto){
          case -1:
            lcdSetText(uart1, 2, "No Auto Selected");
          break;
          case 0:
            lcdSetText(uart1, 2, "");
          break;
          case 1:
            lcdSetText(uart1, 2, "");
          break;
          case 2:
            lcdSetText(uart1, 2, "");
          break;
          case 3:
            lcdSetText(uart1, 2, "");
            break;
          }}
          delay(20);
  }
  else{delay(screenDelay);}
  }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void LCD_Teleop(void *ignore){
  int screen = 1;
  int screenCap = 2;
  int buttonDelay = 50;
  int screenDelay = 75;
  lcdClear(uart1);

  while(isEnabled()){
    delay(25);
    switch(screen){
      case 1:
      lcdPrint(uart1, 1, "Auto  %d ", currentAuto);
        if(lcdReadButtons(uart1) == Center){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Please wait...");
            delay(buttonDelay);
            screen += 1;}
        if(lcdReadButtons(uart1) == Left){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Please wait...");
            delay(buttonDelay);
            currentAuto -= 1;}
        if(lcdReadButtons(uart1) == Right){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Please wait...");
            delay(buttonDelay);
            currentAuto += 1;}
      break;

      case 2:
      lcdPrint(uart1, 1, "Pot1 = %d", analogRead(Pot1));
      lcdPrint(uart1, 2, "Pot2 = %d", analogRead(Pot2));
        if(lcdReadButtons(uart1) == 2){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Please wait...");
            delay(buttonDelay);
            screen += 1;}

      break;

      case 3:
      lcdPrint(uart1, 1, "Encoder R = %d", encoderGet(EncoderR));
      lcdPrint(uart1, 2, "Encoder L = %d", encoderGet(EncoderL));
        if(lcdReadButtons(uart1) == Center){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Please wait...");
            delay(buttonDelay);
            screen += 1;}
      break;

      case 4:
      lcdPrint(uart1, 1, "Gyro = %d", gyroGet(gyro));
      lcdPrint(uart1, 2, "Nothing Here...");
        if(lcdReadButtons(uart1) == Center){
            lcdClear(uart1);
            lcdSetText(uart1, 1, "wait");
            delay(buttonDelay);
            screen += 1;}

      break;

      default:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Default");
        delay(screenDelay);
        screen = 1;
      break;
      }
      //screen cap reset
      if(screen > screenCap){screen = 1;}
    }
  taskDelete(LCD_Teleop_task);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void LCD_Auto(void *ignore){
  lcdClear(uart1);
  int waitScreen = 0;
  while(isAutonomous()){
    switch(waitScreen){
      case 0:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "(|°_°) ┬─┬");
        delay(750);
        waitScreen += 1;
     case 1:
       lcdClear(uart1);
       lcdSetText(uart1, 1, "(╯°□°）╯︵ ┻━┻");
       delay(750);
       waitScreen += 1;
     case 2:
       lcdClear(uart1);
       lcdSetText(uart1, 1, "(╯°□°）╯   ┬─┬");
       delay(750);
       waitScreen += 1;
     case 3:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "(|°_°)    ┬─┬");
      delay(100);
      waitScreen += 1;
    case 4:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "(|°_°)  ┬─┬");
      delay(100);
      waitScreen += 1;
    case 5:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "(|°_°) ┬─┬");
      delay(100);
      waitScreen += 1;
    }
    if(waitScreen > 5){waitScreen = 0;}
    delay(25);
  }
  //taskDelete(autolcd_task);
}
