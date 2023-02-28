#include "cmt2300a_app.h"
#include "cmt2300a_params.h"
#include <string.h>

#define INFINITE 0xFFFFFFFF

static EnumRFStatus g_nNextRFState = RF_STATE_IDLE;
static unsigned char *g_pRxBuffer = NULL;
static unsigned char *g_pTxBuffer = NULL;
static unsigned short g_nRxLength = 0;
static unsigned short g_nTxLength = 0;

static unsigned int g_nRxTimeout = INFINITE;
static unsigned int g_nTxTimeout = INFINITE;
static unsigned int g_nRxTimeCount = 0;
static unsigned int g_nTxTimeCount = 0;
static unsigned int g_nRstTimeCount = 0;
static unsigned int g_nRstTimeout = 20;
static unsigned char g_nInterrutFlags = 0;

bool Cmt2300a_app:: set_handle_func(Handle_func * _handle_func)
{
	if(_handle_func == NULL)
		return false;
	handle_func = _handle_func;
	return true;
}

Cmt2300a_app::Cmt2300a_app(Cmt2300a *_cmt2300a, Get_tick_count _func, bool _ant_sw, Gpio_if *_int1, Gpio_if *_int2)
{
    cmt2300a = _cmt2300a;
    get_tick = _func;
    ant_sw = _ant_sw;
    int1 = _int1;
    int2 = _int2;
	  handle_func = NULL;
    init();
}

Cmt2300a_app::~Cmt2300a_app()
{
  if( cmt2300a != NULL )
  {
    delete cmt2300a;
    cmt2300a = NULL;
  }
  
  if( int1 != NULL )
  {
    delete int1;
    int1 = NULL;
  }
  
  if( int2 != NULL )
  {
    delete int2;
    int2 = NULL;
  }
}

bool Cmt2300a_app::chip_ready(void)
{
  return cmt2300a->exist();
}

void Cmt2300a_app::init(void)
{
    unsigned char tmp;

    cmt2300a->init();

    /* Config registers */
    cmt2300a->config_reg_bank(CMT2300A_CMT_BANK_ADDR, g_cmt2300aCmtBank, CMT2300A_CMT_BANK_SIZE);
    cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank, CMT2300A_SYSTEM_BANK_SIZE);
    cmt2300a->config_reg_bank(CMT2300A_FREQUENCY_BANK_ADDR, g_cmt2300aFrequencyBank, CMT2300A_FREQUENCY_BANK_SIZE);
    cmt2300a->config_reg_bank(CMT2300A_DATA_RATE_BANK_ADDR, g_cmt2300aDataRateBank, CMT2300A_DATA_RATE_BANK_SIZE);
    cmt2300a->config_reg_bank(CMT2300A_BASEBAND_BANK_ADDR, g_cmt2300aBasebandBank, CMT2300A_BASEBAND_BANK_SIZE);
    cmt2300a->config_reg_bank(CMT2300A_TX_BANK_ADDR, g_cmt2300aTxBank, CMT2300A_TX_BANK_SIZE);

    // xosc_aac_code[2:0] = 2
    tmp = (~0x07) & cmt2300a->read_reg(CMT2300A_CUS_CMT10);
    cmt2300a->write_reg(CMT2300A_CUS_CMT10, tmp | 0x02);

    config();
}

void Cmt2300a_app::config(void)
{
    if (ant_sw)
    {
        /* If you enable antenna switch, GPIO1/GPIO2 will output RX_ACTIVE/TX_ACTIVE,
       and it can't output INT1/INT2 via GPIO1/GPIO2 */
        cmt2300a->ant_swtich_enable(0);
    }
    else
    {
        /* Config GPIOs */
        cmt2300a->config_gpio(
            CMT2300A_GPIO1_SEL_INT1 | /* INT1 > GPIO1 */
            CMT2300A_GPIO2_SEL_INT2 | /* INT2 > GPIO2 */
            CMT2300A_GPIO3_SEL_DOUT);

        /* Config interrupt */
        cmt2300a->config_interrupt(
            CMT2300A_INT_SEL_TX_DONE, /* Config INT1 */
            CMT2300A_INT_SEL_PKT_OK   /* Config INT2 */
        );
    }

		cmt2300a->config_gpio(
            CMT2300A_GPIO3_SEL_INT2);
		
    /* Enable interrupt */
    cmt2300a->interrupt_enable(
        CMT2300A_MASK_TX_DONE_EN |
        CMT2300A_MASK_PREAM_OK_EN |
        CMT2300A_MASK_SYNC_OK_EN |
        CMT2300A_MASK_NODE_OK_EN |
        CMT2300A_MASK_CRC_OK_EN |
        CMT2300A_MASK_PKT_DONE_EN);

    /* Disable low frequency OSC calibration */
    cmt2300a->fosc_enable(false);

    /* Use a single 64-byte FIFO for either Tx or Rx */
    //fifo_merge_enable(TRUE);

    //set_fifo_thr(16);

    /* This is optional, only needed when using Rx fast frequency hopping */
    /* See AN142 and AN197 for details */
    //set_afc_overflow_thr(0x27);

    /* Go to sleep for configuration to take effect */
    cmt2300a->to_sleep();
}

void Cmt2300a_app::set_status(EnumRFStatus nStatus)
{
    g_nNextRFState = nStatus;
}

EnumRFStatus Cmt2300a_app::get_status(void)
{
    return g_nNextRFState;
}

unsigned char Cmt2300a_app::get_interrupt_flags(void)
{
    return g_nInterrutFlags;
}

void Cmt2300a_app::start_rx(unsigned char buf[], unsigned short len, unsigned int timeout)
{
    g_pRxBuffer = buf;
    g_nRxLength = len+1;
    g_nRxTimeout = timeout;

    memset(g_pRxBuffer, 0, g_nRxLength);

    g_nNextRFState = RF_STATE_RX_START;
}

