/*
 Project Name ------  FRS
 Task --------------  DWIN LCD Firmware with Esp32
 Engineer ----------- Muhammad Usman
 File --------------- Main File (Code Exceution Start in this file)
 Company -----------  Machadev Pvt Limited

Firmware Details

Implemented:

- LoRa Task: Pinned to Core 1 to frequently update the mesh network.
- Task Management:
  - All tasks are suspended except for the login task.
  - Upon completion of the login task, the device configuration task is initiated.
  - In the configuration task, company details, manufacturer details, unit details, and device direction are set.
  - Once the device is configured, it enters an infinite slideshow loop until a screen touch is detected.
  - If a touch is detected, it proceeds to handle homepage tasks.

  - If the LoRa module is not found, the system will remain in a loop and retry until the module is detected.
  - If the RTC module is not found, the system will remain in a loop and retry until the module is detected.

Mesh Network Development:

- Developed a mesh network using Ebyte LoRa E32 with ESP32.
- The same logic applies to each node.

Flow:

- The mesh network program is identical for all nodes in the network:
  - Each node listens to other nodes in a loop.
  - Each node updates the activity status of other nodes every 10 seconds.
  - Each node broadcasts a message every 30 seconds.
  - Each node prints network stats every 60 seconds.

Tests:

- The network consists of 4 nodes:
  - Each node knows how many nodes are available, active, and dead in its network.
  - Each node successfully updates its node info container every 60 seconds.
  - Note: There is no acknowledgment message for broadcasted messages.

PlatformIO Configuration:

[env:esp32-s3-devkitm-1]
platform = espressif32
board = esp32-s3-devkitm-1
framework = arduino
monitor_speed = 115200

Escalator Node:

- The AUX pin of the LoRa module is NOT connected to the ESP32.
- The relay is active low, with an LED connected in series with the relay.

FyreBox Node:

- The AUX pin of the LoRa module is NOT connected to the ESP32 S3 Mini.
- Serial0: Used for program uploading and debugging.
- Serial1: DWIN LCD is connected at IO15 (TX of LCD) and IO16 (RX of LCD).
- LoRa Module: Connected at IO35 (RX) and IO36 (TX) using software serial.
- SD Card Connection: The SIG pin must be HIGH (IO5) for the SD card to connect with the DWIN LCD.

*/

// Import Libraries
#include "lcd.h"
#include "constant.h"
#include <WiFi.h>
#include <EEPROM.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Initialize and define SoftwareSerial object
SoftwareSerial SerialGPS(GPSRXPin, GPSTXPin); // not currently used
SoftwareSerial LoRaSerial(LORA_TX_PIN, LORA_RX_PIN); // ESP32(RX), ESP32(TX)

