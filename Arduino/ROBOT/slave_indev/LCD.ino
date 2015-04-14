#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 23, 22, 21, 20);

void setupLCD() {
    lcd.begin(16, 2);
}

void printLCD(String x) {
    lcd.print(x);
}

void clear() {
    lcd.clear();
}
