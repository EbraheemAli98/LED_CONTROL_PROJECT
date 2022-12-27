#include "BLINK/Led_BlinkingApp.h"


extern volatile uint8 g_Int_flag;

int main(void)
{ 
    App_Init();     /*  an initialization task */
    App_Start(1,1); 
    
    for(;;)
    {
      
    }  
}

