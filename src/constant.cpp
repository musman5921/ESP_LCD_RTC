/*
 Project Name ------  FRS
 Task --------------  DWIN LCD Firmware with Esp32
 Engineer ----------- Muhammad Usman
 File --------------- Lcd Source File
 Company -----------  Machadev Pvt Limited
 */

#include "constant.h"

TaskHandle_t xHandlegps;
TaskHandle_t xHandledatetime;
TaskHandle_t xHandlelogin;
TaskHandle_t xHandleconfigdevice;
TaskHandle_t xHandlehomepage;

String checkData = "";
String datatocompare = "";

unsigned long previousDataReceiveTime = 0;
const unsigned long interval = 7 * 24 * 60 * 60 * 1000; // Interval is set to one week in milliseconds
int lastDataEntryweekbyYear = 0; // Initialize last data entry week by year
byte lastDataEntryEEPROM = 0;
const int EEPROMAddress = 100; // EEPROM address to store the last data entry day

// date and time variables
String DAY = "";
String MONTH = "";
String YEAR = "";
String HOUR = "";
String MINUTE = "";
String dateString = "";
String timeString = "";

int day = 0; 
int month = 0; 
int year = 0;  

int weekByMonth = 0;
int weekByYear = 0;

// Define Values
const String clientPanelDigits = "1101";
const String adminPanelDigits = "1102";
const String predefinedSSID = "abc";
const String predefinedPassword = "abc123";
String internetSSID = "";
String internetPassword = "";
String storedUniqueData = "";
String companyName = "";
String companyAddress = "";
String keyResponsiblePersonName = "";
String keyResponsiblePersonContact = "";
String keyResponsiblePerson1Name = "";
String keyResponsiblePerson1Contact = "";
String keyResponsiblePerson2Name = "";
String keyResponsiblePerson2Contact = "";
String keyResponsiblePerson3Name = "";
String keyResponsiblePerson3Contact = "";
String keyResponsiblePerson4Name = "";
String keyResponsiblePerson4Contact = "";
String localFireDepartmentName = "";
String localFireDepartmentContact = "";
String manufacturerName = "";
String manufacturerContact = "";
String manufacturerEmail = "";
String dateOfManufacture = "";
String serialNumber = "";
String locationOfUnit = "";
String assignedUnitNumber = "";
String dateOfUnitInstallation = "";
String unitInstaller = "";
String unitContactDetails = "";
String ipAddress = "";
const String showClient = "1101";
const String showAdmin = "1102";
const String switchUser = "2ec";
const String uniqueButtonDigits = "1101";
const String predefinedInternetSSID = "Machadev";
const String predefinedInternetPassword = "13060064";
const String showPassword = "103";
const String hidePassword = "102";
const String companyDoneButtonYes = "1101";
const String companyDoneButtonNo = "1102";
const String Data_Uploading = "1101";
const String Manufacturing_Details_Upload = "1101";
const String Manufacturing_Details_Back = "1102";
const String Unit_Details_Upload = "1101";
const String Unit_Details_Back = "1102";
const String Left_Arrow_Indication = "1101";
const String Right_Arrow_Indication = "1102";
const String Arrow_Details_Back = "1103";
const String Home_Screen_Menu = "1101";
const String Menu_Home_Screen = "1102";
const String Home_Screen_Report = "1101";
const String Report_Home_Screen = "1102";

//checklists
const String Home_Screen_Checklist = "1101";
const String geticonPage1 = "1111";
const String previousONpage1 = "1112";

const String geticonPage2 = "1113";
const String previousONpage2 = "1114";

const String geticonPage3 = "1115";
const String previousONpage3 = "1116";

const String geticonPage4 = "1117";
const String previousONpage4 = "1118";

const String Checklist_Done = "1103";
const String previousONpage5 = "110a";

const String Home_Screen_Back = "1101";
const String Home_Screen = "1102";

const int RESET = 0x0;