// Setup Function: Call Once when Code Starts
void setup()
{
  // SIG pin must be HIGH for the sdcard to connect with the DWIN LCD
  pinMode(SIGPIN, OUTPUT);
  digitalWrite(SIGPIN, HIGH);

  // Start the Serial Communication with PC
  Serial.begin(115200);  
  Serial.println("Debug Serial is ready.");

  // Start the Serial Communication with DWIN LCD
  Serial1.begin(115200, SERIAL_8N1, DWIN_RX_PIN, DWIN_TX_PIN); 
  Serial.println("Serial1 is ready.");

  // Start the Serial Communication with LoRa module
  LoRaSerial.begin(9600);
  Serial.println("LoRaSerial is ready.");

  // Init driver(LoRa E32) and mesh manager
  Serial.println("Initializing mesh");
  while(! initializeMESH()){  // stays in a loop until LoRa found 
    Serial.println("Mesh initialization failed");
    Serial.println("Retyring...");
    delay(3000);
   }
  Serial.println("Mesh initialized successfully.");

  // RTC pins for ESP32-S3-Mini
  Wire.begin(RTC_SDA, RTC_SCL);
  delay(5);

  // Mandatory for gps task
  Serial.println("Initializing RTC");
  while (!rtc.begin()){ // stays in a loop until RTC found 
    Serial.println("Couldn't find RTC");
    Serial.println("Retyring...");
    delay(3000);
  }
  Serial.println("RTC Initialized.");

  // This line sets date and time on RTC (year, month, date, hour, min, sec)
  // rtc.adjust(DateTime(2024, 5, 23, 16, 0, 0));

  EEPROM.begin(512); // Initialize EEPROM
  preferences.begin("credentials", false); // Open Preferences with "credentials" namespace
  delay(5);
  pageSwitch(COPYRIGHT); // Switch to Copyright Page
  Serial.println("Page Switched");
  delay(5);

  xTaskCreatePinnedToCore(LoRatask, "LoRatask", 4096, NULL, 1, &xHandleLoRa, 1);

  xTaskCreate(loginTask, "LoginTask", 4096, NULL, 2, &xHandlelogin);
  
  // xTaskCreate(checkGPSTask, "CheckGPS", 2048, NULL, 1, &xHandlegps);
  // vTaskSuspend(xHandlegps);
  
  xTaskCreate(dateTimeTask, "DateTimeTask", 2048, NULL, 4, &xHandledatetime);
  vTaskSuspend(xHandledatetime);

  xTaskCreate(configuredeviceTask, "ConfigureDeviceTask", 4096, NULL, 3, &xHandleconfigdevice);
  vTaskSuspend(xHandleconfigdevice);
  
  xTaskCreate(homepageTasks, "HomepageTasks", 4096, NULL, 1, &xHandlehomepage);
  vTaskSuspend(xHandlehomepage);

  // resetVP(CLIENT_SSID);
  resetVP(VP_UNIT_DATE);
  resetVP(VP_UNIT_TIME);
  // resetVP(CLIENT_PASSWORD);
  resetVP(CLIENT_PASSWORD_DISPLAY);
  // resetVP(ADMIN_SSID);
  // resetVP(ADMIN_PASSWORD);
  resetVP(ADMIN_PASSWORD_DISPLAY);
  resetVP(clientLoginStatus);
  resetVP(adminLoginStatus);
  resetVP(INTERNET_SSID);
  // resetVP(INTERNET_PASSWORD);
  resetVP(INTERNET_PASSWORD_DISPLAY);
  // resetVP(INTERNET_PASSWORD_ICON);
  resetVP(INTERNET_CONNECT_BUTTON);
  resetVP(UNIQUE_KEY_OKAY_BUTTON);
  resetVP(UNIQUE_KEY);
  delay(10);
  sendWriteCommand(LOGIN, RESET);
  resetVP(COMPANY_DONE_BUTTON_ADDRESS);
  resetVP(VP_DEVICE_DRIVER_RETURN_KEY);
  resetVP(VP_COMPANY_NAME);
  resetVP(VP_COMPANY_ADDRESS);
  resetVP(VP_KEY_RESPONSIBLE_PERSON_NAME);
  resetVP(VP_KEY_RESPONSIBLE_PERSON_CONTACT);
  resetVP(VP_KEY_RESPONSIBLE_PERSON1_NAME);
  resetVP(VP_KEY_RESPONSIBLE_PERSON1_CONTACT);
  resetVP(VP_AUTO_UPLOAD_COMPANY_DETAILS);
  resetVP(VP_KEY_RESPONSIBLE_PERSON2_NAME);
  resetVP(VP_KEY_RESPONSIBLE_PERSON2_CONTACT);
  resetVP(VP_KEY_RESPONSIBLE_PERSON3_NAME);
  resetVP(VP_KEY_RESPONSIBLE_PERSON3_CONTACT);
  resetVP(VP_KEY_RESPONSIBLE_PERSON4_NAME);
  resetVP(VP_KEY_RESPONSIBLE_PERSON4_CONTACT);
  resetVP(VP_LOCAL_FIRE_DEPARTMENT_NAME);
  resetVP(VP_LOCAL_FIRE_DEPARTMENT_CONTACT);
  resetVP(VP_MANUFACTURING_DETAILS);
  resetVP(VP_MANUFACTURE_NAME);
  resetVP(VP_MANUFACTURE_CONTACT);
  resetVP(VP_MANUFACTURE_EMAIL);
  resetVP(VP_MANUFACTURE_DATE);
  resetVP(VP_MANUFACTURE_SERIAL_N0);
  resetVP(VP_UNIT_DONE);
  resetVP(VP_LOCATION_OF_UNIT);
  resetVP(VP_ASSIGNED_UNIT_NUMBER);
  resetVP(VP_DATE_OF_UNIT_INSTALLATION);
  resetVP(VP_UNIT_INSTALLER);
  resetVP(VP_UNIT_CONTACT_DETAILS);
  resetVP(VP_UNIT_IP_ADDRESS);
  resetVP(VP_DEVICE_DRIVER_RETURN_KEY);
  resetVP(notificationStatus1);
  resetVP(notificationStatus2);
  resetVP(notificationStatus3);
  resetVP(notificationStatus4);
  delay(100);

  activateSlideShow = true;

  // Only for testing of checklists data entery
  // EEPROM.write(EEPROMAddress, 0);
  // EEPROM.commit(); // Commit changes

  // Only for testing of configureInternet();
  // preferences.putString("internetSSID", " ");
  // preferences.putString("internetPass", " ");

  // Only for testing of configureLogin();
  // removeClientCredentials();
  // removeAdminCredentials();
  
}

// Run Code in Loop
void loop()
{
  // **************** Main Code starts here !!!!! ******************* //
  DateTime now = rtc.now();

  day = DAY.toInt(); 
  month = MONTH.toInt(); 
  year = YEAR.toInt();

  weekByMonth = getWeekNumberByMonth(day, month, year); // returns int (number of weeks in a month 1 to 4)
  weekByYear = getWeekNumberByYear(day, month, year); // returns int (number of weeks in a year 1 to 54)

  int currentWeekByMonth = weekByMonth + 1;
  // Serial.println("Week passed by month: "+weekByMonth);
  // Serial.println("Current Week by month: "+currentWeekByMonth);

  int currentWeekByYear = weekByYear + 1;
  // Serial.println("Week passed by year: "+weekByYear);
  // Serial.println("Current Week by year: "+currentWeekByYear);

}

