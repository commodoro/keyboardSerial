#include <CapacitiveSensor.h>

#define S 7

enum orderKeys
{
    UP = 0,
    DOWN,
    LEFT,
    RIGTH,
    A,
    B,
    START,
    SELECT
};
CapacitiveSensor *sens[8];
bool keyStates[8] = {false};
const uint8_t pinSend = 2, pinRec = 3;
const uint32_t umbral = 800;

void setup()
{
    for (auto i = 0; i < S; i++)
    {
        sens[i] = new CapacitiveSensor(pinSend, pinRec + i);
        sens[i]->set_CS_AutocaL_Millis(0xFFFFFFFF); 
    }

    pinMode(12, INPUT_PULLUP); // EMERGENCY/SECURITY;
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    uint32_t data;
    for (auto i = 0; i < S; i++)
    {
        data = sens[i]->capacitiveSensor(20);
        // Serial.print(i);
        // Serial.print(" - ");
        // Serial.println(data);
        if (data > umbral)
        {
            switch (i)
            {
            case UP:
                if (!keyStates[i])
                {
                    Serial.print("^");
                    keyStates[i] = true;
                };
                break;
            case DOWN:
                if (!keyStates[i])
                {
                    Serial.print("_");
                    keyStates[i] = true;
                };
                break;
            case LEFT:
                if (!keyStates[i])
                {
                    Serial.print("{");
                    keyStates[i] = true;
                };
                break;
            case RIGTH:
                if (!keyStates[i])
                {
                    Serial.print("}");
                    keyStates[i] = true;
                };
                break;
            case A:
                if (!keyStates[i])
                {
                    Serial.print("a");
                    keyStates[i] = true;
                };
                break;
            case B:
                if (!keyStates[i])
                {
                    Serial.print("b");
                    keyStates[i] = true;
                };
                break;
            case SELECT:
                if (!keyStates[i])
                {
                    Serial.print("[");
                    keyStates[i] = true;
                };
                break;
            case START:
                if (!keyStates[i])
                {
                    Serial.print("#");
                    keyStates[i] = true;
                };
                break;
            }
        }
        else
        {
            switch (i)
            {
            case UP:
                if (keyStates[i])
                {
                    Serial.print("^");
                    keyStates[i] = false;
                };
                break;
            case DOWN:
                if (keyStates[i])
                {
                    Serial.print("_");
                    keyStates[i] = false;
                };
                break;
            case LEFT:
                if (keyStates[i])
                {
                    Serial.print("{");
                    keyStates[i] = false;
                };
                break;
            case RIGTH:
                if (keyStates[i])
                {
                    Serial.print("}");
                    keyStates[i] = false;
                };
                break;
            case A:
                if (keyStates[i])
                {
                    Serial.print("A");
                    keyStates[i] = false;
                };
                break;
            case B:
                if (keyStates[i])
                {
                    Serial.print("B");
                    keyStates[i] = false;
                };
                break;
            case SELECT:
                if (keyStates[i])
                {
                    Serial.print("[");
                    keyStates[i] = false;
                };
                break;
            case START:
                if (keyStates[i])
                {
                    Serial.print("#");
                    keyStates[i] = false;
                };
                break;
            }
        }
    }
}
