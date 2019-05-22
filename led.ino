
#include <ArduinoJson.h>
#include "BluetoothSerial.h"
#include "FS.h"
#include "SPIFFS.h"
BluetoothSerial SerialBT;
//faz o controle do temporizador (interrupção por tempo)
hw_timer_t *timer = NULL;

//função que o temporizador irá chamar, para reiniciar o ESP32
void IRAM_ATTR resetModule() {
  ets_printf("(watchdog) reiniciar\n"); //imprime no log
  esp_restart(); //reinicia o chip
}

//função que o configura o temporizador
void configureWatchdog()
{
  timer = timerBegin(0, 80, true); //timerID 0, div 80
  //timer, callback, interrupção de borda
  timerAttachInterrupt(timer, &resetModule, true);
  //timer, tempo (us), repetição
  timerAlarmWrite(timer, 5000000, true);
  timerAlarmEnable(timer); //habilita a interrupção //enable interrupt
}
