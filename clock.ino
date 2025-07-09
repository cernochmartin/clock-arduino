#include "LiquidCrystal.h"

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int cs = 9;
const int contrast = 100;
int h = 12;
int m = 59;
int s = 45;
int flag = 1;
const int led1 = 11;
const int led2 = 12;
const int alarmHour = 7;
const int alarmMinute = 0;
bool alarmActive = false;
uint32_t alarmStartMillis = 0;
int button1;
int button2;
int hs = 0;
int ms = 1;
const int Time_light = 150;
int bl_TO = Time_light;
int bl = 10;
const int backlight = 120;
static uint32_t last_time, now = 0;

void setup()
{
    lcd.begin(16, 2);
    pinMode(hs, INPUT_PULLUP);
    pinMode(ms, INPUT_PULLUP);
    analogWrite(cs, contrast);
    analogWrite(bl, backlight);
    now = millis();

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
}

void loop()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Time ");
    if (h < 10)
        lcd.print("0");
    lcd.print(h);
    lcd.print(":");
    if (m < 10)
        lcd.print("0");
    lcd.print(m);
    lcd.print(":");
    if (s < 10)
        lcd.print("0");
    lcd.print(s);
    if (flag == 0)
        lcd.print(" AM");
    if (flag == 1)
        lcd.print(" PM");
    lcd.setCursor(0, 1);
    lcd.print("Arduino Clock!");

    for (int i = 0; i < 5; i++)
    {
        while ((now - last_time) < 200)
        {
            now = millis();
        }

        last_time = now;

        button1 = digitalRead(hs);
        button2 = digitalRead(ms);

        if (((button1 == 0) | (button2 == 0)) & (bl_TO == 1))
        {
            bl_TO = Time_light;
            analogWrite(bl, backlight);
            while ((button1 == 0) | (button2 == 0))
            {
                button1 = digitalRead(hs);
                button2 = digitalRead(ms);
            }
        }
        else
        {
            if (button1 == 0)
            {
                h = h + 1;
                bl_TO = Time_light;
                analogWrite(bl, backlight);
            }

            if (button2 == 0)
            {
                s = 0;
                m = m + 1;
                bl_TO = Time_light;
                analogWrite(bl, backlight);
            }

            if (s == 60)
            {
                s = 0;
                m = m + 1;
            }
            if (m == 60)
            {
                m = 0;
                h = h + 1;
            }
            if (h == 13)
            {
                h = 1;
                flag = flag + 1;
                if (flag == 2)
                    flag = 0;
            }

            if ((button1 == 0) | (button2 == 0))
            {
                lcd.setCursor(0, 0);
                lcd.print("Time ");
                if (h < 10)
                    lcd.print("0");
                lcd.print(h);
                lcd.print(":");
                if (m < 10)
                    lcd.print("0");
                lcd.print(m);
                lcd.print(":");
                if (s < 10)
                    lcd.print("0");
                lcd.print(s);

                if (flag == 0)
                    lcd.print(" AM");
                if (flag == 1)
                    lcd.print(" PM");

                lcd.setCursor(0, 1);
                lcd.print("Arduino Clock!");
            }
        }

        if (h == alarmHour && m == alarmMinute && s == 0 && !alarmActive)
        {
            alarmActive = true;
            alarmStartMillis = millis();
        }

        if (alarmActive)
        {
            if ((millis() / 250) % 2 == 0)
            {
                digitalWrite(led1, HIGH);
                digitalWrite(led2, LOW);
            }
            else
            {
                digitalWrite(led1, LOW);
                digitalWrite(led2, HIGH);
            }
            if (millis() - alarmStartMillis >= 60000)
            {
                digitalWrite(led1, LOW);
                digitalWrite(led2, LOW);
                alarmActive = false;
            }
        }
    }
    s = s + 1;

    if (s == 60)
    {
        s = 0;
        m = m + 1;
    }
    if (m == 60)
    {
        m = 0;
        h = h + 1;
    }
    if (h == 13)
    {
        h = 1;
        flag = flag + 1;
        if (flag == 2)
            flag = 0;
    }
}