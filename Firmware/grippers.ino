#define octopus_gripper

#define GRIPPER_OPEN 180
#define GRIPPER_CLOSE 30

#define OCTOPUS_GRIPPER_MAX_ANGLE 180   // open
#define OCTOPUS_GRIPPER_MIN_ANGLE 30    // close

#define OCTOPUS_GRIPPER_PIN GRIPPER_PIN


void initGripper() {

#ifdef octopus_gripper
  gripper.attach(OCTOPUS_GRIPPER_PIN);
  gripper.write(OCTOPUS_GRIPPER_MIN_ANGLE);
#endif

}

void gripperMove(const int POS) {

#ifdef octopus_gripper
  if (POS <= OCTOPUS_GRIPPER_MAX_ANGLE && POS >= OCTOPUS_GRIPPER_MIN_ANGLE)
    gripper.write(POS);
#endif

}

void gripperOpen() {
#ifdef octopus_gripper
  gripper.write(GRIPPER_OPEN);
#endif
}

void gripperClose() {
#ifdef octopus_gripper
  gripper.write(GRIPPER_CLOSE);
#endif
}
