#include "usb_mgr.h"

uint8_t TxBuffer[] = "Hello World! From STM32 USB CDC Device To Virtual COM Port\r\n";
uint8_t TxBufferLen = sizeof(TxBuffer);
uint8_t rx_buf[300];
uint16_t rx_len;
uint8_t tx_buf[300];
bool has_rx=0;


void usb_OnDataReceived(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,1);
    rx_buf[0]=0x69;
    CDC_Transmit_FS(rx_buf, rx_len);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,0);
}

void USB_CDC_RxHandler(uint8_t* rx_buf_cdc, uint32_t len)
{
    // CDC_Transmit_FS(rx_buf_cdc, len);
    // CDC_Transmit_FS(TxBuffer, TxBufferLen);

   memcpy(rx_buf,rx_buf_cdc,len);
   rx_len = len;
   has_rx=1;
}

void usb_mainloop(void)
{
    if(has_rx)
    {
        has_rx=0;
        usb_OnDataReceived();
    }
}
