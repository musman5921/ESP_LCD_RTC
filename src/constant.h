/*
 Project Name ------  FRS
 Task --------------  DWIN LCD Firmware with Esp32
 Engineer ----------- Muhammad Usman
 File --------------- Constants
 Company -----------  Machadev Pvt Limited
 */

// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

// Baud Rates
// #define Baud_RATE_SERIAL  9600
// #define Baud_RATE_DISPLAY  9600

extern TaskHandle_t xHandlegps;
extern TaskHandle_t xHandledatetime;
extern TaskHandle_t xHandlelogin;
extern TaskHandle_t xHandleconfigdevice;
extern TaskHandle_t xHandlehomepage;

extern String checkData;
extern String datatocompare;

extern unsigned long previousDataReceiveTime;
extern const unsigned long interval;
extern int lastDataEntryweekbyYear;
extern byte lastDataEntryEEPROM;
extern const int EEPROMAddress;

// date and time variables
extern String DAY;
extern String MONTH;
extern String YEAR;
extern String HOUR;
extern String MINUTE;
extern String dateString;
extern String timeString;

extern int day; 
extern int month; 
extern int year;  

extern int weekByMonth;
extern int weekByYear;

// Defined Values
extern const String clientPanelDigits;
extern const String adminPanelDigits;
extern String internetSSID;
extern String internetPassword;
extern String storedUniqueData;
extern const String showPassword;
extern const String hidePassword;
extern const String companyDoneButtonYes;
extern const String companyDoneButtonNo;
extern String companyName;
extern String companyAddress;
extern String keyResponsiblePersonName;
extern String keyResponsiblePersonContact;
extern String keyResponsiblePerson1Name;
extern String keyResponsiblePerson1Contact;
extern String keyResponsiblePerson2Name;
extern String keyResponsiblePerson2Contact;
extern String keyResponsiblePerson3Name;
extern String keyResponsiblePerson3Contact;
extern String keyResponsiblePerson4Name;
extern String keyResponsiblePerson4Contact;
extern String localFireDepartmentName;
extern String localFireDepartmentContact;
extern const String Data_Uploading;
extern const int COMPANY_MANUFACTURE_DETAILS;
extern const String Manufacturing_Details_Upload;
extern const String Manufacturing_Details_Back;
extern String manufacturerName;
extern String manufacturerContact;
extern String manufacturerEmail;
extern String dateOfManufacture;
extern String serialNumber;
extern String locationOfUnit;
extern String assignedUnitNumber;
extern String dateOfUnitInstallation;
extern String unitInstaller;
extern String unitContactDetails;
extern String ipAddress;
extern const String Unit_Details_Upload;
extern const String Unit_Details_Back;
extern const String Left_Arrow_Indication;
extern const String Right_Arrow_Indication;
extern const String Arrow_Details_Back;
extern const String Home_Screen_Menu;
extern const String Menu_Home_Screen;
extern const String Home_Screen_Report;
extern const String Report_Home_Screen;

//checklists
extern const String Home_Screen_Checklist;
extern const String geticonPage1;
extern const String previousONpage1;

extern const String geticonPage2;
extern const String previousONpage2;

extern const String geticonPage3;
extern const String previousONpage3;

extern const String geticonPage4;
extern const String previousONpage4;

extern const String Checklist_Done;
extern const String previousONpage5;

extern const String Home_Screen_Back;
extern const String Home_Screen;



extern unsigned char Buffer[10];
extern const int RESET;

// VP Addresses
extern const int VP_CONNECT_BUTTON;
extern const int CLIENT_SSID;
extern const int CLIENT_PASSWORD;
extern const int ADMIN_SSID;
extern const int ADMIN_PASSWORD;
extern const int LOGIN;
extern const int COPYRIGHT;
extern const int checkboxVP;
extern const int clientLoginStatus;
extern const int adminLoginStatus;
extern const int CLIENT_PASSWORD_DISPLAY;
extern const int CLIENT_PASSWORD_ICON;
extern const int CLIENT_REMEMBER_LOGIN;
extern const int ADMIN_PASSWORD_DISPLAY;
extern const int ADMIN_PASSWORD_HIDE;
extern const int ADMIN_REMEMBER_LOGIN;
extern const int ADMIN_PASSWORD_ICON;
extern const int INTERNETPAGE;
extern const int INTERNET_SSID;
extern const int INTERNET_PASSWORD;
extern const int INTERNET_PASSWORD_DISPLAY;
extern const int INTERNET_PASSWORD_HIDE;
extern const int INTERNET_CONNECT_BUTTON;
extern const int UNIQUE_KEY;
extern const int UNIQUE_KEY_OKAY_BUTTON;
extern const int UNIQUE_KEY_PAGE;
extern const String predefinedInternetSSID;
extern const String predefinedInternetPassword;
extern const String showClient;
extern const String showAdmin;
extern const String switchUser;
extern const String uniqueButtonDigits;

