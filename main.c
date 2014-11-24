#include "main.h"


#include "stm32_ub_usb_cdc.h"

int main(void)
{
  PLLInit();

  UB_USB_CDC_Init(); // init
while(1){
	  // check if USB connected
	  if(UB_USB_CDC_GetStatus()==USB_CDC_CONNECTED) {
		// send String to USB (+CarriageReturn+LineFeed)
		UB_USB_CDC_SendString("Test", CRLF);
	  }
}

}
