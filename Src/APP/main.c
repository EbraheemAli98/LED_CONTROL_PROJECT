#include "../MCAL/GPIO/Port.h"
#include "../MCAL/GPIO/Dio.h"

int main(void)
{
    Port_Init(&Port_PinConfig);
    for(;;)
    {
        Dio_WriteChannel(DIO_LED_CHL_INDEX,STD_HIGH);
    }
    
}