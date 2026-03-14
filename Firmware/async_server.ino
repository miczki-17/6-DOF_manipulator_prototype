#include <Arduino_JSON.h>
JSONVar readings;

#ifdef WIFI_CONTROLLER
  #if WIFI_CONTROLLER == ESP32

    #ifndef async_server
    #define async_server





      // websocket events

      /*char *toString( double number ) {
        char *buff = new char[10];
        sprintf( buff, "%.1f", number );
        return buff;
      }

      String prepareVelocity() {
        String result;

        result += toString(20);
        return result;
      }

      

      void notifyClients( String key, String value ) {
        const uint8_t size = JSON_OBJECT_SIZE( 1 );
        StaticJsonDocument< size > json;

        json[ key.c_str() ] = value.c_str();

        char data[ 20 ];
        size_t len = serializeJson( json, data );
        ws.textAll( data, len );
      }

      void sendPosition() {
        notifyClients( "posx", toString(100) );
      }

      void sendVelocity() {
        notifyClients("vel", prepareVelocity());
      }*/



      // warning! --> !only 20 bytes to send!
      
      /*void notifyClients( String key, String value ) {
        const uint8_t size = JSON_OBJECT_SIZE( 1 );
        StaticJsonDocument< size > json;

        json[ key.c_str() ] = value.c_str();

        char data[ 20 ];
        size_t len = serializeJson( json, data );
        ws.textAll( data, len );
      }*/


      
      // for check cmd msg-s
      bool tryAction( const char *action, const char *act ) {
        if ( strcmp( action, act ) == 0 )
          return true;
        return false;
      }

      // recive msg from clients
      void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {

          const uint8_t size = JSON_OBJECT_SIZE( 1 ) + JSON_OBJECT_SIZE( 2 );
          StaticJsonDocument<size> json;
          DeserializationError err = deserializeJson(json, data);
          if (err) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
          }
          const char *action = json["action"];

          //twice examples for you :>
          //if ( tryAction( action, "read" ) ) {
            //Serial.println( "read" );
            //notifyClientsReadFile( "read", readFile( "program.txt" ) );
          //}

          //if ( tryAction( action, "upload" ) ) {
            //const char *program = json["program"];
            //Serial.println( "upload" );
            ///uploadFile( "program.txt", program );
          //}
          //

          /*if (tryAction(action, "transporter")) {
            #ifdef BAUD
              Serial.println("cooperate with transporter\n");
            #endif
            isCooperateWTHTransporter = true;
            isCooperateWTHRobot = false;
          }

          if (tryAction(action, "robot")) {
            #ifdef BAUD
              Serial.println("cooperate with robot\n");
            #endif
            isCooperateWTHTransporter = false;
            isCooperateWTHRobot = true;
          }*/

          if( tryAction(action, "rectangle")) {
            #ifdef BAUD
              Serial.println("rectangle\n");
            #endif
            isRectangle = true;
          }

          if (tryAction(action, "triangle")) {
            #ifdef BAUD
              Serial.println("triangle\n");
            #endif
            isTriangle = true;
          }

          if (tryAction(action, "rhombus")) {
            #ifdef BAUD
              Serial.println("rhombus\n");
            #endif
            isRhombus = true;
          }

          if (tryAction(action, "hexagon")) {
            #ifdef BAUD
              Serial.println("hexagon\n");
            #endif
            isHexagon = true;
          }

          if (tryAction(action, "stop")) {
            #ifdef BAUD
              Serial.println("stop\n");
            #endif
            isStop = !isStop;

            isRectangle = false;
            isTriangle = false;
            isRhombus = false;
            isHexagon = false;

            slidersPos.x = 0;
            slidersPos.y = 0;
            slidersPos.z = 250;

            arm.setPoint(slidersPos.x, slidersPos.y, slidersPos.z);
            arm.setEffectorOrientation(down_rotation);
            arm.setEffectorIntoLowGround(1);
            arm.solve();
            arm.moveWTHAccel(steppers);
          }

          //checkControl( action );
          //checkRotation( action );



          ///////////////////////////////////////////////////////////// <-- sliders
          
          /*if (tryAction(action, "posX")) {
            const char *pos = json["pos"];
            slidersPos.x = atof(pos);
            #ifdef BAUD
              Serial.print("X slider position: ");
              Serial.println(slidersPos.x);
            #endif
          }
          if (tryAction(action, "posY")) {
            const char *pos = json["pos"];
            slidersPos.y = atof(pos);
            #ifdef BAUD
              Serial.print("Y slider position: ");
              Serial.println(slidersPos.y);
            #endif
          }
          if (tryAction(action, "posZ")) {
            const char *pos = json["pos"];
            slidersPos.z = atof(pos);
            #ifdef BAUD
              Serial.print("Z slider position: ");
              Serial.println(slidersPos.z);
            #endif
          }*/

          ///////////////////////////////////////////////////////////// <-- sliders
    
        }
      }

      
      void onEvent(AsyncWebSocket       *server,
                   AsyncWebSocketClient *client,
                   AwsEventType         type,
                   void                 *arg,
                   uint8_t              *data,
                   size_t               len) {
        switch (type) {
          case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
          break;
          case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
          case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;
          case WS_EVT_PONG:
          case WS_EVT_ERROR:
            break;
        }
      }





      // processor func
      String processor(const String& var) {
        
      }





      void loadHTML() {
        // adding html file from esp32 spiffs memory space
        server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
          request->send(SPIFFS, "/website.html", String(), false, processor);
        });
      }

      void loadCSS() {
        //adding css file from esp32 spiffs memory space
        server.on( "/web_style.css", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/web_style.css", "text/css" );
        });
        server.on( "/preloader.css", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/preloader.css", "text/css" );
        });

        server.on( "/sliders/sliders.css", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/sliders/sliders.css", "text/css" );
        });
      }

      void loadJavaScript() {
        //adding js script from esp32 spiffs memory space into async wesite
        server.on( "/websocket.js", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/websocket.js", "text/javascript" );
        });
        server.on( "/jquery.js", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/jquery.js", "text/javascript" );
        });

        server.on( "/sliders/sliders.js", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/sliders/sliders.js", "text/javascript" );
        });
      }

      void loadImg() {
        // adding imgs into async website

        server.on( "/robot_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/robot_button.png", "image/png" );
        });
        server.on( "/transporter_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/transporter_button.png", "image/png" );
        });


        server.on( "/stop/STOP_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/stop/STOP_button.png", "image/png" );
        });
        


        // triangle
        server.on( "/triangle/triangle_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/triangle/triangle_button.png", "image/png" );
        });
        server.on( "/triangle/triangle_part_1.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/triangle/triangle_part_1.png", "image/png" );
        });
        server.on( "/triangle/triangle_part_2.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/triangle/triangle_part_2.png", "image/png" );
        });
        server.on( "/triangle/triangle_part_3.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/triangle/triangle_part_3.png", "image/png" );
        });


        // square
        server.on( "/square/square_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/square/square_button.png", "image/png" );
        });
        server.on( "/square/square_part_1.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/square/square_part_1.png", "image/png" );
        });
        server.on( "/square/square_part_2.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/square/square_part_2.png", "image/png" );
        });
        server.on( "/square/square_part_3.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/square/square_part_3.png", "image/png" );
        });
        server.on( "/square/square_part_4.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/square/square_part_4.png", "image/png" );
        });


        // rhombus
        server.on( "/rhombus/rhombus_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/rhombus/rhombus_button.png", "image/png" );
        });
        server.on( "/rhombus/rhombus_part_1.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/rhombus/rhombus_part_1.png", "image/png" );
        });
        server.on( "/rhombus/rhombus_part_2.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/rhombus/rhombus_part_2.png", "image/png" );
        });
        server.on( "/rhombus/rhombus_part_3.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/rhombus/rhombus_part_3.png", "image/png" );
        });
        server.on( "/rhombus/rhombus_part_4.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/rhombus/rhombus_part_4.png", "image/png" );
        });


        // hexagon
        server.on( "/hexagon/hexagon_button.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_button.png", "image/png" );
        });
        server.on( "/hexagon/hexagon_part_1.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_part_1.png", "image/png" );
        });
        server.on( "/hexagon/hexagon_part_2.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_part_2.png", "image/png" );
        });
        server.on( "/hexagon/hexagon_part_3.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_part_3.png", "image/png" );
        });
        server.on( "/hexagon/hexagon_part_4.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_part_4.png", "image/png" );
        });
        server.on( "/hexagon/hexagon_part_5.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_part_5.png", "image/png" );
        });
        server.on( "/hexagon/hexagon_part_6.png", []( AsyncWebServerRequest * request ) {
          request -> send( SPIFFS, "/hexagon/hexagon_part_6.png", "image/png" );
        });
      }
      

      
      

      void serverLoadResources() {
        loadHTML();
        loadCSS();
        loadJavaScript();
        loadImg();
      }

      void initWebSocket() {
        ws.onEvent(onEvent);
        server.addHandler(&ws);
      }

      void initWiFi() {
        WiFi.softAP(ssid, password);
        IPAddress IP = WiFi.softAPIP();

        
  
        #ifdef BAUD
          Serial.print("AP IP address: ");
          Serial.println(IP);
        #endif
      }

      void startServer() {
        server.begin();
      }







      char *toString(double number) {
        char *buff = new char[10];
        sprintf(buff, "%.1f", number);
        return buff;
      }
      

      String preparePositions() {
        double x, y, z;
        arm.getPos(x, y, z);
        z += 94.3;

        String result = "";
        result += toString(x) + String("<br>")
               + toString(y) + String("<br>")
               + toString(z);
        return result;
      }
      

      String prepareVelocity() {
        String result = "effector velocity:<br> 0.3 m/s";

        return result;
      }



      // sending actual effector position to clients
     

      String getReadings() {
        readings["positions"] = preparePositions();
        readings["velocity"]  = prepareVelocity();
        String jsonString = JSON.stringify(readings);
        return jsonString;
      }

      void notifyClients(String data) {
        ws.textAll(data);
      }

      

    #endif

  #endif
#endif
