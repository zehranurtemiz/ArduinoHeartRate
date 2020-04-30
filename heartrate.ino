/*  PulseSensor kütüphanesi kullanılarak dakikadaki atım sayısı LCD ekran üzerinde görüntülenir. */

#include<LiquidCrystal.h> // LCD ekran kütüphanesi

#define USE_ARDUINO_INTERRUPTS true // kısa süreli kesinti tanımlanır
#include <PulseSensorPlayground.h>  // Pulse Sensör kütüphanesi   

// değişkenler
const int PulseWire = 0;   // Pulse Sensörünün Mor Kablosu ANALOG PIN 0’a bağlanır.
const int LED13 = 13;      // Kırmızı LED, PIN 13’e bağlanır.
int Threshold = 550;       // Hangi sinyal seviyesinden itibaren kalp atımı olarak kabul edileceğine karar vermek için bir eşik değeri tanımlanır. 
                         
PulseSensorPlayground pulseSensor;   // PulseSensor kütüphanesinde bulunan fonksiyonları kullanabilmek için bir nesne oluşturulur.    

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup() {   
  Serial.begin(9600);  // Serial monitör için başlangıç değeri tanımlanır.
  lcd.begin(16,2);     // LCD ekranın boyutları tanımlanır.
  
  // PulseSensor nesnesine değerler atanır. 
  pulseSensor.analogInput(PulseWire); 
  pulseSensor.blinkOnPulse(LED13); // Kırmızı LED her kalp atımında yanıp söner.
  pulseSensor.setThreshold(Threshold); // Eşik değeri atanır. 

  // PulseSensor nesnesinin oluşturuluğunu ve değerlerin doğru şekilde atandığını kontrol etmek için LCD ekranda bilgilendirme yapılır.
  if (pulseSensor.begin()) {
    // LCD ekranda bir kere görüntülenir.
    Serial.println("Sensör basariyla çalistirildi.");      
    lcd.setCursor(0,0);  // LCD ekranın imleç yeri tanımlanır.
    lcd.print("NABIZ OLCULUYOR");  // Ekrana “NABIZ OLCULUYOR” yazdırılır.
  } 
}

void loop() {
  // pulseSensor nesnesindeki kalp atış hızını integer olarak döndüren fonksiyonu çağırır. Kalp atış hızı "nabiz" değişkenine aktarılır.
  int nabiz = pulseSensor.getBeatsPerMinute(); 
  // Kalp atışının gerçekleşip gerçekleşmediğini kontrol eder. Eğer sensöre gelen sinyal belirlenen eşiğin üzerinde ise kalp atışı gerçekleşmiş kabul edilir ve “true” döndürülür.

  if (pulseSensor.sawStartOfBeat()) {     
    Serial.println("Nabiz tespit edildi! "); 
    // Sensöre gelen sinyal eşik değerinin üzerinde ise ise çıktı olarak "nabiz tespit edildi" yazdırılır. 

    Serial.print("NABIZ: ");  // Output’a “NABIZ: “ yazdırılır.
    Serial.println(nabiz);    // “nabiz” değişkenindeki değer çıktıya yazdırılır. 
    lcd.setCursor(0,2); 
    lcd.setCursor(3,3); 
    lcd.print(" NABIZ: ");    // Ekrana “ NABIZ: “ yazdırılır." 
    lcd.print(nabiz);         // Nabız ekrana yazdırılır.
    lcd.clear();
  } 
  delay(20);    // döngü yeniden çalıştırılmadan önce 20 milisaniye beklenir.
}
