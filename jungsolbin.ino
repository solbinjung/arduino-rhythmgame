#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int randNumber;

int score = 0;

const int btn1 = 8;
const int btn2 = 9;
const int btn3 = 10;

byte play00[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte play01[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte play02[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
};
byte play03[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();

  lcd.createChar(0, play00);
  lcd.createChar(1, play01);
  lcd.createChar(2, play02);
  lcd.createChar(3, play03);

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
}
void loop() {
  lcd.setCursor(6, 0);
  lcd.print("SCORE:");
  lcd.print(score);

  lcd.setCursor(1, 1);
  lcd.write(3);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(3, 1);
  lcd.write(3);

  for (int i = 1; i <= 24; i++) {
    randNumber = random(1, 4);
    int j = randNumber;

    lcd.setCursor(j, 0);
    lcd.write(1);
    lcd.setCursor(j, 1);
    lcd.write(3);
    delay(400);
    lcd.setCursor(j, 0);
    lcd.write(0);
    lcd.setCursor(j, 1);
    lcd.write(2);
    delay(400);
    lcd.setCursor(j, 0);
    lcd.write(0);
    lcd.setCursor(j, 1);
    lcd.write(3);
    delay(400);

    Serial.print("j=");
    Serial.println(j);

    if (j == 1 && digitalRead(btn1) == HIGH) {
      Serial.println(" 1번 버튼 누름");
      score += 10;
    } else if (j == 2 && digitalRead(btn2) == HIGH) {
      Serial.println("2번 버튼 누름");
      score += 10;
    } else if (j == 3 && digitalRead(btn3) == HIGH) {
      Serial.println("3번 버튼 누름");
      score += 10;
    }
    lcd.setCursor(12, 0);
    lcd.print(score);

    Serial.print("score:");
    Serial.println(score);
    Serial.println("--------------");
  }
  if (score >= 100) {
    lcd.setCursor(6, 1);
    lcd.print("Great!");
  } else {
    lcd.setCursor(6, 1);
    lcd.print("Fail..");
  }
  delay(50000);
}