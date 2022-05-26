#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>
#define S1 100
#define S2 100
#define distance 50

const int TRIG1 = 6; //超音波センサ1(右側)TRIGに接続するピン番号
const int ECHO1 = 7; //超音波センサ1(右側)ECHOに接続するピン番号
const int TRIG2 = 4; //超音波センサ2(左側)TRIGに接続するピン番号
const int ECHO2 = 5; //超音波センサ2(左側)ECHOに接続するピン番号
int counter_all = 0;    //通過した人数を数える
int counter_RtoL = 0; //右から左に通過した人数を計測
int counter_LtoR = 0; //左から右に通過した人数を計測
int buzzer = 12;    //ブザーにつなぐピン番号
unsigned long   time_hcsr04_1; //センサ1の時間を計測
unsigned long   time_hcsr04_2; //センサ2の時間を計測
HCSR04 hcsr04_1( TRIG1, ECHO1 );
HCSR04 hcsr04_2( TRIG2, ECHO2 );
int j = 0;
int k = 0;
long a=0;
long b=0;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  hcsr04_1.begin();
  hcsr04_2.begin();
  Serial.begin( 9600 );
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("No one goes");
  lcd.setCursor(0, 1);
  lcd.print("through");
}

void loop() {

  float distance1 = hcsr04_1.get_length(); //センサ１(右側)と物の距離を測定
  float distance2 = hcsr04_2.get_length(); //センサ２(左側)と物の距離を測定
  time_hcsr04_1 = millis();
  time_hcsr04_2 = millis();
  int i = 0;
  long  time_memory_1[S1];
  long  time_memory_2[S2];
  

  for (i = 0; i <= S1 - 1; i++) {
    time_memory_1[i] = 0;
    time_memory_2[i] = 0;
  }

  if (distance1 <= 20 && distance1 >= 1) {
    time_memory_1[j] = time_hcsr04_1;
    j ++;
    delay(3);
  }
  if (time_memory_1[0]> 1) {
    a=time_memory_1[0];
     Serial.print("センサ１の距離：");
    Serial.println(distance1);
    Serial.print("センサ１を通過した時間：");
    Serial.println(time_memory_1[0]);
  }

  if (distance2 <= 20 && distance2 >=1) {
    time_memory_2[k] = time_hcsr04_2;
    k++;
    delay(3);
  }

  if (time_memory_2[0] > 1) {
    b=time_memory_2[0];
    Serial.print("センサ2の距離：");
    Serial.println(distance2);
    Serial.print("センサ2を通過した時間：");
    Serial.println(time_memory_2[0]);
  }

 
  while ((a>1 && (time_hcsr04_1-a) >= 3000) || ((b>1) && (time_hcsr04_2-b) >= 3000)) {
   Serial.println("リセットしました");
    Serial.println("**************************************************");
    lcd.setCursor(0, 0);
    lcd.print("It`s reseted      ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
     digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(2500);
     lcd.setCursor(0, 0);
    lcd.print(counter_all);
    lcd.print("  pepople pass");
    lcd.setCursor(0, 1);
    lcd.print("RtoL:");
    lcd.print(counter_RtoL);
    lcd.print("  ");
    lcd.print("LtoR:");
    lcd.print(counter_LtoR);
    j=0;
    k=0;
    a=0;
    b=0;
    for (j = 0; j <= S1 - 1; j++) {
    time_memory_1[j] = 0;
    time_memory_2[j] = 0;
  }
  j=0;
    break;
  }

    
  while ( (a > 1) && (b > 1) && (abs(a-b) < 3000) ) {
     if( (a > 1) && (b > 1) ) {
   if ( a < b) {
      counter_RtoL++;
    } else {
      counter_LtoR++;
    }
 }
    counter_all++ ;
    Serial.print("人が通りました。今まで通った人数は");
    Serial.print(counter_all);
    Serial.println("人です。");
    Serial.print("今まで右から左に通った人数は");
    Serial.print(counter_RtoL);
    Serial.println("人です。");
    Serial.print("今まで左から右に通った人数は");
    Serial.print(counter_LtoR);
    Serial.println("人です。");
    Serial.println("**************************************************");
  
    lcd.setCursor(0, 0);
    lcd.print(counter_all);
    lcd.print("  pepople pass");
    lcd.setCursor(0, 1);
    lcd.print("RtoL:");
    lcd.print(counter_RtoL);
    lcd.print("  ");
    lcd.print("LtoR:");
    lcd.print(counter_LtoR);

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    j=0;
    k=0;
    a=0;
    b=0;
    for (j = 0; j <= S1 - 1; j++) {
    time_memory_1[j] = 0;
    time_memory_2[j] = 0;
  }
  j=0;
  delay(2000);
    break;
  }

}
