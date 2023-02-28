#include "usb_comm.h"
#include "dfs_proto.h"

Usb_comm::Usb_comm(USBD_HandleTypeDef *usb_handle, unsigned int buff_size, unsigned int send_buff_size,usb_idle_callback callback)
    : Usb_tranceiver(usb_handle, buff_size, send_buff_size,callback)
{
}

void Usb_comm::process(void)
{

}

Usb_comm::~Usb_comm()
{
}