extern const int COMPANY_DETAILS_PAGE1;
extern const int COMPANY_DETAILS_PAGE2;
extern const int COMPANY_DETAILS_PAGE3;
extern const int COMPANY_DETAIL_AUTO_LOAD;
extern const int COMPANY_DONE_BUTTON_ADDRESS;
extern const int VP_COMPANY_NAME;
extern const int VP_COMPANY_ADDRESS;
extern const int VP_KEY_RESPONSIBLE_PERSON_NAME;
extern const int VP_KEY_RESPONSIBLE_PERSON_CONTACT;
extern const int VP_KEY_RESPONSIBLE_PERSON1_NAME;
extern const int VP_KEY_RESPONSIBLE_PERSON1_CONTACT;
extern const int VP_AUTO_UPLOAD_COMPANY_DETAILS;
extern const int VP_KEY_RESPONSIBLE_PERSON2_NAME;
extern const int VP_KEY_RESPONSIBLE_PERSON2_CONTACT;
extern const int VP_KEY_RESPONSIBLE_PERSON3_NAME;
extern const int VP_KEY_RESPONSIBLE_PERSON3_CONTACT;
extern const int VP_KEY_RESPONSIBLE_PERSON4_NAME;
extern const int VP_KEY_RESPONSIBLE_PERSON4_CONTACT;
extern const int VP_LOCAL_FIRE_DEPARTMENT_NAME;
extern const int VP_LOCAL_FIRE_DEPARTMENT_CONTACT;
extern const int VP_MANUFACTURING_DETAILS;
extern const int VP_MANUFACTURE_NAME;
extern const int VP_MANUFACTURE_CONTACT;
extern const int VP_MANUFACTURE_EMAIL;
extern const int VP_MANUFACTURE_DATE;
extern const int VP_MANUFACTURE_SERIAL_N0;
extern const int VP_UNIT_DONE;
extern const int VP_ASSIGNED_UNIT_NUMBER;
extern const int VP_DATE_OF_UNIT_INSTALLATION;
extern const int VP_UNIT_INSTALLER;
extern const int VP_UNIT_CONTACT_DETAILS;
extern const int VP_UNIT_IP_ADDRESS;
extern const int COMPANY_UNIT_DETAILS;
extern const int VP_LOCATION_OF_UNIT;
extern const int DEVICE_DIRECTION_DETAILS_PAGE;
extern const int VP_DEVICE_DRIVER_RETURN_KEY;
extern const int DEVICE_CONFIGURED_SUCCESSFULLY;
extern const int HOME_PAGE;
extern const int MENU_PAGE;
extern const int SHOW_REPORT_PAGE;
extern const int CHECKLISTPAGE1;
extern const int CHECKLISTPAGE2;
extern const int CHECKLISTPAGE3;
extern const int CHECKLISTPAGE4;
extern const int CHECKLISTPAGE5;
extern const int CLIENTPAGE;
extern const int ADMINPAGE;

extern const int VP_UNIT_DATE;
extern const int VP_UNIT_TIME;

// Home page VPs
extern const int show_Menu;
extern const int local_Map;
extern const int site_Map;
extern const int fyreBox_Unit_Lists;
extern const int show_report;
extern const int self_Test;
extern const int checklists;
extern const int start_SlideShow;

