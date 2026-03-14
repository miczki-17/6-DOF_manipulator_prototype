



// -90/90     0/180     0/-180      -90/90      -90/90      0/180
// -180/180

long gotopos[ 6 ] = { 0, 0, 0, 0, 0, 0 };

double start_rotation[3][3] = {
  {0, 0, 1},
  { -1, 0, 0},
  {0, -1, 0}
};

void calibArm() {

  uint16_t i = 0;
  uint16_t j = 0;

  /*////////////////////////////////////////////////////////////////////////// <-- test
    if( digitalRead( arm.joints[ 3 ].pin.contact ) != LOW ) {
    digitalWrite( arm.joints[ 3 ].pin.dir, HIGH );
    for( ; i < 920; i++ ) {
      digitalWrite( arm.joints[ 3 ].pin.step, HIGH );
      delayMicroseconds( 800 );
      digitalWrite( arm.joints[ 3 ].pin.step, LOW );
      delayMicroseconds( 800 );
    }
    }*/

  /*i = 0;

    digitalWrite( arm.joints[ 5 ].pin.dir, LOW );
    for( ; i < 920; i++ ) {
    digitalWrite( arm.joints[ 5 ].pin.step, HIGH );
    delayMicroseconds( 800 );
    digitalWrite( arm.joints[ 5 ].pin.step, LOW );
    delayMicroseconds( 800 );
    }*/
  ///////////////////////////////////////////////////////////////////////////// <- test

  steppers[5].setCurrentPosition(0);

  if ( digitalRead( arm.joints[ 4 ].pin.contact ) == LOW ) {
    digitalWrite( arm.joints[ 4 ].pin.dir, HIGH );
    while ( 1 ) {
      if ( digitalRead( arm.joints[ 4 ].pin.contact ) == HIGH ) i++;
      digitalWrite( arm.joints[ 4 ].pin.step, HIGH );
      delayMicroseconds( 800 );
      digitalWrite( arm.joints[ 4 ].pin.step, LOW );
      delayMicroseconds( 800 );
      if ( i >= 400 )
        break;
    }
    i = 0;
  }
  digitalWrite( arm.joints[ 4 ].pin.dir, LOW );
  while ( 1 ) {
    if ( digitalRead( arm.joints[ 4 ].pin.contact ) == LOW ) i++;
    digitalWrite( arm.joints[ 4 ].pin.step, HIGH );
    delayMicroseconds( 800 );
    digitalWrite( arm.joints[ 4 ].pin.step, LOW );
    delayMicroseconds( 800 );
    if ( i >= 400 )
      break;
  }
  delay( 300 );
  /*digitalWrite( arm.joints[ 4 ].pin.dir, HIGH );
    for( i = 0; i < 1920; i++ ) {
    digitalWrite( arm.joints[ 4 ].pin.step, HIGH );
    delayMicroseconds( 800 );
    digitalWrite( arm.joints[ 4 ].pin.step, LOW );
    delayMicroseconds( 800 );
    }*/
  steppers[ 4 ].setCurrentPosition( -1920 );



  delay( 300 );



  i = 0;
  if ( digitalRead( arm.joints[ 3 ].pin.contact ) == LOW ) {
    digitalWrite( arm.joints[ 3 ].pin.dir, LOW );
    while ( 1 ) {
      if ( digitalRead( arm.joints[ 3 ].pin.contact ) == HIGH ) i++;
      digitalWrite( arm.joints[ 3 ].pin.step, HIGH );
      delayMicroseconds( 800 );
      digitalWrite( arm.joints[ 3 ].pin.step, LOW );
      delayMicroseconds( 800 );
      if ( i >= 400 )
        break;
    }
    i = 0;
  }
  digitalWrite( arm.joints[ 3 ].pin.dir, HIGH );
  while ( 1 ) {
    if ( digitalRead( arm.joints[ 3 ].pin.contact ) == LOW ) i++;
    digitalWrite( arm.joints[ 3 ].pin.step, HIGH );
    delayMicroseconds( 800 );
    digitalWrite( arm.joints[ 3 ].pin.step, LOW );
    delayMicroseconds( 800 );
    if ( i >= 400 )
      break;
  }
  steppers[3].setCurrentPosition(3840);
  /*delay( 300 );
    digitalWrite( arm.joints[ 3 ].pin.dir, LOW );
    for ( i = 0; i < 2880; i++ ) {
    digitalWrite( arm.joints[ 3 ].pin.step, HIGH );
    delayMicroseconds( 800 );
    digitalWrite( arm.joints[ 3 ].pin.step, LOW );
    delayMicroseconds( 800 );
    }
    steppers[ 3 ].setCurrentPosition( 960 );*/



  delay( 300 );



  i = 0;
  j = 0;
  digitalWrite( arm.joints[ 1 ].pin.dir, LOW );
  digitalWrite( arm.joints[ 2 ].pin.dir, HIGH );
  while ( digitalRead( arm.joints[ 1 ].pin.contact ) == HIGH || digitalRead( arm.joints[ 2 ].pin.contact ) == HIGH ) {

    if ( digitalRead( arm.joints[ 1 ].pin.contact ) == HIGH ) {
      digitalWrite( arm.joints[ 1 ].pin.step, HIGH );
      delayMicroseconds( 900 );
      digitalWrite( arm.joints[ 1 ].pin.step, LOW );
      delayMicroseconds( 900 );
    }

    if ( digitalRead( arm.joints[ 2 ].pin.contact ) == HIGH ) {
      digitalWrite( arm.joints[ 2 ].pin.step, HIGH );
      delayMicroseconds( 600 );
      digitalWrite( arm.joints[ 2 ].pin.step, LOW );
      delayMicroseconds( 600 );
    }
  }
  /*for ( ; i < 200; i++ ) {
    digitalWrite( arm.joints[ 1 ].pin.step, HIGH );
    delayMicroseconds( 900 );
    digitalWrite( arm.joints[ 1 ].pin.step, LOW );
    delayMicroseconds( 900 );

    digitalWrite( arm.joints[ 2 ].pin.step, HIGH );
    delayMicroseconds( 900 );
    digitalWrite( arm.joints[ 2 ].pin.step, LOW );
    delayMicroseconds( 900 );
  }
  i = 0;
  j = 0;*/

  delay( 500 );

  digitalWrite( arm.joints[ 1 ].pin.dir, HIGH );
  digitalWrite( arm.joints[ 2 ].pin.dir, LOW );
  for ( i = 0; i < 3440; i++ ) {                            // 3840 - 400
    digitalWrite( arm.joints[ 2 ].pin.step, HIGH );
    delayMicroseconds( 600 );   // 600
    digitalWrite( arm.joints[ 2 ].pin.step, LOW );
    delayMicroseconds( 600 );   // 600
    if ( i < 2480 ) {                                       // these numbers was obtained from tests
      digitalWrite( arm.joints[ 1 ].pin.step, HIGH );
      delayMicroseconds( 900 );  // 900
      digitalWrite( arm.joints[ 1 ].pin.step, LOW );
      delayMicroseconds( 900 );  // 900
    }
  }
  steppers[ 1 ].setCurrentPosition( 2840 );
  steppers[ 2 ].setCurrentPosition( -1920 );



  delay( 500 );



  i = 0;
  digitalWrite( arm.joints[ 0 ].pin.dir, LOW );
  while ( 1 ) {
    if ( digitalRead( arm.joints[ 0 ].pin.contact ) == LOW ) i++;
    digitalWrite( arm.joints[ 0 ].pin.step, HIGH );
    delayMicroseconds( 900 );
    digitalWrite( arm.joints[ 0 ].pin.step, LOW );
    delayMicroseconds( 900 );
    if ( i >= 400 )
      break;
  }
  delay( 300 );
  digitalWrite( arm.joints[ 0 ].pin.dir, HIGH );
  for ( i = 0; i < 3840; i++ ) {
    digitalWrite( arm.joints[ 0 ].pin.step, HIGH );
    delayMicroseconds( 900 );
    digitalWrite( arm.joints[ 0 ].pin.step, LOW );
    delayMicroseconds( 900 );
  }
  steppers[ 0 ].setCurrentPosition( 0 );

}

