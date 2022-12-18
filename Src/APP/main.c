
#include "../MCAL/GPIO/Dio.h"

int main(void)
{
    for(;;)
    {
        Dio_WriteChannel(DIO_LED_CHL_INDEX,STD_HIGH);
    }
    
}