// Define the VP Addresses
unsigned char Buffer[10];
const int CLIENT_SSID = 0x3100;
const int CLIENT_PASSWORD = 0x3164;
const int CLIENT_PASSWORD_DISPLAY = 0x2F38;
const int CLIENT_PASSWORD_ICON = 0x31C8;
const int CLIENT_REMEMBER_LOGIN = 0x31c9;
const int clientLoginStatus = 0x3000;
const int adminLoginStatus = 0x3000;
const int ADMIN_SSID = 0x32CB;
const int ADMIN_PASSWORD = 0x332F;
const int ADMIN_PASSWORD_DISPLAY = 0x2f9c;
const int ADMIN_PASSWORD_HIDE = 0x3393;
const int ADMIN_REMEMBER_LOGIN = 0x3394;
const int ADMIN_PASSWORD_ICON = 0x3393;
const int LOGIN = 0x31CA;
const int INTERNET_SSID = 0x3396;
const int INTERNET_PASSWORD = 0x33fa;
const int INTERNET_PASSWORD_DISPLAY = 0x2ed4;
const int INTERNET_PASSWORD_ICON = 0x345e;
const int INTERNET_CONNECT_BUTTON = 0x345f;
const int UNIQUE_KEY = 0x3460;
const int UNIQUE_KEY_OKAY_BUTTON = 0x34c4;
const int COMPANY_DONE_BUTTON_ADDRESS = 0x3a3c;
const int VP_COMPANY_NAME = 0x34c5;
const int VP_COMPANY_ADDRESS = 0x3529;
const int VP_KEY_RESPONSIBLE_PERSON_NAME = 0x358d;
const int VP_KEY_RESPONSIBLE_PERSON_CONTACT = 0x35f1;
const int VP_KEY_RESPONSIBLE_PERSON1_NAME = 0x3665;
const int VP_KEY_RESPONSIBLE_PERSON1_CONTACT = 0x3655;
const int VP_AUTO_UPLOAD_COMPANY_DETAILS = 0x3a3d;
const int VP_KEY_RESPONSIBLE_PERSON2_NAME = 0x371d;
const int VP_KEY_RESPONSIBLE_PERSON2_CONTACT = 0x3781;
const int VP_KEY_RESPONSIBLE_PERSON3_NAME = 0x37e5;
const int VP_KEY_RESPONSIBLE_PERSON3_CONTACT = 0x3849;
const int VP_KEY_RESPONSIBLE_PERSON4_NAME = 0x3911;
const int VP_KEY_RESPONSIBLE_PERSON4_CONTACT = 0x39d9;
const int VP_LOCAL_FIRE_DEPARTMENT_NAME = 0x3975;
const int VP_LOCAL_FIRE_DEPARTMENT_CONTACT = 0x39d9;
const int VP_MANUFACTURING_DETAILS = 0x3a40;
const int VP_MANUFACTURE_NAME = 0x3c97;
const int VP_MANUFACTURE_CONTACT = 0x3cfb;
const int VP_MANUFACTURE_EMAIL = 0x3d5f;
const int VP_MANUFACTURE_DATE = 0x3dc3;
const int VP_MANUFACTURE_SERIAL_N0 = 0x3e27;
const int VP_UNIT_DONE = 0x3a3e;
const int VP_LOCATION_OF_UNIT = 0x3a3f;
const int VP_ASSIGNED_UNIT_NUMBER = 0x3aa3;
const int VP_DATE_OF_UNIT_INSTALLATION = 0x3b07;
const int VP_UNIT_INSTALLER = 0x3b68;
const int VP_UNIT_CONTACT_DETAILS = 0x3bcf;
const int VP_UNIT_IP_ADDRESS = 0x3cc3;
const int VP_DEVICE_DRIVER_RETURN_KEY = 0x3e8b;
const int VP_UNIT_DATE = 0x6100;
const int VP_UNIT_TIME = 0x6000;

// Home page VPs
const int show_Menu = 0x6211;
const int local_Map = 0x6212;
const int site_Map = 0x6213;
const int fyreBox_Unit_Lists = 0x6214;
const int show_report = 0x6215;
const int self_Test = 0x6216;
const int checklists = 0x6217;
const int start_SlideShow = 0x6218;

// Check Boxes Memory Variables
String controlFunction = "";
String speakerActivate = "";
String firemanActivateBox = "";
String bellRingSystemActivation = "";
String batteryHealth = "";
String ledLightOnWhite = "";
String ledRedActivation = "";
String smsReceivedFyreboxActivated = "";
String lcdScreenWork = "";
String systemActivateWeeklySelfTest = "";
String evacuatioDiagram = "";
String arrowWorking = "";
String permanentPower = "";
String illuminatedSignalsWorking = "";
String batteriesReplacement = "";
String flashSignPanel = "";
String unitSecured = "";
String faciaComponentSecured = "";
String evacuationDiagramUptodate = "";
String fyreboxFreeObstructions = "";
String LogbookUptodate = "";
String fyreboxUnitWipedCleaned = "";
String anyDamageBox = "";
String anyRustUnit = "";
String checkBoxesDonePressed = "3";

