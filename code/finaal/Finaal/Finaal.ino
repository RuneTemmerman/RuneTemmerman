#include "SerialCommand.h"
#include "EEPROMAnything.h"
#include <EEPROM.h>
#include "BluetoothSerial.h"

#define motor1PWM1 13
#define motor1PWM2 14
#define motor2PWM1 16
#define motor2PWM2 17
#define Baudrate 115200

BluetoothSerial BTSerial;

void onSet();
void onDebug();
void onCalibrate();
void onUnknownCommand(char* command);
void onRun();
void onCmd();

SerialCommand sCmd(BTSerial);

bool run = false;
unsigned long previous, calculationTime;

const int sensor[] = {26, 25, 33, 32, 35, 34, 36};

struct param_t {
    unsigned long cycleTime = 2600;
    int black[7] = {0};
    int white[7] = {4095};
    int power = 100;
    float diff = 1.5;
    float kp = 0.2;
    float ki = 0.0005;
    float kd = 0.4;
} params;

int normalised[7];
float debugPosition;
float iTerm = 0, lastErr = 0;

#define EEPROM_SIZE sizeof(param_t)

void setup() 
{
    Serial.begin(Baudrate);
    BTSerial.begin("ESP32_Lijnvolger");  // Naam voor Bluetooth zichtbaar

    // Zet motoren standaard uit
    analogWrite(motor1PWM1, 0);
    analogWrite(motor1PWM2, 0);
    analogWrite(motor2PWM1, 0);
    analogWrite(motor2PWM2, 0);

    sCmd.addCommand("set", onSet);
    sCmd.addCommand("debug", onDebug);
    sCmd.addCommand("calibrate", onCalibrate);
    sCmd.addCommand("run", onRun);
    sCmd.addCommand("cmd", onCmd);
    sCmd.setDefaultHandler(onUnknownCommand);

    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(0, params);
    EEPROM.end();

    Serial.println("Bluetooth ready! Zoek ESP32_Lijnvolger via je gsm-app.");
}

void loop() {
    sCmd.readSerial();

    if (!run) {
        analogWrite(motor1PWM1, 0);
        analogWrite(motor1PWM2, 0);
        analogWrite(motor2PWM1, 0);
        analogWrite(motor2PWM2, 0);
        return;
    }

    unsigned long startCalculation = micros();
    float position = 0;
    unsigned long current = micros();

    if (current - previous >= params.cycleTime) previous = current;
    {
        for (int i = 0; i < 7; i++) {
            normalised[i] = map(analogRead(sensor[i]), params.black[i], params.white[i], 0, 1000);
        }

        int index = 0;
        for (int i = 1; i < 7; i++) if (normalised[i] < normalised[index]) index = i;

        if (index == 0) position = -30;
        else if (index == 6) position = 30;
        else {
            int sNul = normalised[index];
            int sMinEen = normalised[index - 1];
            int sPlusEen = normalised[index + 1];
            float b = sPlusEen - sMinEen;
            b = b / 2;
            float a = sPlusEen - b - sNul;
            position = -b / (2 * a);
            position += index;
            position -= 3;
            position *= 9.525;
        }

        debugPosition = position;

        float error = -position;
        float output = error * params.kp;
        iTerm += params.ki * error;
        iTerm = constrain(iTerm, -510, 510);
        output += iTerm;
        output += params.kd * (error - lastErr);
        lastErr = error;

        int powerLeft = 0;
        int powerRight = 0;

        output = constrain(output, -510, 510);
        if (run) {
            if (output >= 0) {
                powerLeft = constrain(params.power + params.diff * output, -255, 255);
                powerRight = constrain(powerLeft - output, -255, 255);
                powerLeft = powerRight + output;
            } else {
                powerRight = constrain(params.power - params.diff * output, -255, 255);
                powerLeft = constrain(powerRight + output, -255, 255);
                powerRight = powerLeft - output;
            }
        }

        analogWrite(motor1PWM1, powerLeft > 0 ? powerLeft : 0);
        analogWrite(motor1PWM2, powerLeft < 0 ? -powerLeft : 0);
        analogWrite(motor2PWM1, powerRight > 0 ? powerRight : 0);
        analogWrite(motor2PWM2, powerRight < 0 ? -powerRight : 0);
    }

    calculationTime = micros() - startCalculation;
}

