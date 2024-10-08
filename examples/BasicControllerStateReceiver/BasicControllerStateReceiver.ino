#include <ControllerStateReceiver.h>
#include <TaskScheduler.h>

#define CE_PIN 22
#define CSN_PIN 23
#define RF24_ADDRESS "TRC24"

ControllerStateReceiver controller(CE_PIN, CSN_PIN, RF24_ADDRESS);
Scheduler runner;

void loopTask() {
  // Checks and updates the controller states
  bool isDataReceived = controller.update();

  if (isDataReceived) {
    // Check the buttons when there is data received

    // Example: Print the state of all buttons
    if (controller.triangle()) { Serial.println("Triangle pressed"); }
    if (controller.circle())   { Serial.println("Circle pressed"); }
    if (controller.square())   { Serial.println("Square pressed"); }
    if (controller.cross())    { Serial.println("Cross pressed"); }
    if (controller.up())       { Serial.println("Up pressed"); }
    if (controller.down())     { Serial.println("Down pressed"); }
    if (controller.left())     { Serial.println("Left pressed"); }
    if (controller.right())    { Serial.println("Right pressed"); }
    if (controller.start())    { Serial.println("Start pressed"); }
    if (controller.select())   { Serial.println("Select pressed"); }
    if (controller.l1())       { Serial.println("L1 pressed"); }
    if (controller.l2())       { Serial.println("L2 pressed"); }
    if (controller.l3())       { Serial.println("L3 pressed - left analog button"); }
    if (controller.r1())       { Serial.println("R1 pressed"); }
    if (controller.r2())       { Serial.println("R2 pressed"); }
    if (controller.r3())       { Serial.println("R3 pressed - right analog button"); }

    // Example: Print analog stick positions
    Serial.print("Left Analog Stick X (lx): ");
    Serial.println(controller.lx());
    Serial.print("Left Analog Stick Y (ly): ");
    Serial.println(controller.ly());
    Serial.print("Right Analog Stick X (rx): ");
    Serial.println(controller.rx());
    Serial.print("Right Analog Stick Y (ry): ");
    Serial.println(controller.ry());
  }
}

Task tRadioReceive(10, TASK_FOREVER, &loopTask, &runner, true);

void setup() {
  Serial.begin(115200);

  controller.init();

  Serial.println("PS2 Controller Initialized");
}

void loop() {
  runner.execute();
}