// Menu Memory Variables
String showBoxesDonePressed = "055";
String returnKeycode_report = "056";
String returnKeycode_checklist = "057";
String startSlideshow = "058";
String stopSlideshow = "059";
String returnKeycode_showMenu = "060";
String returnKeycode_hideMenu = "061";
String returnKeycode_uploadPDF = "062";
String returnKeycode_batteryCalc = "066";

// Check Boxes VP Addresses
const int CONTROL_FUNCTION = 0x5000;
const int SPEAKER_ACTIVATE = 0x5001;
const int FIREMAN_ACTIVATE_BOX = 0x5002;
const int BELL_RING_SYSTEM_ACTIVATION = 0x5003;
const int BATTERY_HEALTH = 0x5004;
const int LED_LIGHT_ON_WHITE = 0x5005;
const int LED_RED_ACTIVATION = 0x5006;
const int SMS_RECEIVED_FYREBOX_ACTIVATED = 0x5007;
const int LCD_SCREEN_WORK = 0x5008;
const int SYSTEM_ACTIVATE_WEEKLY_SELF_TEST = 0x5009;
const int EVACUATION_DIAGRAM = 0x500a;
const int ARROW_WORKING = 0x500b;
const int PERMANENT_POWER = 0x500c;
const int ILLUMINATED_SIGNALS_WORKING = 0x500d;
const int BATTERIES_REPLACEMENT = 0x500e;
const int FLASH_SIGN_PANELS = 0x500f;
const int UNIT_SECURED = 0x5010;
const int FACIA_COMPONENT_SECURED = 0x5011;
const int EVACUATION_DIAGRAM_UPTODATE = 0x5012;
const int FYREBOX_FREE_OBSTRUCTIONS = 0x5013;
const int LOGBOOK_UPTODATE = 0x5014;
const int FYREBOX_UNIT_WIPED_CLEAN = 0x5015;
const int ANY_DAMAGE_BOX = 0x5016;
const int ANY_RUST_UNIT = 0x5017;

// Menu functions VP Addresses of return key code
const int showMenuVP = 0x6221;
const int hideMenuVP = 0x6221;
const int uploadPDF_VP = 0x6221;
const int batteryCalc_VP = 0x6221;

// Check Boxes VP Addresses of Basic Graphic	
const int basicGraphic_page1 = 0x5100;
const int basicGraphic_page2 = 0x5120;
const int basicGraphic_page3 = 0x5140;
const int basicGraphic_page4 = 0x5160;
const int basicGraphic_page5 = 0x5180;

// Vp adresses of Data variable dispay 
const int showWeek_page1_VP = 5030;
const int showWeek_page2_VP = 5040;
const int showWeek_page3_VP = 5050;
const int showWeek_page4_VP = 5060;
const int showWeek_page5_VP = 5070;

// Next page VP Address of Return Key Code		
const int returnKeycode_nextPage_VP = 5080;

// Prev page VP Address of Return Key Code		
const int returnKeycode_prevPage_VP = 5090;

// Y Position of screen to display icons		
const int firstPosition	 	= 0x00C8;
const int secondPosition 	= 0x0104;
const int thirdPosition 	= 0x0140;
const int fourthPosition 	= 0x017C;
const int fifthPosition		= 0x01B8;
const int sixthPosition	 	= 0x01F4;

// Returned key values
// To Check week number and based on vp address show icons
const int Prev_week	= 1;
const int Next_week	= 2;
// week numbers are reserved from 1 to 48 for future use 

// To check next page buttons and show icons on next page
const int Next_page1 = 51;
const int Next_page2 = 52;
const int Next_page3 = 53;
const int Next_page4 = 54;
const int Next_page5 = 55;

// To check prev page buttons and show icons on prev page
const int Prev_page1 = 61;
const int Prev_page2 = 62;
const int Prev_page3 = 63;
const int Prev_page4 = 64;
const int Prev_page5 = 65;

// RTC
unsigned long lastActivityTime = 0;
const unsigned long idleTimeout = 30000; // 30 seconds

// Database Parameters
const String getOrgId = "2";
const String deviceKey = "qTh6ltGGZzmEB";
const String visitorOrgID = "1";
const String visitorName = "Asher%20Sajid";
const String visitoprPhone = "03105963267";
const String deviceId = "1";
const String alertType = "1";
const String operation = "get_devices";
const String logInOperation = "user_login_form";
const String userEmail = "ashiq%40gmail.com";
const String userPassword = "abc123";

