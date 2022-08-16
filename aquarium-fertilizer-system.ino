#include <Time.h>
#include <TimeAlarms.h>
#include <DS1307RTC.h>

const int motor= 10;

void setup()
{
  Serial.begin(9600);
   while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
     
  pinMode(motor, OUTPUT);
  Alarm.alarmRepeat(8,20,0, aquariumFeed); //set timer to control pump
}

void loop(){
  if (timeStatus() == timeSet) {
    digitalClockDisplay();
  } else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  delay(1000);
  Alarm.delay(1000); // wait one second between clock display
}

void aquariumFeed(){
  // run pump for +- 5 seconds
  digitalWrite(motor,HIGH);
  delay(5500);
  digitalWrite(motor,LOW);   
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
