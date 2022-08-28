#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// ultrasonic
#define triggerPin A0
#define echoPin A1
#define maxDistance 200
#define collisionDistance 45
NewPing sonar(triggerPin, echoPin, maxDistance);
int currentDistance = 0;
int leftDistance = 0;
int rightDistance = 0;

// DC Motor
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// servo
Servo servo;

void moveForward()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}
void moveBackward()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}
void turnLeft()
{
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    delay(770);
}
void turnRight()
{
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    delay(770);
}

void turnAround()
{
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    delay(1600);
}

void releaseMotors()
{

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void setMotorSpeed(int maxSpeed)
{

    motor1.setSpeed(maxSpeed);
    motor2.setSpeed(maxSpeed);
    motor3.setSpeed(maxSpeed);
    motor4.setSpeed(maxSpeed);
}

// distance function
int getDistance()
{
    delay(70);
    unsigned int uS = sonar.ping();
    int cm = uS / US_ROUNDTRIP_CM;
    return cm;
}

void changeDirection()
{
    releaseMotors();
    servo.write(180);
    delay(400);
    leftDistance = getDistance();
    servo.write(0);
    delay(400);
    rightDistance = getDistance();
    servo.write(90);
    compareDistance();
}

void compareDistance()
{
    if (leftDistance >= rightDistance)
    {
        turnLeft();
        moveForward();
    }
    else
    {
        turnRight();
        moveForward();
    }
}

void setup()
{
    servo.attach(10);
    setMotorSpeed(200);
    servo.write(90);
    delay(1000);
}

void loop()
{
    servo.write(90);
    delay(200);
    currentDistance = getDistance();
    if (currentDistance <= collisionDistance)
    {
        changeDirection();
        return;
    }

    moveForward();
}