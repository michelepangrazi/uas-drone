#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_BMP085_U.h>

// Display OLED
#define OLED_I2C_ADDRESS 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT);

// Pulsante
#define BUTTON_PIN 7

// GY68
Adafruit_BMP085_Unified bmp;

// GY271
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// GPS
static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

// MPU6050
Adafruit_MPU6050 mpu;

// Stati del sistema
enum ScreenState { HOMEPAGE, GPS_SCREEN, MPU6050_SCREEN, GY68_SCREEN, GY271_SCREEN};
ScreenState currentScreen = HOMEPAGE;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(115200);

  // Setup OLED Display
  if (oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("OLED Display initialized");
    oled.clearDisplay();
  }else{
    Serial.println("Ooops, no OLED display detected ... Check your wiring!");
    while (true);
  }
  
  // Setup GPS
  ss.begin(GPSBaud);
  Serial.println("GPS initialized");

  // Setup MPU6050
  if (mpu.begin()) {
    Serial.println("MPU6050 initialized");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }else{
    Serial.println("Ooops, no MPU6050 detected ... Check your wiring!");
    while(true);
  }
  
  // Setup GY68
  // if (bmp.begin()) {
  //   Serial.println("GY68 initialized");
  // }else{
  //   Serial.println("Ooops, no GY68 detected ... Check your wiring!");
  //   while (true);
  // }

  // Setup GY271
  // if(mag.begin()){
  //   Serial.println("GY271 initialized!");
  // }else{
  //   Serial.println("Ooops, no GY271 detected ... Check your wiring!");
  //   while(true);
  // }

}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    delay(300);  // Debounce
    switchScreen();
  }
  switch (currentScreen) {
    case HOMEPAGE:
      homepage();
      oled.display();
      break;
    case GPS_SCREEN:
      showGPSData();
      oled.display();
      break;
    case MPU6050_SCREEN:
      showMPUData();
      oled.display();
      break;
    case GY68_SCREEN:
      showGY68Data();
      oled.display();
      break;
    case GY271_SCREEN:
      showGY271Data();
      oled.display();
      break;
  }
}

void printHeaderScreen(String text){
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(4, 4);
  oled.print(text);
  oled.drawLine(0, 15, 128, 15, WHITE);
}

// Home page
void homepage(){
  printHeaderScreen("Sensor checker v1.0");
  oled.fillRect(0, 16, 128, 48, BLACK);
  oled.setTextSize(1);
  oled.setCursor(0,20);
  oled.println("1 - GPS sensor");
  oled.setCursor(0,30);
  oled.println("2 - MPU sensor");
  oled.setCursor(0,40);
  oled.println("3 - GY68 sensor");
  oled.setCursor(0,50);
  oled.println("4 - GY271 sensor");
}

void switchScreen() {
  currentScreen = (ScreenState)((currentScreen + 1) % 5);
  oled.clearDisplay();
}

// GPS page
void showGPSData() {
  oled.clearDisplay();
  printHeaderScreen("GPS sensor");

  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  boolean test_screen = false;
  
  if (gps.location.isValid()) {
    oled.setCursor(0, 20);
    oled.print("Lat: ");
    oled.println(gps.location.lat(), 6);
    oled.setCursor(0, 30);
    oled.print("Lng: ");
    oled.println(gps.location.lng(), 6);
    oled.setCursor(0, 40);
    oled.print("Sat: ");
    oled.println(gps.satellites.value(), 6);
    oled.setCursor(0, 50);
    oled.print("Alt: ");
    oled.println(gps.altitude.meters(), 6);
  }
  else if (test_screen) {
    oled.setCursor(0, 20);
    oled.print("Lat: ");
    oled.println(42.12345);
    oled.setCursor(0, 30);
    oled.print("Lng: ");
    oled.println("12.1343");
    oled.setCursor(0, 40);
    oled.print("Sat: ");
    oled.println("13");
    oled.setCursor(0, 50);
    oled.print("Alt: ");
    oled.println("203");
  }else {
    oled.setCursor(30, 30);
    oled.println("No GPS data");
  }
}

// MPU6050 page
void showMPUData() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  oled.clearDisplay();
  printHeaderScreen("MPU6050 sensor");

  oled.setCursor(0, 20);
  oled.print("Acc X: ");
  oled.println(a.acceleration.x);
  oled.print("Acc Y: ");
  oled.println(a.acceleration.y);
  oled.print("Acc Z: ");
  oled.println(a.acceleration.z);

  oled.setCursor(0, 55);
  oled.print("Temp: ");
  oled.print(temp.temperature);
  oled.println(" C");
}

// GY68 page
void showGY68Data() {
  oled.clearDisplay();
  printHeaderScreen("GY68 sensor");
}

// GY271 page
void showGY271Data() {
  oled.clearDisplay();
  printHeaderScreen("GY271 sensor");
  // sensors_event_t event; 
  // mag.getEvent(&event);
  // oled.setCursor(0, 20);
  // oled.print("X: "); oled.print(event.magnetic.x); oled.println("");
  // oled.print("Y: "); oled.print(event.magnetic.y); oled.println("");
  // oled.print("Z: "); oled.print(event.magnetic.z); oled.println("");
  // float heading = atan2(event.magnetic.y, event.magnetic.x);
  // float declinationAngle = 0.22;
  // heading += declinationAngle;
  // if(heading < 0)
  //   heading += 2*PI;
  // if(heading > 2*PI)
  //   heading -= 2*PI;
  // float headingDegrees = heading * 180/M_PI; 
  // oled.print("Heading (degrees): "); oled.println(headingDegrees);
}
