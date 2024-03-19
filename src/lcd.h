/*
 Project Name ------  FRS
 Task --------------  DWIN LCD Firmware with Esp32
 Engineer ----------- Muhammad Usman
 File --------------- Lcd Header File
 Company -----------  Machadev Pvt Limited
 */

// lcd.h
#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <RTClib.h>
#include <SoftwareSerial.h>
#include <Preferences.h>

extern RTC_DS3231 rtc; // Define rtc
extern SoftwareSerial SerialGPS;

extern Preferences preferences;

struct Credentials 
{
    String ssid;
    String password;
};

void readData();
void checkVersion();
void sendReadCommand(uint16_t address, uint16_t data_length);
String readResponse();
void readPage();
void pageSwitch(byte pageNo);
void systemReset();
bool compareCredentials(String ssid, String password);
void checkConnectButton();
void writeString(uint16_t address, const String &data);
String tempreadResponse();
bool checkLastFourDigitsMatch(const String &inputString, const String &targetDigits);
// String hexToText(const String& hexString);
void sendWriteCommand(uint16_t address, byte data);
void readTextFromDWIN();
String readText();
void resetVP(uint16_t address);
String hexToString(const String &hex);
String hexToStringRemovedZeros(const String &hex);
String readDataFromDisplay(uint16_t address, uint16_t totalLength, uint16_t maxChunkSize);
bool readCheckboxState();
String extractDataBetweenMarkers(String input, String startMarker, String endMarker);
String extractDataBeforeMarker(String input, String startMarker);
String dummyReadResponse();
Credentials retrieveCredentials(uint16_t ssidCommand, uint16_t passwordCommand, uint16_t passwordDisplay, uint16_t passwordIcon);
void performLoginCheck(bool &clientLogin, bool &adminLogin);
String extractVpAddress(const String &inputHex, const String &vpAddressPattern);
void writeStringToDwin(uint16_t address, const String &data);
String toHexString(const String &data);
void sendDataToLcd(uint16_t vpAddress, const String &data);
void writeString(uint16_t address, const String &hexData);
byte hexStringToByte(const String &hex);
byte hexCharToByte(char c);
byte hexToByte(const char *hex);
bool containsPattern(const String &str, const String &pattern);
String extractDataBetweenPatterns(const String &input, const String &startPattern, const String &endPattern);
String removeFirst6Bytes(const String &input);
String removeFirst7Bytes(const String &input);
String processPasswordDisplay(uint16_t readPassword, uint16_t passwordDisplay, uint16_t passwordIcon);
void startCheckingPassword(uint16_t passwordDisplay, uint16_t passwordIcon, const String &checkData);
bool checkLast3DigitsMatch(const String &inputString, const String &targetDigits);
String processFourthAndFifthBytes(const String &checkData);
bool compareInternetCredentials(String ssid, String password);
String readOneData(uint16_t ssidCommand);
String remove13Characters(const String &input);
String ReturnJson(String url, DynamicJsonDocument &doc);
bool processGPRMC(String gprmcString);
bool isActivityDetected();
void iconDisplay(byte iconNo);

void sendIconcommand(uint16_t pageVP, byte icon0, byte icon1, byte icon2, byte icon3, byte icon4, byte icon5);
String extractKeycode(const String &input);
String extractPageVP(const String &input, const String &vpAddressPattern);
String concatinate_checkboxData();
String devicesAvailable_DB(String url);
int getWeekNumberByMonth(int day, int month, int year);
int getWeekNumberByYear(int day, int month, int year);

void checkGPSTask(void *parameter);
bool getGPSTime();
void dateTimeTask(void *parameter);
void loginTask(void *parameter);
void checkInternet();
void configuredeviceTask(void *parameter);
void companyDetails();
void manufactureDetails();
void unitDetails();
void devicesDirectionDetails();
void slideShow();
void homepageTasks(void *parameter);
void CheckBoxes();
void displayIcons();
void saveClientCredentials(const String& username, const String& password);
void removeClientCredentials();
void saveAdminCredentials(const String& username, const String& password);
void removeAdminCredentials();
void loadCredentials(String& username, String& password);
bool RememberIcon(uint16_t rememberLogin);
void processClientLogin(uint16_t username, uint16_t passwordCommand, uint16_t passwordDisplay, uint16_t passwordIcon);
void processAdminLogin(uint16_t username, uint16_t passwordCommand, uint16_t passwordDisplay, uint16_t passwordIcon);

#endif // LCD_H