// Manufacturer Details Parameters
String mfr_operation = "1";
String mfr_deviceID = "2";
String mfr_manufacturerName = "Asher";
String mfr_manufacturerEmail = "malikasher267@gmail.com";
String mfr_manufacturerContact = "03105963267";
String mfr_manufacturerDate = "01 Jan 2024";
String mfr_serialNumber = "01";
String mfr_orgLogo = "Null";
String mfr_orgEvaMap = "Null";
String mfr_orgAddress = "Wah Cantt";
String mfr_orgStatus = "0";

// Device Checklists Parameters
String devCheck_operation = "add_device_checklist";
String devCheck_deviceId = "";
String siren = "";
String switchDevice = "";
String voltIndicator = "";
String ledWhite = "";
String ledRed = "";
String activationSms = "";
String signage = "";
String autoTest = "";
String testSms = "";
String power = "";
String voltLevel = "";
String battExpiery = "1-01-25";
String deviceInstall = "01-03-24";
String boxState = "Active";
String diagUpdate = "01-02-24";
String deviceObstacle = "Null";
String lastUpdate = "01-02-24";
String deviceClean = "";
String status = "";

// Organization Details Parameters
String Org_operation = "add_organization";
String orgName = "Machadev";
String orgEmail = "malikasher267@gmail.com";
String orgPhone = "03105963267";
String orgType = "1";
String orgVat = "2";
String orgLogo = "C:/Users/01-244211-016/Pictures/machadev_logo.PNG";
String orgEvaMap = "Null";
String orgAddress = "Wah Cantt";
String orgStatus = "1"; 

// Update Organization
String udt_operation = "update_organization";
String udt_orgID = "2";
String udt_orgName = "Machadev";
String udt_orgEmail = "malikasher267@gmail.com";
String udt_orgPhone = "03105963267";
String udt_orgType = "1";
String udt_orgVat = "2";
String udt_orgLogo = "1";
String udt_orgEvaMap = "Null";
String udt_orgAddress = "Wah Cantt";
String udt_orgStatus = "1"; 

// Get Device Details
String orgid = "2";
String getOperation = "get_devices";

// Base Url
const String getOrgBaseUrl = "https://fyreboxhub.com/api/get_org_details.php?org_id=";
const String getDeviceBaseUrl = "https://fyreboxhub.com/api/get_device_checklists.php?device_key=";
const String addVisitorBaseUrl = "https://fyreboxhub.com/api/add_visitor.php?";
const String AlertBaseUrl = "https://fyreboxhub.com/api/create_alert.php?";
const String getDataBaseUrl = "https://fyreboxhub.com/api/get_data.php?";
const String loginBaseUrl = "https://fyreboxhub.com/api/get_data.php?";

// Set Base Url
const String manufacturerBaseUrl = "https://fyreboxhub.com/api/set_data.php?";

// Complete Set Url
// String setManufacturerDetailsUrl = manufacturerBaseUrl + "operation" + mfr_operation + "device_id" + mfr_deviceID + "manufacturer_name" + mfr_manufacturerName + "manufacturer_emaild" + mfr_manufacturerEmail + "manufacturer_contact" + mfr_manufacturerContact + "manufacturer_dated" + mfr_manufacturerDate + "serial_number" + mfr_serialNumber + "org_logod" + mfr_orgLogo + "org_evacuation_map" + mfr_orgEvaMap + "org_address" + mfr_orgAddress + "org_status" + mfr_orgStatus;

// String setDeviceChecklists = manufacturerBaseUrl + "operation=" + devCheck_operation + "&device_id=" + devCheck_deviceId + "&siren=" + siren + "&switch=" + switchDevice + "&volt_indicator=" + voltIndicator + "&led_white=" + ledWhite + "&led_red=" + ledRed + "&activation_sms=" + activationSms + "&signage=" + signage + "&auto_test=" + autoTest + "&test_sms=" + testSms + "&power=" + power + "&volt_level=" + voltLevel + "&batt_expiry=" + battExpiery + "&devi_install=" + deviceInstall + "&box_state=" + boxState + "&diag_update=" + diagUpdate + "&devi_obstacle=" + deviceObstacle + "&last_update=" + lastUpdate + "&devi_clean=" + deviceClean + "&status=" + status; 
// https://fyreboxhub.com/api/set_data.php?operation=add_device_checklist&device_id=3&siren=1&switch=1&volt_indicator=6&led_white=1&led_red=1&activation_sms=1&signage=5&auto_test=1&test_sms=1&power=1&volt_level=3&batt_expiry=1-01-24&devi_install=01-01-24&box_state=Active&diag_update=01-01-24&devi_obstacle=Null&last_update=01-01-24&devi_clean=1&status=1