void Cmt2300a_app::start_tx(unsigned char buf[], unsigned short len, unsigned int timeout)
{
    g_pTxBuffer = buf;
    g_nTxLength = len+1;
    g_nTxTimeout = timeout;

    g_nNextRFState = RF_STATE_TX_START;
}

unsigned char len = 0;

EnumRFResult Cmt2300a_app::process(void)
{
    EnumRFResult nRes = RF_BUSY;

    switch (g_nNextRFState)
    {
    case RF_STATE_IDLE:
    {   
        nRes = RF_IDLE;
        break;
    }

    case RF_STATE_RX_START:
    {
        cmt2300a->to_stby();
        cmt2300a->clear_interrupt();

        /* Must clear FIFO after enable SPI to read or write the FIFO */
        cmt2300a->read_fifo_enable();
        cmt2300a->clear_rx_fifo();

				HAL_GPIO_WritePin(GPIOB, CMT2300_IO1_Pin , GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, CMT2300_IO2_Pin , GPIO_PIN_RESET);
			
        if (false == cmt2300a->to_rx())
            g_nNextRFState = RF_STATE_ERROR;
        else
            g_nNextRFState = RF_STATE_RX_WAIT;

        g_nRxTimeCount = get_tick();

        break;
    }

    case RF_STATE_RX_WAIT:
    {
			 
        if (ant_sw)
        {
            if (CMT2300A_MASK_PKT_OK_FLG & cmt2300a->read_reg(CMT2300A_CUS_INT_FLAG)) /* Read PKT_OK flag */
            {
                g_nNextRFState = RF_STATE_RX_DONE;
            }
        }
        else
        {
            if (int2->read()) /* Read INT2, PKT_OK */
            {
                g_nNextRFState = RF_STATE_RX_DONE;
            }
        }

        if ((INFINITE != g_nRxTimeout) && ((get_tick() - g_nRxTimeCount) > g_nRxTimeout))
            g_nNextRFState = RF_STATE_RX_TIMEOUT;
				if(handle_func != NULL)
					handle_func();

        break;
    }

    case RF_STATE_RX_DONE:
    {
        cmt2300a->to_stby();
        
        cmt2300a->read_fifo(&len, 1);
        len = len < 31 ? len : 31;
        g_pRxBuffer[0] = len;
        /* The length need be smaller than 32 */
        cmt2300a->read_fifo(g_pRxBuffer+1, len);

        g_nInterrutFlags = cmt2300a->clear_interrupt();
			
        cmt2300a->to_sleep();
        g_nNextRFState = RF_STATE_IDLE;
        nRes = RF_RX_DONE;
        break;
    }

    case RF_STATE_RX_TIMEOUT:
    {
        cmt2300a->to_sleep();

        g_nNextRFState = RF_STATE_IDLE;
        nRes = RF_RX_TIMEOUT;
        break;
    }

    case RF_STATE_TX_START:
    {
        cmt2300a->to_stby();
        cmt2300a->clear_interrupt();

        /* Must clear FIFO after enable SPI to read or write the FIFO */
        cmt2300a->write_fifo_enable();
        cmt2300a->clear_tx_fifo();

        /* The length need be smaller than 32 */
        cmt2300a->write_fifo(g_pTxBuffer, g_nTxLength);
        cmt2300a->set_payload_length(g_nTxLength);
      
        if (0 == (CMT2300A_MASK_TX_FIFO_NMTY_FLG & cmt2300a->read_reg(CMT2300A_CUS_FIFO_FLAG)))
            g_nNextRFState = RF_STATE_ERROR;

				HAL_GPIO_WritePin(GPIOB, CMT2300_IO1_Pin , GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, CMT2300_IO2_Pin , GPIO_PIN_SET);
				
        if (false == cmt2300a->to_tx())
            g_nNextRFState = RF_STATE_ERROR;
        else
            g_nNextRFState = RF_STATE_TX_WAIT;

        g_nTxTimeCount = get_tick();

        break;
    }

    case RF_STATE_TX_WAIT:
    {
        if (ant_sw)
        {
            if (CMT2300A_MASK_TX_DONE_FLG & cmt2300a->read_reg(CMT2300A_CUS_INT_CLR1)) /* Read TX_DONE flag */
            {
                g_nNextRFState = RF_STATE_TX_DONE;
            }
        }
        else
        {
            if (int1->read()) /* Read INT1, TX_DONE */
            {
                g_nNextRFState = RF_STATE_TX_DONE;
            }
        }
        if ((INFINITE != g_nTxTimeout) && ((get_tick() - g_nTxTimeCount) > g_nTxTimeout))
            g_nNextRFState = RF_STATE_TX_TIMEOUT;

        break;
    }

    case RF_STATE_TX_DONE:
    {
        cmt2300a->clear_interrupt();
        cmt2300a->to_sleep();

        g_nNextRFState = RF_STATE_IDLE;
        nRes = RF_TX_DONE;
        break;
    }

    case RF_STATE_TX_TIMEOUT:
    {
        cmt2300a->to_sleep();

        g_nNextRFState = RF_STATE_IDLE;
        nRes = RF_TX_TIMEOUT;
        break;
    }

    case RF_STATE_ERROR:
    {
        cmt2300a->soft_rst();
        
        // delay 20ms for reset
        while((get_tick() - g_nRstTimeout) > g_nRstTimeCount)
  
        cmt2300a->to_stby();
        config();

        g_nNextRFState = RF_STATE_IDLE;
        nRes = RF_ERROR;
        break;
    }

    default:
        break;
    }

    return nRes;
}
