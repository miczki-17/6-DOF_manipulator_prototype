String reciveData = "";
char* dataP;

double x = 0;
double y = 0;
double z = 0;

int gripPos;

String tmp = "";
String lastRotation = "down";
bool low = 0;


#ifdef BAUD
void checkCommands() {                            // x120 y120 z120 g0-180 rx { x => d, f, u } l{1, 0}
  if ( Serial.available() > 0 ) {
    reciveData = Serial.readStringUntil( '\n' );
    dataP = &reciveData[ 0 ];

    while ( *dataP != NULL ) {
      switch ( *dataP ) {
        case 'x':
          dataP++;
          while ( *dataP != ' ' ) {
            tmp += *dataP;
            dataP++;
          }
          x = tmp.toDouble();
          tmp = "";
          break;

        case 'y':
          dataP++;
          while ( *dataP != ' ' ) {
            tmp += *dataP;
            dataP++;
          }
          y = tmp.toDouble();
          tmp = "";
          break;

        case 'z':
          dataP++;
          while ( *dataP != ' ' ) {
            tmp += *dataP;
            dataP++;
          }
          z = tmp.toDouble();
          tmp = "";
          break;

        case 'g':
          dataP++;
          while ( *dataP != ' ' ) {
            tmp += *dataP;
            dataP++;
          }
          gripPos = tmp.toInt();
          tmp = "";

#ifdef octopus_gripper
          gripperMove( gripPos );
#endif

          break;

        case 'r':
          dataP++;
          switch ( *dataP ) {
            case 'd':
              arm.setEffectorOrientation( down_rotation );
              lastRotation = "down";
              break;
            case 'f':
              arm.setEffectorOrientation( default_rotation );
              lastRotation = "default";
              break;
            case 'b':
              arm.setEffectorOrientation( back_rotation );
              lastRotation = "back";
              break;
            case 's':
              arm.setEffectorOrientation( straight_rotation );
              lastRotation = "straight";
              break;
            default:
              break;
          }
          break;

        case 'l':
            dataP++;
            switch ( *dataP ) {
              case '0':
                arm.setEffectorIntoLowGround(0);
                low = 0;
                break;
              case '1':
                arm.setEffectorIntoLowGround(1);
                low = 1;
                break;
              default:
                break;
            }
          break;

        default:
          dataP++;
          break;
      }
    }

    Serial.println();
    Serial.println( "--> ROBOT:");
    Serial.print( "x: " ); Serial.println( x );
    Serial.print( "y: " ); Serial.println( y );
    Serial.print( "z: " ); Serial.println( z );
    Serial.print( "rot: " ); Serial.println( lastRotation );
    Serial.print( "low: " ); Serial.println( low );
    Serial.print( "gripper pos: " ); Serial.println( gripPos );
    Serial.println();

    arm.setPoint( x, y, z );
    arm.solve();
    arm.moveWTHAccel(steppers);
  }
}
#endif
