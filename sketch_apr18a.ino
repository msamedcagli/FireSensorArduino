#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 16x2 I2C

int buzzerPin = 9;

// Sensör pinleri
int gazPin = A0;
int sicaklikPin = A1;

// Ölçüm değerleri
int gazdeger;
int sensorDeger;
float sicaklik;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistem Basladi");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Gaz ve sıcaklık verilerini oku
  gazdeger = analogRead(gazPin);
  sensorDeger = analogRead(sicaklikPin);
  
  // Sıcaklık hesapla (LM35 için)
  sicaklik = (sensorDeger * 5.0 / 1024.0) * 100.0;

  // LCD yazdır
  lcd.setCursor(0, 0);
  lcd.print("Gaz: ");
  lcd.print(gazdeger);
  lcd.print("   "); // Temizleme için

  lcd.setCursor(0, 1);
  lcd.print("Sic: ");
  lcd.print(sicaklik);
  lcd.print(" C ");

  // Seri monitör yazdır (isteğe bağlı)
  Serial.print("Gaz: ");
  Serial.print(gazdeger);
  Serial.print("  Sicaklik: ");
  Serial.println(sicaklik);

  // Buzzer kontrol: sıcaklık > 60 veya gaz > 150 ise öt
  if (sicaklik > 55 || gazdeger > 350) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else {
    digitalWrite(buzzerPin, LOW);
    delay(200); // Stabilite için
  }
}