// String setOrganizationDetails = manufacturerBaseUrl + "operation=" + Org_operation + "&org_name=" + orgName + "&org_email=" + orgEmail + "&org_phone=" + orgPhone + "&org_type=" + orgType + "&org_vat=" + orgVat + "&org_logo=" + orgLogo + "&org_evacuation_map=" + orgEvaMap + "&org_address=" + orgAddress + "&org_status=" + orgStatus;

// String updateOrganizationDetails = manufacturerBaseUrl + "operation=" + udt_operation + "&org_id=" + udt_orgID + "&org_name=" + udt_orgName + "&org_email=" + udt_orgEmail + "&org_phone=" + udt_orgPhone + "&org_type=" + udt_orgType + "&org_vat=" + udt_orgVat + "&org_logo=" + udt_orgLogo + "&org_evacuation_map=" + udt_orgEvaMap + "&org_address=" + udt_orgAddress + "&org_status=" + udt_orgStatus;


// Complete get Url
const String logInDetailsUrl = loginBaseUrl + "operation=" + logInOperation + "&user_email=" + userEmail + "&user_password=" + userPassword;
const String getOrgDetailsUrl = getOrgBaseUrl + getOrgId;
const String getDeviceChecklistsUrl = getDeviceBaseUrl + deviceKey;
const String addVisitorUrl = addVisitorBaseUrl + "org_id=" + visitorOrgID + "&name=" + visitorName + "&phone=" + visitoprPhone;
const String createAlertUrl = AlertBaseUrl + "device_id=" + deviceId + "&alert_type=" + alertType;
const String devicesDetailsUrl = getDataBaseUrl + "operation=" + getOperation + "&org_id=" + orgid;

// Define Page Number
const int COPYRIGHT = 0x0001;
const int CLIENTPAGE = 0x0003;
const int ADMINPAGE = 0x0004;
const int INTERNETPAGE = 0x0005;
const int UNIQUE_KEY_PAGE = 0x0006;
const int COMPANY_DETAILS_PAGE1 = 0x0007;
const int COMPANY_DETAILS_PAGE2 = 0x0008;
const int COMPANY_DETAILS_PAGE3 = 0x0009;
const int COMPANY_DETAIL_AUTO_LOAD = 0x000A;
const int COMPANY_UNIT_DETAILS = 0x000D;
const int COMPANY_MANUFACTURE_DETAILS = 0x000E;
const int DEVICE_DIRECTION_DETAILS_PAGE = 0x0010;
const int DEVICE_CONFIGURED_SUCCESSFULLY = 0x0014;
const int HOME_PAGE = 0x001A;
const int CHECKLISTPAGE1 = 0x001B;
const int CHECKLISTPAGE2 = 0x001C;
const int CHECKLISTPAGE3 = 0x001D;
const int CHECKLISTPAGE4 = 0x001E;
const int CHECKLISTPAGE5 = 0x001F;
const int SHOW_REPORT_PAGE = 0x0020;
const int MENU_PAGE = 0x0025;


// Flags
bool clientLogin = false;
bool adminLogin = false;
bool rememberClient = false;
bool rememberAdmin = false;
bool wifiConnectedFlag = false;
bool uniqueKeyFlag = false;
bool devicesAvailable = false;
bool companyDetailsFlag = false;
bool companyManufacturerDetails = false;
bool UnitDetailsFlag = false;
bool arrowFlags = false;
bool displayIconsFlag = false;
bool checkBoxFlag = false;
bool activateSlideShow = false;
bool slideShowFlag = false;
bool ConfigureDeviceFlag = false;
bool dataEnteredtoday = false;
bool weekElapsed = false;
bool APIresponseFlag = false;
bool companyManufacturerDetailsBack = false;
bool unitDetailsBack = false;
bool ArrowDetailsBack = false;

// RX and TX
const int GPSRXPin = 5;  // ESP32 GPIO 5 for RX
const int GPSTXPin = 18; // ESP32 GPIO 18 for TX