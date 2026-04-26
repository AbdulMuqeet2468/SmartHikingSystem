#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#define LED 5
#define BUZZ 4

#define ON_TRACK  (1 << 0)
#define OFF_TRACK (1 << 1)

EventGroupHandle_t eg;
Adafruit_SSD1306 display(128, 64, &Wire);

// PATH (from MATLAB)
float path[][2] = {
  {17.00000, 78.00000},{17.01053, 78.03247},{17.02105, 78.06142},
  {17.03158, 78.08372},{17.04211, 78.09694},{17.05263, 78.09966},
  {17.06316, 78.09158},{17.07368, 78.07357},{17.08421, 78.04759},
  {17.09474, 78.01646},{17.10526, 77.98354},{17.11579, 77.95241},
  {17.12632, 77.92643},{17.13684, 77.90842},{17.14737, 77.90034},
  {17.15789, 77.90306},{17.16842, 77.91628},{17.17895, 77.93858},
  {17.18947, 77.96753},{17.20000, 78.00000}
};

// ACTUAL (with deviation)
float actual[][2] = {
  {17.00000, 78.00000},{17.01053, 78.03247},{17.02105, 78.06142},
  {17.03158, 78.08372},{17.04211, 78.09694},{17.05263, 78.09966},
  {17.06316, 78.09158},{17.07368, 78.12357},{17.10921, 78.09090},
  {17.13804, 78.04146},{17.15526, 77.98354},{17.15909, 77.92741},
  {17.15132, 77.88313},{17.13684, 77.85842},{17.14737, 77.90034},
  {17.15789, 77.90306},{17.16842, 77.91628},{17.17895, 77.93858},
  {17.18947, 77.96753},{17.20000, 78.00000}
};

// auto size
int n = sizeof(path) / sizeof(path[0]);

int i = 0;

// shared values (for sync)
float currLat, currLon, currDev;


// GPS + processing task
void gpsTask(void *pv){
  while(1){

    currLat = actual[i][0];
    currLon = actual[i][1];

    currDev = abs(currLat - path[i][0]) +
              abs(currLon - path[i][1]);

    if(currDev > 0.03){   // tuned threshold
      xEventGroupSetBits(eg, OFF_TRACK);
    } else {
      xEventGroupSetBits(eg, ON_TRACK);
    }

    i = (i + 1) % n;

 vTaskDelay(pdMS_TO_TICKS(1500));
  }
}

// alert + display task
void alertTask(void *pv){
  while(1){
    auto bits = xEventGroupWaitBits(
      eg,
      ON_TRACK | OFF_TRACK,
      pdTRUE,
      pdFALSE,
      portMAX_DELAY
    );
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.print("Lat:");
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}

// alert + display task
void alertTask(void *pv){
  while(1){
    auto bits = xEventGroupWaitBits(
      eg,
      ON_TRACK | OFF_TRACK,
      pdTRUE,
      pdFALSE,
      portMAX_DELAY
    );
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.print("Lat:");
    display.print(currLat, 4);

    display.setCursor(0,10);
    display.print("Lon:");
    display.print(currLon, 4);





    display.setCursor(0,20);
    display.print("Dev:");
    display.print(currDev, 4);

    display.setTextSize(2);
    display.setCursor(0,35);

    if(bits & OFF_TRACK){
      digitalWrite(LED, HIGH);
      digitalWrite(BUZZ, HIGH);
      display.print("ALERT!");
    } else {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZ, LOW);
      display.print("SAFE");
    }

    display.display();
  }
}

void setup(){
  pinMode(LED, OUTPUT);
pinMode(BUZZ, OUTPUT);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);

  eg = xEventGroupCreate();

  xTaskCreate(gpsTask, "gps", 4000, NULL, 1, NULL);
  xTaskCreate(alertTask, "alert", 4000, NULL, 1, NULL);
}

void loop(){}


