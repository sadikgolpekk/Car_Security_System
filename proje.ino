#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 22);

// Pinler
const int motorButtonPin = 2;
const int kemerButtonPin = 3;
const int doorSwitchPin  = 13;
const int kapiLedPin     = A5;
const int ledKirmizi     = 4;
const int buzzer         = 5;

const int sicaklikPin    = A0;
const int isikPin        = A1;
const int yakitPin       = A2;
const int farLedPin      = A3;
const int yakitLedPin    = A4;

const int klimaMotorPin  = 6;
const int engineMotorPin = 7;

bool motorDurumu         = false;
bool motorEngellenmis    = false;  // Yakıt bitince motor engellenir

bool motorCalistiMesajiGosterildi = false;
bool farKapandiMesajiYazildi = false;


void setup() {
  pinMode(motorButtonPin, INPUT);
  pinMode(kemerButtonPin, INPUT);
  pinMode(doorSwitchPin, INPUT_PULLUP);

  pinMode(kapiLedPin, OUTPUT);
  pinMode(ledKirmizi, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(yakitLedPin, OUTPUT);
  pinMode(farLedPin, OUTPUT);
  pinMode(klimaMotorPin, OUTPUT);
  pinMode(engineMotorPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  if (digitalRead(doorSwitchPin) == HIGH) {
    motorDurumu = false;
    digitalWrite(engineMotorPin, LOW);
    digitalWrite(kapiLedPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Uyari: Kapi Acik");
    lcd.setCursor(0, 1);
    lcd.print("Motor calismaz");
    delay(300);
    return;
  }
  digitalWrite(kapiLedPin, LOW);

  if (digitalRead(kemerButtonPin) == LOW) {
    motorDurumu = false;
    digitalWrite(engineMotorPin, LOW);
    digitalWrite(ledKirmizi, HIGH);
    
     tone(buzzer, 440);
     delay(200);
     tone(buzzer, 1760);
     delay(200);
     noTone(buzzer);
    

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kemeri takiniz");
    lcd.setCursor(0, 1);
    lcd.print("Motor calismaz");
    delay(300);
    return;
  }
  digitalWrite(ledKirmizi, LOW);

  kontrolEtMotorButonu();
  kontrolEtSicaklik();
  kontrolEtFar();
  kontrolEtYakit();
}

void kontrolEtMotorButonu() {
  bool kemerTakili = digitalRead(kemerButtonPin) == HIGH;
  bool kapiKapali  = digitalRead(doorSwitchPin) == LOW;
  int  motorButon  = digitalRead(motorButtonPin);

  if (motorButon == HIGH && kemerTakili && kapiKapali && !motorEngellenmis) {
  if (!motorDurumu) {
    motorDurumu = true;
    digitalWrite(engineMotorPin, HIGH);
    if (!motorCalistiMesajiGosterildi) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor Calisti");
      delay(1000);
      motorCalistiMesajiGosterildi = true;
    }
  }
} else {
  if (motorDurumu) {
    motorDurumu = false;
    digitalWrite(engineMotorPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor Kapandi");
    delay(1000);
    motorCalistiMesajiGosterildi = false;
  }
}

}

void kontrolEtSicaklik() {
  if (!motorDurumu) {
    digitalWrite(klimaMotorPin, LOW);
    return;
  }

  float volts     = analogRead(sicaklikPin) * (5.0 / 1023.0);
  float sicaklik  = volts * 100.0;


  if (sicaklik > 25.0) {
    digitalWrite(klimaMotorPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik:");
    lcd.print((int)sicaklik);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Klima acildi");

    delay(800);
  } else {
    digitalWrite(klimaMotorPin, LOW);
    lcd.clear();
  }
  delay(500);
}

void kontrolEtFar() {
  if (!motorDurumu) return; // Motor çalışmıyorsa far kontrolü gereksiz

  int val = analogRead(isikPin);

  if (val <= 250) { 
    // Ortam karanlık, far açık
    digitalWrite(farLedPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Farlar Acik");

    // Farlar açıldıysa, kapalı mesaj bayrağını sıfırla
    farKapandiMesajiYazildi = false;

    delay(800);
  } 
  else { 
    // Ortam aydınlık, far kapalı
    digitalWrite(farLedPin, LOW);

    if (!farKapandiMesajiYazildi) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Farlar Kapandi");
      delay(800);
      farKapandiMesajiYazildi = true; // Tek sefer gösterildi
    }
  }

  delay(500);
}


void kontrolEtYakit() {
  int val   = analogRead(yakitPin);
  float pct = (val / 1023.0) * 100.0;

  lcd.clear();
  lcd.setCursor(0, 0);

  if (pct <= 0.0) {
    motorDurumu = false;
    motorEngellenmis = true;  
    digitalWrite(yakitLedPin, LOW);
    digitalWrite(engineMotorPin, LOW);
    digitalWrite(farLedPin, LOW);

    lcd.print("Yakit Bitti");
    lcd.setCursor(0, 1);
    lcd.print("Motor Durdu");
  } else if (pct < 5.0) {
     motorEngellenmis = false;  
    digitalWrite(yakitLedPin, millis() % 300 < 150);
    lcd.print("Kritik: Yakit Az");
    lcd.setCursor(0, 1);
    lcd.print("%"); lcd.print((int)pct);
    
    delay(800);
  } else if (pct < 10.0) {
     motorEngellenmis = false;  
    digitalWrite(yakitLedPin, HIGH);
    lcd.print("Uyari: Yakit Dusuk");
    lcd.setCursor(0, 1);
    lcd.print("%"); lcd.print((int)pct);

    
    delay(800);
  } else {
    digitalWrite(yakitLedPin, LOW);
    motorEngellenmis = false;  
  }

  delay(500);
}