// Check Boxes Strings
extern String controlFunction;
extern String speakerActivate;
extern String firemanActivateBox;
extern String bellRingSystemActivation;
extern String batteryHealth;
extern String ledLightOnWhite;
extern String ledRedActivation;
extern String smsReceivedFyreboxActivated;
extern String lcdScreenWork;
extern String systemActivateWeeklySelfTest;
extern String evacuatioDiagram;
extern String arrowWorking;
extern String permanentPower;
extern String illuminatedSignalsWorking;
extern String batteriesReplacement;
extern String flashSignPanel;
extern String unitSecured;
extern String faciaComponentSecured;
extern String evacuationDiagramUptodate;
extern String fyreboxFreeObstructions;
extern String LogbookUptodate;
extern String fyreboxUnitWipedCleaned;
extern String anyDamageBox;
extern String anyRustUnit;

// Menu Strings
extern String checkBoxesDonePressed;
extern String showBoxesDonePressed;
extern String returnKeycode_report;
extern String returnKeycode_checklist;
extern String startSlideshow;
extern String stopSlideshow;
extern String returnKeycode_showMenu;
extern String returnKeycode_hideMenu;
extern String returnKeycode_uploadPDF;
extern String returnKeycode_batteryCalc;

// Check Boxes VP Addresses
extern const int CONTROL_FUNCTION;
extern const int SPEAKER_ACTIVATE;
extern const int FIREMAN_ACTIVATE_BOX;
extern const int BELL_RING_SYSTEM_ACTIVATION;
extern const int BATTERY_HEALTH;
extern const int LED_LIGHT_ON_WHITE;
extern const int LED_RED_ACTIVATION;
extern const int SMS_RECEIVED_FYREBOX_ACTIVATED;
extern const int LCD_SCREEN_WORK;
extern const int SYSTEM_ACTIVATE_WEEKLY_SELF_TEST;
extern const int EVACUATION_DIAGRAM;
extern const int ARROW_WORKING;
extern const int PERMANENT_POWER;
extern const int ILLUMINATED_SIGNALS_WORKING;
extern const int BATTERIES_REPLACEMENT;
extern const int FLASH_SIGN_PANELS;
extern const int UNIT_SECURED;
extern const int FACIA_COMPONENT_SECURED;
extern const int EVACUATION_DIAGRAM_UPTODATE;
extern const int FYREBOX_FREE_OBSTRUCTIONS;
extern const int LOGBOOK_UPTODATE;
extern const int FYREBOX_UNIT_WIPED_CLEAN;
extern const int ANY_DAMAGE_BOX;
extern const int ANY_RUST_UNIT;

// Menu functions VP Addresses of return key code
extern const int showMenuVP;
extern const int hideMenuVP;
extern const int uploadPDF_VP;
extern const int batteryCalc_VP;

// Check Boxes VP Addresses of Basic Graphic	
extern const int basicGraphic_page1;
extern const int basicGraphic_page2;
extern const int basicGraphic_page3;
extern const int basicGraphic_page4;
extern const int basicGraphic_page5;

// Vp adresses of Data variable dispay (4500 to 4600)	
extern const int showWeek_page1_VP;
extern const int showWeek_page2_VP;
extern const int showWeek_page3_VP;
extern const int showWeek_page4_VP;
extern const int showWeek_page5_VP;

// Next page VP Addresses of Return Key Code	
extern const int returnKeycode_nextPage_VP;

// Prev page VP Addresses of Return Key Code	
extern const int returnKeycode_prevPage_VP;

// Y Position of screen to display icons		
extern const int firstPosition; 
extern const int secondPosition; 
extern const int thirdPosition; 
extern const int fourthPosition;   	
extern const int fifthPosition;      
extern const int sixthPosition;

// Returned key values
// To Check week number and based on vp address show icons
extern const int Prev_week;
extern const int Next_week;
// week numbers are reserved from 1 to 48 for future use 

// To check next page buttons and show icons on next page
extern const int Next_page1;
extern const int Next_page2;
extern const int Next_page3;
extern const int Next_page4;
extern const int Next_page5;

// To check prev page buttons and show icons on prev page
extern const int Prev_page1;
extern const int Prev_page2;
extern const int Prev_page3;
extern const int Prev_page4;
extern const int Prev_page5;

// RTC
extern unsigned long lastActivityTime;
extern const unsigned long idleTimeout;

