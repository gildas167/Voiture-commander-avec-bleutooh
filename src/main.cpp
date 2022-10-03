/**
*  VOITURE MOTORISER COMMANDER AVEC APPLICATION MOBILE VIA BLEUTOOH
*
*  @author TIA (Tech It All Engeneering and Services)
*  @version 1.1
*  @copyright 2022
*
*/
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3);
// Motor connections
int motor_en = 9;
int motor_in1 = 11;
int motor_in2 = 12;

int motor_en1 = 10;
int motor_in11 = 6;
int motor_in21 = 5;

uint16_t NA;

int s;

String command = " ";

void setup()
{
  // Set all the motor control pins to outputs
  pinMode(motor_en, OUTPUT);
  pinMode(motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);

  pinMode(motor_en1, OUTPUT);
  pinMode(motor_in11, OUTPUT);
  pinMode(motor_in21, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);
  digitalWrite(motor_in11, LOW);
  digitalWrite(motor_in21, LOW);

  Serial.begin(9600);
  bt.begin(9600);
}
void speed(int s)
{
  // Set motor to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(motor_en, s);
  analogWrite(motor_en1, s);
  return;
}

void turn_left()
{
  // TOURNE A GAUCHE

  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
  digitalWrite(motor_in11, LOW);
  digitalWrite(motor_in21, HIGH);
}

void turn_right()
{
  // TOURNE A DROITE

  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in11, HIGH);
  digitalWrite(motor_in21, LOW);
}

void stop()
{
  // STOP
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);
  digitalWrite(motor_in11, LOW);
  digitalWrite(motor_in21, LOW);
}

void go()
{
  // AVANCER

  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in11, LOW);
  digitalWrite(motor_in21, HIGH);
}

void move_back()
{
  // RECULER
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
  digitalWrite(motor_in11, HIGH);
  digitalWrite(motor_in21, LOW);
}

// Efface les données 
void string_clear(String a)
{

  while (a != " ")
  {
    a = " ";
  }
}

void loop()
{
  if (bt.available())
  {
    command = bt.readString();
    Serial.println(command);
    // convertion des trois premières caractères reçus en int
    uint8_t v = atoi(command.substring(0, 3).c_str());
    //Reception de la direction 
    String c = command.substring(3, 4);
    // Définition de la vitesse 
    speed(v);
    string_clear(command);

    if (c == "a")
    {
      go();
      string_clear(command);
    }

    if (c == "g")
    {
      turn_left();
      string_clear(command);
    }

    if (c == "d")
    {
      turn_right();
      string_clear(command);
    }

    if (c == "s")
    {
      stop();
      string_clear(command);
    }

    if (c == "r")
    {
      move_back();
      string_clear(command);
    }
  }
}