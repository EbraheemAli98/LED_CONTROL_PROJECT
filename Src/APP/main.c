#include "../HAL/BUTTON/Button.h"
#include "../MCAL/Gpt/Gpt.h"
#include "../HAL/LED/Led.h"
#include "../MCAL/GPIO/Port.h"

void LED_Blink(void);

int main(void)
{
    Port_Init(&Port_PinConfig);
    Button_Init();
    Gpt_ChannelConfigurationStr.ChannelSelect[GPT_CHL0_ID].GptNotification = LED_Blink;
    Gpt_Init(&Gpt_ChannelConfigurationStr);
    Gpt_EnableNotification(GPT_CHL0_ID);
    
    for(;;)
    {
        
    }   
}

void LED_Blink(void)
{
    Dio_WriteChannel(LED_CHANNEL_ID,LED_ON);
}