void onSet() {
    char* parameter = sCmd.next();
    char* value = sCmd.next();

    if (strcmp(parameter, "cycle") == 0) {
        long newCycleTime = atol(value);
        float ratio = ((float)newCycleTime) / ((float)params.cycleTime);
        params.ki *= ratio;
        params.kd /= ratio;
        params.cycleTime = newCycleTime;
    } else if (strcmp(parameter, "power") == 0) {
        params.power = atol(value);
        BTSerial.print("Power set to: ");
        BTSerial.println(params.power);
    } else if (strcmp(parameter, "diff") == 0) params.diff = atof(value);
    else if (strcmp(parameter, "kp") == 0) params.kp = atof(value);
    else if (strcmp(parameter, "ki") == 0) {
        float cycleTimeInSec = ((float)params.cycleTime) / 1000000;
        params.ki = atof(value) * cycleTimeInSec;
    } else if (strcmp(parameter, "kd") == 0) {
        float cycleTimeInSec = ((float)params.cycleTime) / 1000000;
        params.kd = atof(value) / cycleTimeInSec;
    }

    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(0, params);
    EEPROM.commit();
    EEPROM.end();
}

void onDebug() {
    BTSerial.print("cycle time: ");
    BTSerial.println(params.cycleTime);
    BTSerial.print("power: ");
    BTSerial.println(params.power);
    BTSerial.print("kp: ");
    BTSerial.println(params.kp);
    BTSerial.print("ki: ");
    BTSerial.println(params.ki);
    BTSerial.print("kd: ");
    BTSerial.println(params.kd);
    BTSerial.print("Diff: ");
    BTSerial.println(params.diff);

    BTSerial.print("Calculation time (µs): ");
    BTSerial.println(calculationTime);

    BTSerial.println("Sensor readings:");
    for (int i = 0; i < 7; i++) {
        BTSerial.print("Sensor ");
        BTSerial.print(i);
        BTSerial.print(": ");
        BTSerial.println(analogRead(sensor[i]));
    }

    BTSerial.print("Normalised readings: ");
    for (int i = 0; i < 7; i++) {
        BTSerial.print(normalised[i]);
        if (i < 6) BTSerial.print(", ");
    }

    BTSerial.print("Position: ");
    BTSerial.println(debugPosition);
}

void onUnknownCommand(char* command) {
    BTSerial.print("unknown command: \"");
    BTSerial.print(command);
    BTSerial.println("\"");
}

void onCalibrate() {
    char* param = sCmd.next();
    if (strcmp(param, "black") == 0) {
        BTSerial.print("start calibration black...");
        for (int i = 0; i < 7; i++) params.black[i] = analogRead(sensor[i]);
        BTSerial.println("done");
    } else if (strcmp(param, "white") == 0) {
        BTSerial.print("start calibration white...");
        for (int i = 0; i < 7; i++) params.white[i] = analogRead(sensor[i]);
        BTSerial.println("done");
    }

    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(0, params);
    EEPROM.commit();
    EEPROM.end();
}

void onRun() {
    char* parameter = sCmd.next();
    if (strcmp(parameter, "on") == 0) {
        iTerm = 0;
        run = true;
    } else {
        run = false;
        analogWrite(motor1PWM1, 0);
        analogWrite(motor1PWM2, 0);
        analogWrite(motor2PWM1, 0);
        analogWrite(motor2PWM2, 0);
    }
}

void onCmd() {
    BTSerial.println("-------Possible commands:-------");
    BTSerial.println("calibrate white");
    BTSerial.println("calibrate black");
    BTSerial.println("set cycle 'x' (<10000 µs)");
    BTSerial.println("set power 'x' (0...255)");
    BTSerial.println("set diff 'x' (0...1)");
    BTSerial.println("set kp 'x'");
    BTSerial.println("set ki 'x'");
    BTSerial.println("set kd 'x'");
}