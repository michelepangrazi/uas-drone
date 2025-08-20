#include <Adafruit_SSD1306.h>
 
#define OLED_I2C_ADDRESS 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define INPUT_PIN A0

int buttonPin = 7;
 
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT);
 
void setup() {
  pinMode(buttonPin, INPUT);
  
  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    while (true);
  }
  oled.clearDisplay();
}
 
void loop() {
  homepage();
  oled.display();
  
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    buttonPressed();
    oled.display();
    delay(2000);
  }
}

void homepage(){
  startHeaderScreen();
  startScreen();
}

void buttonPressed(){
  oled.fillRect(0, 16, 128, 48, BLACK);
  oled.setTextSize(2);
  oled.setCursor(OLED_WIDTH / 2, OLED_HEIGHT / 2 + 8);
  printCenteredText("OK Button");
}

void startScreen(){
  oled.fillRect(0, 16, 128, 48, BLACK);
  oled.setTextSize(2);
  oled.setCursor(OLED_WIDTH / 2, OLED_HEIGHT / 2 + 8);
  printCenteredText("Press Button");
}

void startHeaderScreen(){
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(4, 4);
  oled.print("Sensor checker");
  oled.drawLine(0, 15, 128, 15, WHITE);
}
 
void printCenteredText(String text) {
  int16_t x = 0, y = 0;
  uint16_t w = 0, h = 0;
  int16_t cursorX = oled.getCursorX();
  int16_t cursorY = oled.getCursorY();
  oled.getTextBounds(text, 0, 0, &x, &y, &w, &h);
  oled.setCursor(cursorX - x - w / 2, cursorY - y - h / 2);
  oled.print(text);
}


/*
  GPS 
*/


// #include <TinyGPS++.h>
// #include <SoftwareSerial.h>
// /*
//    This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
//    It requires the use of SoftwareSerial, and assumes that you have a
//    4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
// */
// static const int RXPin = 3, TXPin = 4;
// static const uint32_t GPSBaud = 9600;

// // The TinyGPS++ object
// TinyGPSPlus gps;

// // The serial connection to the GPS device
// SoftwareSerial ss(RXPin, TXPin);

// void setup()
// {
//   Serial.begin(9600);
//   ss.begin(GPSBaud);

//   Serial.println(F("DeviceExample.ino"));
//   Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
//   Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
//   Serial.println(F("by Mikal Hart"));
//   Serial.println();
// }

// void loop()
// {
//   // This sketch displays information every time a new sentence is correctly encoded.
//   while (ss.available() > 0)
//     if (gps.encode(ss.read()))
//       displayBaseInfo();

//   if (millis() > 5000 && gps.charsProcessed() < 10)
//   {
//     Serial.println(F("No GPS detected: check wiring."));
//     while(true);
//   }
// }

// void displayBaseInfo(){
//   Serial.println("Satellite Count:");
//   Serial.println(gps.satellites.value());
//   Serial.println("Latitude:");
//   Serial.println(gps.location.lat(), 6);
//   Serial.println("Longitude:");
//   Serial.println(gps.location.lng(), 6);
//   Serial.println("Speed MPH:");
//   Serial.println(gps.speed.mph());
//   Serial.println("Altitude Feet:");
//   Serial.println(gps.altitude.feet());
//   Serial.println("");
// }

// void displayInfo()
// {
//   Serial.print(F("Location: ")); 
//   if (gps.location.isValid())
//   {
//     Serial.print(gps.location.lat(), 6);
//     Serial.print(F(","));
//     Serial.print(gps.location.lng(), 6);
//   }
//   else
//   {
//     Serial.print(F("INVALID"));
//   }

//   Serial.print(F("  Date/Time: "));
//   if (gps.date.isValid())
//   {
//     Serial.print(gps.date.month());
//     Serial.print(F("/"));
//     Serial.print(gps.date.day());
//     Serial.print(F("/"));
//     Serial.print(gps.date.year());
//   }
//   else
//   {
//     Serial.print(F("INVALID"));
//   }