void initArm() {

  uint8_t i;
  for ( i = 0; i < JOINTS_NUM; i++ ) {
    steppers[ i ] = AccelStepper( 1, arm.joints[ i ].pin.step, arm.joints[ i ].pin.dir );
    steppers[ i ].setMaxSpeed( arm.joints[ i ].speed.speed );
    steppers[ i ].setAcceleration( arm.joints[ i ].speed.accel );
    steppers[ i ].setCurrentPosition( 0 );
  }

  for ( i = 0; i < JOINTS_NUM; i++ ) {
    pinMode( arm.joints[ i ].pin.contact, INPUT_PULLUP );
    pinMode( arm.joints[ i ].pin.step,    OUTPUT );
    pinMode( arm.joints[ i ].pin.dir,     OUTPUT );
  }

  //for ( i = 0; i < JOINTS_NUM; i++ )
    //steppersControl.addStepper( steppers[ i ] );

}

void setSpeedJoints(int speed) {
  for (uint8_t i = 0; i < JOINTS_NUM; i++) {
    steppers[i].setMaxSpeed(speed);
  }
}


void prepareArm( void ) {
#ifdef BAUD
  Serial.println("Calibration\n");
#endif


  
  calibArm();
  //steppers[0].setCurrentPosition(0);
  //steppers[1].setCurrentPosition(2840);
  //steppers[2].setCurrentPosition(-1920);
  //steppers[3].setCurrentPosition(3840);
  //steppers[4].setCurrentPosition(-1920);
  //steppers[5].setCurrentPosition(0);

#ifdef BAUD
  Serial.println("Calibration passed, wait...\n");
#endif
  delay( 1000 );


  arm.setPoint( 0.0, 0.0, 250.0 );
  arm.setEffectorOrientation(start_rotation);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay( 1000 );
}



/*void setAccel() {
  uint8_t i;
  float accel;
  for( i = 0; i < JOINTS_NUM; i++ ) {
    accel = arm.joints[ i ].angle.steps + BASIC_ACCEL;
    stepper[ i ].setAcceleration( accel );
    arm.joints[ i ].speed.accel = accel;
  }
  }*/
  
