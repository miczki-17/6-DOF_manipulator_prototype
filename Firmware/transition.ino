void cooperateWTHRobot() {
  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(0.0, 0.0, 350.0);
  arm.setEffectorOrientation(default_rotation);
  arm.setEffectorIntoLowGround(0);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(200.0, -150.0, 220.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(200.0, 0.0, 220.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  /*arm.setPoint(0.0, 0.0, 350.0);
  arm.setEffectorOrientation(default_rotation);
  arm.setEffectorIntoLowGround(0);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(-100.0, 200.0, 300.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(0);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(200.0, 200.0, 300.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(0);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(200.0, 200.0, 180.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(500);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);*/
}






/////////////////////////////////////////////////////////////
//                                                         //
//                            | <-- manipulator            //
//                           / \                           //
//                                                         //
//        -45.0         -15.0   15.0        45.0           //
//                                                         //
/////////////////////////////////////////////////////////////


double positions_table[4] = {
  -45.0,
  -15.0,
  15.0,
  45.0
};

uint8_t current_position = 0;


void cooperateWTHTransporter() {
  /*transporter.run();

  if (transporter.isSensor()) {
    if (current_pos > 3)
      current_pos = 0;

    
  }*/

  /*if (current_position > 3)
    current_position = 0;

  if (transporter.isSensor()) {
    transporter.stop();

#ifdef octopus_gripper
    gripperOpen();
    delay(200);
#endif

    arm.setPoint(175.0, 120.0, 305.0);
    arm.setEffectorOrientation(down_rotation);
    arm.setEffectorIntoLowGround(1);
    arm.solve();
    arm.moveWTHAccel(steppers);

    delay(500);

#ifdef octopus_gripper
    gripperClose();
    delay(200);
#endif

    arm.setPoint(0.0, 0.0, 250.0);
    arm.setEffectorOrientation(straight_rotation);
    arm.setEffectorIntoLowGround(1);
    arm.solve();
    arm.moveWTHAccel(steppers);

    delay(500);

    arm.setPoint(150.0, positions_table[current_position], 240.0);
    arm.setEffectorOrientation(down_rotation);
    arm.setEffectorIntoLowGround(1);
    arm.solve();
    arm.moveWTHAccel(steppers);

    delay(500);

#ifdef octopus_gripper
    gripperOpen();
    delay(200);
#endif

    arm.setPoint(0.0, 0.0, 250.0);
    arm.setEffectorOrientation(straight_rotation);
    arm.setEffectorIntoLowGround(1);
    arm.solve();
    arm.moveWTHAccel(steppers);

    delay(500);

#ifdef octopus_gripper
    gripperClose();
    delay(200);
#endif

    current_position++;
  } else {
    transporter.run();
  }*/
  
}


// shapes 

void drawRectangle() {
  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(60.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -150.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -150.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(60.0, 0.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(60.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);
}

void drawTriangle() {
  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(60.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);
  
  arm.setPoint(0.0, -200.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -100.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(60.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  
}

void drawRhombus() {
  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 300.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -100.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -200.0, 300.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -100.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 300.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);
}

void drawHexagon() {
  
}

void shownDraw1() {
  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(200.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, -200.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(150.0, 100.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 100.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(50);

  arm.setPoint(-100.0, 100.0, 250.0);
  arm.setEffectorOrientation(default_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(150.0, 100.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(150.0, -100.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  arm.setPoint(0.0, -100.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  arm.setPoint(0.0, -60.0, 300.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  arm.setPoint(0.0, 0.0, 350.0);
  arm.setEffectorOrientation(default_rotation);
  arm.setEffectorIntoLowGround(0);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);
}

void shownDraw2() {
  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(100.0, 0.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(100.0, 0.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(160.0, 100.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(100.0, 0.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(200.0, 0.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(100.0, 0.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(160.0, -100.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);
  
  delay(100);

  arm.setPoint(100.0, 0.0, 250.0);
  arm.setEffectorOrientation(down_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(100.0, 0.0, 350.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);

  arm.setPoint(0.0, 0.0, 250.0);
  arm.setEffectorOrientation(straight_rotation);
  arm.setEffectorIntoLowGround(1);
  arm.solve();
  arm.moveWTHAccel(steppers);

  delay(100);
}



int drawNumber() {
  return rand() % 2;
}