//   Serial.print(F(" "));
//   if (gps.time.isValid())
//   {
//     if (gps.time.hour() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.hour());
//     Serial.print(F(":"));
//     if (gps.time.minute() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.minute());
//     Serial.print(F(":"));
//     if (gps.time.second() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.second());
//     Serial.print(F("."));
//     if (gps.time.centisecond() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.centisecond());
//   }
//   else
//   {
//     Serial.print(F("INVALID"));
//   }

//   Serial.println();
// }





/*
  MPU 6050
*/

// Basic demo for accelerometer readings from Adafruit MPU6050

// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <Wire.h>

// Adafruit_MPU6050 mpu;

// void setup(void) {
//   Serial.begin(115200);
//   while (!Serial)
//     delay(10); // will pause Zero, Leonardo, etc until serial console opens

//   Serial.println("Adafruit MPU6050 test!");

//   // Try to initialize!
//   if (!mpu.begin()) {
//     Serial.println("Failed to find MPU6050 chip");
//     while (1) {
//       delay(10);
//     }
//   }
//   Serial.println("MPU6050 Found!");

//   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
//   Serial.print("Accelerometer range set to: ");
//   switch (mpu.getAccelerometerRange()) {
//   case MPU6050_RANGE_2_G:
//     Serial.println("+-2G");
//     break;
//   case MPU6050_RANGE_4_G:
//     Serial.println("+-4G");
//     break;
//   case MPU6050_RANGE_8_G:
//     Serial.println("+-8G");
//     break;
//   case MPU6050_RANGE_16_G:
//     Serial.println("+-16G");
//     break;
//   }
//   mpu.setGyroRange(MPU6050_RANGE_500_DEG);
//   Serial.print("Gyro range set to: ");
//   switch (mpu.getGyroRange()) {
//   case MPU6050_RANGE_250_DEG:
//     Serial.println("+- 250 deg/s");
//     break;
//   case MPU6050_RANGE_500_DEG:
//     Serial.println("+- 500 deg/s");
//     break;
//   case MPU6050_RANGE_1000_DEG:
//     Serial.println("+- 1000 deg/s");
//     break;
//   case MPU6050_RANGE_2000_DEG:
//     Serial.println("+- 2000 deg/s");
//     break;
//   }

//   mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
//   Serial.print("Filter bandwidth set to: ");
//   switch (mpu.getFilterBandwidth()) {
//   case MPU6050_BAND_260_HZ:
//     Serial.println("260 Hz");
//     break;
//   case MPU6050_BAND_184_HZ:
//     Serial.println("184 Hz");
//     break;
//   case MPU6050_BAND_94_HZ:
//     Serial.println("94 Hz");
//     break;
//   case MPU6050_BAND_44_HZ:
//     Serial.println("44 Hz");
//     break;
//   case MPU6050_BAND_21_HZ:
//     Serial.println("21 Hz");
//     break;
//   case MPU6050_BAND_10_HZ:
//     Serial.println("10 Hz");
//     break;
//   case MPU6050_BAND_5_HZ:
//     Serial.println("5 Hz");
//     break;
//   }

//   Serial.println("");
//   delay(100);
// }

// void loop() {

//   /* Get new sensor events with the readings */
//   sensors_event_t a, g, temp;
//   mpu.getEvent(&a, &g, &temp);

//   /* Print out the values */
//   Serial.print("Acceleration X: ");
//   Serial.print(a.acceleration.x);
//   Serial.print(", Y: ");
//   Serial.print(a.acceleration.y);
//   Serial.print(", Z: ");
//   Serial.print(a.acceleration.z);
//   Serial.println(" m/s^2");

//   Serial.print("Rotation X: ");
//   Serial.print(g.gyro.x);
//   Serial.print(", Y: ");
//   Serial.print(g.gyro.y);
//   Serial.print(", Z: ");
//   Serial.print(g.gyro.z);
//   Serial.println(" rad/s");

//   Serial.print("Temperature: ");
//   Serial.print(temp.temperature);
//   Serial.println(" degC");

//   Serial.println("");
//   delay(500);
// }