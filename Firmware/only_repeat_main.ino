#include <AccelStepper.h>
#include <ESP32Servo.h>
#include <time.h>

#include "headers/arm_config.h"
#include "headers/rotations.h"
#include "headers/defines.h"
#include "headers/joint.h"
#include "headers/server_config.h"

#include "libs/arm.h"
#include "libs/arm.cpp"

#include "libs/transporter.h"
#include "libs/transporter.cpp"

//#include "soc/rtc_wdt.h"


AccelStepper steppers[ JOINTS_NUM ];
ARM arm;


Servo gripper;


//Transporter transporter;


#ifdef WIFI_CONTROLLER
  #if WIFI_CONTROLLER == ESP32
    #include <AsyncTCP.h>
    #include <WiFi.h>
    #include <ESPAsyncWebServer.h>
    #include <ArduinoJson.h>
  #endif
#endif

#ifdef CONTROLLER_TYPE
  #if CONTROLLER_TYPE == ESP32
    #include <SPIFFS.h>
  #endif
#endif

#if WIFI_CONTROLLER == ESP32
  #ifdef SERVER_PORT
    AsyncWebServer server(SERVER_PORT);
    AsyncWebSocket ws(ws_gate);
  #else
    AsyncWebServer server(80);
    AsyncWebSocket ws("/ws");
  #endif
#endif

#define SERVICE_LED_PIN 15




typedef unsigned long ul;
ul currentMicros;
ul lastMicros = 0;
ul elapsedMicros = 0;

ul serviceCurrentMicros;
ul serviceLastMicros = 0;
ul serviceElapsedMicros = 0;


ul serviceCurrentMillis;
ul serviceLastMillis = 0;
ul serviceElapsedMillis = 0;


TaskHandle_t ServiceTask;

bool mainLoopIsReady = false;
bool serviceLoopIsReady = false;

bool isCooperateWTHTransporter = false;
bool isCooperateWTHRobot = false;


bool isStop = false;

bool isRectangle = false;
bool isTriangle = false;
bool isRhombus = false;
bool isHexagon = false;

bool serviceLedState = LOW;


struct {
  double x;
  double y;
  double z;
} slidersPos;



int randomNumber;



void setup() {

//rtc_wdt_protect_off();    // Turns off the automatic wdt service
//rtc_wdt_enable();         // Turn it on manually
//rtc_wdt_set_time(RTC_WDT_STAGE0, 50000);  // Define how long you desire to let dog wait.

//transporter.init();
//transporter.stop();
//delay(100);

  //initServiceLed();

#if CONTROLLER_TYPE == ESP32
  initSPIFFS();
#endif

xTaskCreatePinnedToCore(
    serviceLoop,
    "service",
    8192,
    NULL,
    0,
    &ServiceTask,
    0);

delay( 1000 );


initArm();
delay(100);

  //initGripper();
  //gripperClose();
  //delay( 100 );

#ifdef BAUD
  Serial.begin(BAUD);
  Serial.println("Ready!");
#endif

srand(time(NULL));
}

void loop() {
  
  prepareArm();
  
  mainLoopIsReady = true;

  while (mainLoopIsReady) {
    //currentMicros = micros();
    //elapsedMicros = currentMicros - lastMicros;

    //if (elapsedMicros > MAIN_LOOP_TIME) {
      //checkCommands();

      /*if (isStop) {
        //arm.setPoint(slidersPos.x, slidersPos.y, slidersPos.z);
        //arm.setEffectorOrientation(down_rotation);
        //arm.setEffectorIntoLowGround(1);
        //arm.solve();
        //arm.moveWTHAccel(steppers);
        // during stop
      }

      if (isRectangle) {
        drawRectangle();
        isRectangle = false;
      }

      if (isTriangle) {
        drawTriangle();
        isTriangle = false;
      }

      if (isRhombus) {
        drawRhombus();
        isRhombus = false;
      }

      if (isHexagon) {
        shownDraw();
        isHexagon = false;
      }*/

      /*switch (drawNumber()) {
        case 0:
          shownDraw1();
          break;
        case 1:
          shownDraw2();
          break;
        default:
          break;
      }*/

      shownDraw1();
      delay(3000);

      

      // cooperate functions

      /*if (isCooperateWTHRobot) {
        transporter.stop();
        cooperateWTHRobot();
      }

      if (isCooperateWTHTransporter) {
        cooperateWTHTransporter();
      }*/

      //cooperateWTHTransporter();

      //lastMicros = currentMicros;
    //}

    //rtc_wdt_feed();

  }
}





void serviceSetup() {

#if WIFI_CONTROLLER == ESP32
  initWiFi();
  initWebSocket();
  serverLoadResources();
  startServer();
#endif

  serviceLoopIsReady = true;
}

void serviceLoop(void *param) {
  serviceSetup();

  while (serviceLoopIsReady) {

    serviceCurrentMicros = micros();
    serviceElapsedMicros = serviceCurrentMicros - serviceLastMicros;

    if ( serviceElapsedMicros > SERVICE_LOOP_TIME ) {

      

#if WIFI_CONTROLLER == ESP32
      ws.cleanupClients();
#endif
      
      serviceLastMicros = serviceCurrentMicros;
    }

    serviceCurrentMillis = millis();
    serviceElapsedMillis = serviceCurrentMillis - serviceLastMillis;

    if ( serviceElapsedMillis > SERVICE_DATA_SENDING_TIME ) {

#ifdef WIFI_CONTROLLER
      String positionAndVelocityReadings = getReadings();
      notifyClients(positionAndVelocityReadings);
#endif

      //serviceLedChangeState();

      //notifyClientsPositionAndVelocity();
      //sendPosition();
      //sendVelocity();

/*#if CONTROLLER_TYPE == ESP32
#if WIFI_CONTROLLER == ESP32
      if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        serviceLedChangeState();
      } else {
        serviceLedOn();
      }
#endif
#endif*/

      serviceLastMillis = serviceCurrentMillis;
    }
    
  }
}







////////////////////////////////////////////// <- services

void initServiceLed() {
  pinMode(SERVICE_LED_PIN, OUTPUT);
  digitalWrite(SERVICE_LED_PIN, serviceLedState);
}

void serviceLedOn() {
  digitalWrite(SERVICE_LED_PIN, serviceLedState = HIGH);
}

void serviceLedOff() {
  digitalWrite(SERVICE_LED_PIN, serviceLedState = LOW);
}

void serviceLedChangeState() {
  digitalWrite(SERVICE_LED_PIN, serviceLedState = !serviceLedState);
}
