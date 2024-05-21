/*
 Project Name ------  FRS
 Task --------------  DWIN LCD Firmware with Esp32
 Engineer ----------- Muhammad Usman
 File --------------- Main File (Code Exceution Start in this file)
 Company -----------  Machadev Pvt Limited

	Firmware Details

	Implemented:
  All tasks are suspended except login task
  if login task is completed then moving to the next task to configure device
  in configure device company details, manufacture details, unit details and device direction are called
  once device is configured it will jump into infinite loop of slide show until touch on screen is not detected
  if touch is detected then moving to the next task to handle homepage tasks

  working on login credentials to save, load and autofill credential details of client and admin panel.
  working on WiFi credentials to save, load and autofill ssid and password.

Developed a mesh network using Ebyte LoRa E32 with ESP32
The logic is same for each node

Flow:
The mesh network program is same for all nodes in the network
  Each node listen to other nodes in a loop
  Each node update activity of other nodes after every 10 seconds
  Each node broadcast message after every 30 seconds
  Each node print stats of network after every 60 seconds

Tests:
The network contains 4 nodes
  Each node knows how many nodes are available, active and dead in his network
  Each node successfully updates its node info container after every 60 seconds
  
platformio:
  board selected: espressif esp32 dev module 
  monitor speed: 115200

Escalator node:
AUX pin of LoRa module is NOT connected with ESP32 
Relay is active Low
and an led is connected in series with relay

no ack if message is broadcasted

FyreBox node:
AUX pin of LoRa module is NOT connected with ESP32 S3 mini
DWIN LCD is connected at IO15(TX) and IO16(RX) UART1
LoRa module is connecetd at IO35(RX) and IO36(TX) UART2
Configure UART2
SIG pin must be HIGH IO5 for the sdcard to connect with the DWIN LCD

*/

// Import Libraries
#include "lcd.h"
#include "constant.h"
#include <WiFi.h>
#include <EEPROM.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// #include <SPI.h>
// Main Code is Running Here

// temp only for testing
const char* ssid = "Machadev";
const char* password = "13060064"; 

// Initialize and define SoftwareSerial object
SoftwareSerial SerialGPS(GPSRXPin, GPSTXPin); // not currently used

// Initialize and define SoftwareSerial object
SoftwareSerial LoRaSerial(LORA_RX_PIN, LORA_TX_PIN);

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
  Serial1.begin(9600, SERIAL_8N1, DWIN_RX_PIN, DWIN_TX_PIN); 
  Serial.println("Serial1 is ready.");

  // Start the Serial Communication with LoRa module
  // Serial2.begin(9600, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
  // Serial.println("Serial2 is ready.");

  Serial.println("Initializing mesh...");
  if(! initializeMESH()){
    Serial.println("Mesh initialization failed");
    while(1);
  }
  Serial.println("Mesh initialized successfully.");
  
  EEPROM.begin(512); // Initialize EEPROM
  preferences.begin("credentials", false); // Open Preferences with "credentials" namespace
  delay(5);
  pageSwitch(COPYRIGHT); // Switch to Copyright Page
  Serial.println("Page Switched");
  delay(5);

  // Mandatory for gps task
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.println("RTC Initialized");

  xTaskCreate(loginTask, "LoginTask", 4096, NULL, 2, &xHandlelogin);
  
  xTaskCreate(checkGPSTask, "CheckGPS", 2048, NULL, 1, &xHandlegps);
  vTaskSuspend(xHandlegps);
  
  xTaskCreate(dateTimeTask, "DateTimeTask", 2048, NULL, 1, &xHandledatetime);
  vTaskSuspend(xHandledatetime);
  // vTaskDelete(xHandledatetime); // only for testing

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

  // Connect to WiFi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //     delay(1000);
  //     Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  // pageSwitch(HOME_PAGE);
  // Serial.println("Page Switched");
  // delay(5);

  // Only for testing of checklists data entery
  EEPROM.write(EEPROMAddress, 0);
  EEPROM.commit(); // Commit changes

  // preferences.putString("internetSSID", " ");
  // preferences.putString("internetPass", " ");

  removeClientCredentials();
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

