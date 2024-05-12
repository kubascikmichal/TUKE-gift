#include "Panel/Panel.h"

SemaphoreHandle_t rtcMut;
void playerTask(void *param)
{
    Player *player = static_cast<Player *>(param);
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(100);
    while (true)
    {
        uint32_t ret = ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
        if (ret > 0)
        {
            player->playCustom();
        }
    }
}

void PanelTask(void *param)
{
    Panel *p = static_cast<Panel *>(param);
    p->run();
}

void setup()
{
    Player *pl = new Player();
    Serial.begin(115200);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
    TaskHandle_t timeout;
    xTaskCreatePinnedToCore(playerTask, "MusicPlayer", 8192, pl, 1, &timeout, 1);
    Panel *p = new Panel();
    p->setup(s, mutex, timeout);
    p->setRTC(rtc, rtcMut);
    xTaskCreatePinnedToCore(PanelTask, "Panel", 8192, p, 2, NULL, 1);
}

void loop()
{
}