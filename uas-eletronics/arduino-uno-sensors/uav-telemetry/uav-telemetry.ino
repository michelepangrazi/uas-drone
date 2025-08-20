/*
#####################
#   DISPLAY CODE    #
#####################
*/
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// //#include <Adafruit_BME280.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 32 // OLED display height, in pixels

// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// void setup()
// {
//   Serial.begin(9600);

//   // Setup Display
//   if (display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//     Serial.println("Display initialized");
//   }else{
//         Serial.println("Ooops, no Display detected ... Check your wiring!");
//     while (true);
//   }

//   // Setup GY68
//   if (bmp.begin()) {
//     Serial.println("GY68 initialized");
//   }else{
//     Serial.println("Ooops, no GY68 detected ... Check your wiring!");
//     while (true);
//   }

//   // Setup GY271
//   if(mag.begin()){
//     Serial.println("GY271 initialized!");
//   }else{
//     Serial.println("Ooops, no GY271 detected ... Check your wiring!");
//     while(true);
//   }

//   // Show initial display buffer contents on the screen --
//   // the library initializes this with an Adafruit splash screen.
//   display.display();
//   delay(2000); // Pause for 2 seconds

//   // Clear the buffer
//   display.clearDisplay();

//   // Draw a single pixel in white
//   display.drawPixel(10, 10, SSD1306_WHITE);

//   // Show the display buffer on the screen. You MUST call display() after
//   // drawing commands to make them visible on screen!
//   display.display();
//   delay(2000);
//   testdrawstyles();    // Draw 'stylized' characters
// }

// void loop() 
// {
// }

// void testdrawstyles(void) 
// {
//   display.clearDisplay();
//   display.setTextSize(1);             // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE);        // Draw white text
//   display.setCursor(0, 0);            // Start at top-left corner
//   display.println(F("Hello, world!"));

//   display.setTextColor(SSD1306_WHITE);
//   //(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
//   display.println(3.141592, 6); //6-digit after decimal point

//   display.setTextSize(2);             // Draw 2X-scale text
//   display.setTextColor(SSD1306_WHITE);
//   display.print(F("0x")); display.println(0xDEADBEEF, HEX);

//   display.display();
//   delay(2000);
// }

/*
#####################
#     IMU CODE      #
#####################
*/
// #include <Arduino_LSM6DS3.h>

// float x, y, z;
// int degreesX = 0;
// int degreesY = 0;

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);
//   Serial.println("Started");

//   if (!IMU.begin()) {
//     Serial.println("Failed to initialize IMU!");
//     while (1);
//   }

//   Serial.print("Accelerometer sample rate = ");
//   Serial.print(IMU.accelerationSampleRate());
//   Serial.println("Hz");
// }

// void loop() {

//   if (IMU.accelerationAvailable()) {
//     IMU.readAcceleration(x, y, z);

//   }

//   if (x > 0.1) {
//     x = 100 * x;
//     degreesX = map(x, 0, 97, 0, 90);
//     Serial.print("Tilting up ");
//     Serial.print(degreesX);
//     Serial.println("  degrees");
//   }
//   if (x < -0.1) {
//     x = 100 * x;
//     degreesX = map(x, 0, -100, 0, 90);
//     Serial.print("Tilting down ");
//     Serial.print(degreesX);
//     Serial.println("  degrees");
//   }
//   if (y > 0.1) {
//     y = 100 * y;
//     degreesY = map(y, 0, 97, 0, 90);
//     Serial.print("Tilting left ");
//     Serial.print(degreesY);
//     Serial.println("  degrees");
//   }
//   if (y < -0.1) {
//     y = 100 * y;
//     degreesY = map(y, 0, -100, 0, 90);
//     Serial.print("Tilting right ");
//     Serial.print(degreesY);
//     Serial.println("  degrees");
//   }
//   delay(1000);
// }

/*
#####################
#     GY-68 CODE    #
#####################
*/
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BMP085_U.h>
// // GY68
// Adafruit_BMP085_Unified bmp;


// void setup(){
  
//   Serial.begin(9600);
//   while (!Serial);
//   Serial.println("Started");
  
//   if(bmp.begin()){
//     Serial.print("BMP085 initialized!");
//   }else{
//     Serial.print("Ooops, no BMP085 detected ... Check your wiring");
//     while(1);
//   }
// }

// void loop(){
//   sensors_event_t event;
//   bmp.getEvent(&event);

//   if(event.pressure){
//     float temperature;
//     bmp.getTemperature(&temperature);
//     Serial.print("Temperature: ");
//     Serial.print(temperature);
//     Serial.println(" C");

//     Serial.print("Pressure:    ");
//     Serial.print(event.pressure);
//     Serial.println(" hPa");

//     float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
//     Serial.print("Sea Level Pressure: ");
//     Serial.print(seaLevelPressure);
//     Serial.println(" hPa");

//     Serial.print("Altitude:    "); 
//     Serial.print(bmp.pressureToAltitude(seaLevelPressure,
//                                         event.pressure)); 
//     Serial.println(" m");
//     Serial.println("");

//     delay(1000);
//   }
// }
/*
#####################
#   GY-271 CODE     #
#####################
*/
//https://github.com/keepworking/Mecha_QMC5883L
// #include <Wire.h>
// #include <MechaQMC5883.h>

// MechaQMC5883 qmc;

// void setup() {
//   Wire.begin();
//   Serial.begin(9600);
//   qmc.init();
//   //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
// }

// void loop() {
//   int x,y,z;
//   qmc.read(&x,&y,&z);

//   Serial.print("x: ");
//   Serial.print(x);
//   Serial.print(" y: ");
//   Serial.print(y);
//   Serial.print(" z: ");
//   Serial.print(z);
//   Serial.println();
//   delay(100);
// }
/*
################
#   GPS CODE   #
################
*/
#include <Wire.h>
#include <TinyGPS++.h>

// GPS
static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
// SoftwareSerial ss(RXPin, TXPin);

UART ss(digitalPinToPinName(RXPin), digitalPinToPinName(TXPin), NC, NC);

void setup(){
    // Setup GPS
  ss.begin(GPSBaud);
  Serial.println("GPS initialized");
}

void loop(){
   while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  
  if (gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Lng: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Sat: ");
    Serial.println(gps.satellites.value(), 6);
    Serial.print("Alt: ");
    Serial.println(gps.altitude.meters(), 6);
  }
  else{
    Serial.println("Unable to get gps data");
  }

  delay(1000);
}
/*
################
# BUTTON CODE  #
################
*/