// Predefined Credentials
extern const String predefinedSSID;
extern const String predefinedPassword;

// Flags
extern bool clientLogin;
extern bool adminLogin;
extern bool rememberClient;
extern bool rememberAdmin;
extern bool wifiConnectedFlag;
extern bool uniqueKeyFlag;
extern bool devicesAvailable;
extern bool companyDetailsFlag;
extern bool companyManufacturerDetails;
extern bool UnitDetailsFlag;
extern bool arrowFlags;
extern bool displayIconsFlag;
extern bool checkBoxFlag;
extern bool activateSlideShow;
extern bool slideShowFlag;
extern bool ConfigureDeviceFlag;
extern bool dataEnteredtoday;
extern bool weekElapsed;
extern bool APIresponseFlag;
extern bool companyManufacturerDetailsBack;
extern bool unitDetailsBack;
extern bool ArrowDetailsBack;

// Database Parameters
extern const String getOrgId;
extern const String deviceKey;
extern const String visitorOrgID;
extern const String visitorName;
extern const String visitoprPhone;
extern const String deviceId;
extern const String alertType;
extern const String operation;
extern const String logInOperation;
extern const String userEmail;
extern const String userPassword;

// Manufacturer Details Parameters
extern String mfr_operation;
extern String mfr_deviceID;
extern String mfr_manufacturerName;
extern String mfr_manufacturerEmail;
extern String mfr_manufacturerContact;
extern String mfr_manufacturerDate;
extern String mfr_serialNumber;
extern String mfr_orgLogo;
extern String mfr_orgEvaMap;
extern String mfr_orgAddress;
extern String mfr_orgStatus;

// Device Checklists Parameters
extern String devCheck_operation;
extern String devCheck_deviceId;
extern String siren;
extern String switchDevice;
extern String voltIndicator;
extern String ledWhite;
extern String ledRed;
extern String activationSms;
extern String signage;
extern String autoTest;
extern String testSms;
extern String power;
extern String voltLevel;
extern String battExpiery;
extern String deviceInstall;
extern String boxState;
extern String diagUpdate;
extern String deviceObstacle;
extern String lastUpdate;
extern String deviceClean;
extern String status;

// Organization Details Parameters
extern String Org_operation;
extern String orgName;
extern String orgEmail;
extern String orgPhone;
extern String orgType;
extern String orgVat;
extern String orgLogo;
extern String orgEvaMap;
extern String orgAddress;
extern String orgStatus; 

// Update Organization
extern String udt_operation;
extern String udt_orgID;
extern String udt_orgName;
extern String udt_orgEmail;
extern String udt_orgPhone;
extern String udt_orgType;
extern String udt_orgVat;
extern String udt_orgLogo;
extern String udt_orgEvaMap;
extern String udt_orgAddress;
extern String udt_orgStatus; 

// Get Device Details
extern String orgid;
extern String getOperation;

// Base Url
extern const String getOrgBaseUrl;
extern const String getDeviceBaseUrl;
extern const String addVisitorBaseUrl;
extern const String AlertBaseUrl;
extern const String getDataBaseUrl;
extern const String loginBaseUrl;

// Complete Url
extern const String logInDetailsUrl;
extern const String getOrgDetailsUrl;
extern const String getDeviceChecklistsUrl;
extern const String addVisitorUrl;
extern const String createAlertUrl;
extern const String devicesDetailsUrl;

// Set Base Url
extern const String manufacturerBaseUrl;

// Complete Set Url
// extern String setManufacturerDetailsUrl;

// extern String setDeviceChecklists;
// https://fyreboxhub.com/api/set_data.php?operation=add_device_checklist&device_id=3&siren=1&switch=1&volt_indicator=6&led_white=1&led_red=1&activation_sms=1&signage=5&auto_test=1&test_sms=1&power=1&volt_level=3&batt_expiry=1-01-24&devi_install=01-01-24&box_state=Active&diag_update=01-01-24&devi_obstacle=Null&last_update=01-01-24&devi_clean=1&status=1

// extern String setOrganizationDetails;

// extern String updateOrganizationDetails;


// RX and TX
extern const int GPSRXPin;
extern const int GPSTXPin;

#endif // CONSTANTS_H