#include "vtprober.h"
#include "phy_csr.h"
#include "mac_csr.h"
#include "pmu_csr.h"
#include "TransceiverCsr.h"
#include "TransceiverInit.h"

#include "centauri_host.h"
#include "centauri_prober.h"
#include "centauri_cfg.h"
#include "centauri_pmu_csr.h"
#include "centauri_queue.h"
#include "centauri_cmd.h"
#include "centauri_mac.h"

#include <stdbool.h>

#define GPIO_NOTIFY_EVENT_MASK  (MAC_IRQn_MASK | \
                                 PHY_IRQn_MASK | \
                                 STATE_CHANGE_MASK | \
                                 CMD_ACK_MASK | \
                                 CAL_DONE_MASK | \
                                 CCMD_STATUS_MASK | \
                                 CMD_ERR_MASK | \
                                 SLEEP_WAKEUP_MASK | \
                                 POWER_WAKEUP_MASK)

#if HOST_IF_ON
uint32_t rx16m_en;
uint32_t lowsideinj;
#endif

void cent_cca_delay(void)
{
    uint32_t rx_param2;

    cent_spi_readW(CENT_RTN_RX_PARAM2, &rx_param2);

    rx_param2 &= ~0xF0000000;
    rx_param2 |= (CCA_DELAY<<CCA_DELAY_POS);

    cent_spi_writeW(CENT_RTN_RX_PARAM2, rx_param2);
}

void cent_rx_early_drop(int bufsz)
{
    uint32_t rx_param1;

    cent_spi_readW(CENT_RTN_RX_PARAM1, &rx_param1);

	rx_param1 &= ~EARLY_DROP_RX_MAXLEN_MASK;
	rx_param1 |= bufsz & EARLY_DROP_RX_MAXLEN_MASK;

	cent_spi_writeW(CENT_RTN_RX_PARAM1, rx_param1);

	cent_switch_fun_enable(SWITCH_EARLY_DROP_RX);
}

void cent_rx_listen_threshold(void)
{
	uint32_t rx_param1;

    cent_spi_readW(CENT_RTN_RX_PARAM1, &rx_param1);

	rx_param1 &= ~LISTEN_THR_MASK;
	rx_param1 |= ((100*2) << LISTEN_THR_POS) & LISTEN_THR_MASK;

	rx_param1 &= ~LISTEN_CNT_MASK;
	rx_param1 |= (15 << LISTEN_CNT_POS) & LISTEN_CNT_MASK;

	cent_spi_writeW(CENT_RTN_RX_PARAM1, rx_param1);

	cent_switch_fun_enable(SWITCH_LISTEN_THR_ON);
}

void cent_rx_sfd_timeout(void)
{
	uint32_t rx_param1;

    cent_spi_readW(CENT_RTN_RX_PARAM1, &rx_param1);

	rx_param1 &= ~EARLY_DROP_SFD_TIMEOUT_MASK;

	rx_param1 |= (0xff << EARLY_DROP_SFD_TIMEOUT_POS) & EARLY_DROP_SFD_TIMEOUT_MASK;

	cent_spi_writeW(CENT_RTN_RX_PARAM1, rx_param1);

	cent_switch_fun_enable(SWITCH_SFD_TIMEOUT_RESTART);
}

void cent_rx_low_power_listen(void)
{
	uint32_t rx_lp;

	rx_lp = 32 & LP_LISTEN_ON_PERIOD_MASK;	//symbols
	rx_lp |= (20 << LP_LISTEN_OFF_PERIOD_POS) & LP_LISTEN_OFF_PERIOD_MASK;	//us
	rx_lp |= (1 << LP_LISTEN_OFF_STATE_POS) & LP_LISTEN_OFF_STATE_MASK;	//state: 0: idle, 1:rx_standby

	cent_spi_writeW(CENT_RTN_LP_LISTEN, rx_lp);

	cent_switch_fun_enable(SWITCH_LP_LISTEN_ON);
}

void cent_trx_switch_ctrl_setting(void)
{
	uint32_t sw_ctrl;

	if (CENTAURI_SWITCH_CTRL1_EN) {
		sw_ctrl = (SW_CTRL1_EN_MASK) |
                  (CENTAURI_SWITCH_CTRL1_RX<<SW_CTRL1_RX_POS) |
                  (CENTAURI_SWITCH_CTRL1_TX<<SW_CTRL1_TX_POS) |
                  (CENTAURI_SWITCH_CTRL1_PIN<<SW_CTRL1_GPIO_POS);
    } else {
		sw_ctrl = 0;
    }

	if(CENTAURI_SWITCH_CTRL2_EN) {
		sw_ctrl |= SW_CTRL2_EN_MASK |
                   (CENTAURI_SWITCH_CTRL2_RX<<SW_CTRL2_RX_POS) |
                   (CENTAURI_SWITCH_CTRL2_TX<<SW_CTRL2_TX_POS) |
                   (CENTAURI_SWITCH_CTRL2_PIN<<SW_CTRL2_GPIO_POS);
    }	

	cent_spi_writeW(CENT_RTN_SW_CTRL, sw_ctrl);
}

void cent_elna_ctrl_setting(void)
{
	uint32_t sw_ctrl, sys_ctrl;
    
    if (CENTAURI_SWITCH_ELNA_EN) {
        cent_spi_readW(CENT_RTN_SW_CTRL, &sw_ctrl);

        sw_ctrl |= (SW_ELNA_EN_MASK) |
                   (CENTAURI_SWITCH_ELNA_PIN<<SW_ELNA_GPIO_POS) |
                   (CENTAURI_SWITCH_ELNA_AH<<SW_ELNA_AH_POS);

	    cent_spi_writeW(CENT_RTN_SW_CTRL, sw_ctrl);

        cent_spi_readW(CENT_RTN_REG_SYS_CTRL, &sys_ctrl);
        sys_ctrl &= RTN_SYS_CTRL_PROBE_ENABLE_MASK;
        sys_ctrl |= (0xff << RTN_DIV_PDTO_POS) & RTN_DIV_PDTO_MASK;
        cent_spi_writeW(CENT_RTN_REG_SYS_CTRL, sys_ctrl);
    }
}

void cent_elna_enable(uint32_t enable)
{
    if (enable == 2) {
        cent_switch_fun_enable(SWITCH_EXT_LNA);
        cent_cmd_elna_enable(1);
    } else {
        cent_switch_fun_disable(SWITCH_EXT_LNA);
        cent_cmd_elna_enable(enable?1:0);
    }
}

void cent_probe_pin_setting(bool enable, uint32_t type, uint32_t pin)
{
    uint32_t sys_ctrl;
    uint32_t probe_pin;

    cent_spi_readW(CENT_RTN_REG_SYS_CTRL, &sys_ctrl);
    cent_spi_readW(CENT_RTN_REG_PROBE_PIN, &probe_pin);

    /* setup probe pin */
    if (enable) {
        /* enable */
        sys_ctrl |= (1 << (RTN_REG_SYS_CTRL_PROBE_ENABLE_POS + type));
        /* set pin to DRV_PROBE_PIN_DISABLED */
        probe_pin &= ~(0xF << (RTN_REG_PROBE_PIN_POS + type * 4));
        probe_pin |= (pin << (RTN_REG_PROBE_PIN_POS + type * 4));
    } else {
        /* disable */
        sys_ctrl &= ~(1 << (RTN_REG_SYS_CTRL_PROBE_ENABLE_POS + type));
        /* set pin to DRV_PROBE_PIN_DISABLED */
        probe_pin &= ~(0xF << (RTN_REG_PROBE_PIN_POS + type * 4));
    }

    cent_spi_writeW(CENT_RTN_REG_SYS_CTRL, sys_ctrl);
    cent_spi_writeW(CENT_RTN_REG_PROBE_PIN, probe_pin);
}

static uint32_t fun_switch = 0;

void cent_switch_fun_disable(SYS_SWITCH_T fun_disable)
{
    fun_switch &= ~fun_disable;
    cent_spi_writeW(CENT_RTN_REG_FUN_SWITCH, fun_switch);
}

void cent_switch_fun_enable(uint32_t fun_enable)
{
    fun_switch |= fun_enable;
    cent_spi_writeW(CENT_RTN_REG_FUN_SWITCH, fun_switch);
}

uint32_t is_cent_switch_fun_enable(uint32_t fun_enable)
{
	if (fun_switch & fun_enable) {
		return 1;
    }
	return 0;
}

void cent_cali_32k_setting(RCO32K_WIN_E win, RCO32K_MODE_E mode, uint8_t timeout)
{
    CALI_SETTING_T cal_setting;

    cal_setting.cali_32k_mode = mode;
    cal_setting.cali_32k_win = win;
    cal_setting.cali_32k_timeout = timeout;

    cent_spi_regW(CENT_RTN_CALI_SETTING, *((uint32_t*)&cal_setting), 0xffff0000);
}

void cent_cali_4m_setting(RCO4M_WIN_E win, RCO4M_MODE_E mode, uint8_t timeout)
{
    CALI_SETTING_T cal_setting;

    cal_setting.cali_4m_mode = mode;
    cal_setting.cali_4m_win = win;
    cal_setting.cali_4m_timeout = timeout;

    cent_spi_regW(CENT_RTN_CALI_SETTING, *((uint32_t*)&cal_setting), 0x0000ffff);
}

void cent_sleep_mode_setting(TIMER32K_MODE mode, SLEEP_TIME_RES resl)
{
    volatile TIMER_32K_FIELDS_T timer_setting;

    *((uint32_t*)&timer_setting) = 0;

    timer_setting.mode = mode;
    timer_setting.resl = resl;
    if (resl > SLP_RES_1ms) {
        switch (resl) {
        case SLP_RES_2ms:           // max 64 secs
            timer_setting.div = TIMER32K_DIV2;
            break;
        case SLP_RES_4ms:           // max 128 secs
            timer_setting.div = TIMER32K_DIV4;
            break;
        case SLP_RES_8ms:           // max 256 secs
            timer_setting.div = TIMER32K_DIV8;
            break;
        case SLP_RES_16ms:          // max 512 secs
            timer_setting.div = TIMER32K_DIV16;
            break;
        case SLP_RES_32ms:          // max 1024 secs
            timer_setting.div = TIMER32K_DIV32;
            break;
        default:
            break;
        }
        timer_setting.div_en = 1;
    }

    timer_setting.enable = 1;
    timer_setting.wakeup = 1;

    cent_spi_writeW(CENT_RTN_32K_CTRL_ADDR, *((uint32_t*)&timer_setting));
}

static void cent_int_config(void)
{
    cent_spi_writeW(CENT_RTN_HOSTIF_INT_MASK_0, (CENTAURI_HOSTIF_TRIG_GPIO << 28) | GPIO_NOTIFY_EVENT_MASK);

	//cent_spi_writeW(CENT_RTN_HOSTIF_PHYINT, 0x019);   // PMB, SFD, TXCMP
    //cent_spi_writeW(CENT_RTN_HOSTIF_PHYINT, 0x01b);   // PMB, SFD, RX_PKT, TXCMP
    cent_spi_writeW(CENT_RTN_HOSTIF_PHYINT, 0x1009);      // PMB, PHR, TXCMP
    //cent_spi_writeW(CENT_RTN_HOSTIF_PHYINT, 0x01);    // TXCMP
}

void cent_probe_pin_config(void)
{
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_CCA, CENTAURI_PROBE_PIN_CCA);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_STATE_CHANGE, CENTAURI_PROBE_PIN_STATE_CHANGE);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_CALB, CENTAURI_PROBE_PIN_CALB);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_RXPKT_LEN, CENTAURI_PROBE_PIN_RXPKT_LEN);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_MAC_IRQ, CENTAURI_PROBE_PIN_MAC_IRQ);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_PHY_IRQ, CENTAURI_PROBE_PIN_PHY_IRQ);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_HCMD_IRQ, CENTAURI_PROBE_PIN_HCMD_IRQ);
    cent_probe_pin_setting(false, DRV_PROBE_TYPE_GEAR_SHIFT, CENTAURI_PROBE_PIN_GEAR_SHIFT);
}

void cent_spi_delay_config(void)
{
    vtprober_set_delay(2);
}

void cent_if_config(void)
{
    cent_spi_delay_config();
    cent_int_config();
}

#define TIMEOUT_BINARY_MODE         20
#define TIMEOUT_THERMAL_MODE        60

void cent_misc_config(int bufsz)
{   
    cent_probe_pin_config();
	cent_trx_switch_ctrl_setting();
    cent_elna_ctrl_setting();

    cent_sleep_mode_setting(TIMER32K_TIE, SLP_RES_1ms);

    cent_cali_32k_setting(WIN_32K_900PPM, RCO32K_BINARY, TIMEOUT_BINARY_MODE);    
    cent_cali_4m_setting(WIN_4M_1200PPM, RCO4M_BINARY, TIMEOUT_BINARY_MODE);

    cent_cmd_period_config(DEFAULT_PERIOD_TIME, 0);

	cent_cca_delay();
	cent_rx_early_drop(bufsz);
	//cent_rx_listen_threshold();
	cent_rx_sfd_timeout();
    
	//Load/Store Enable for power saving mode
	cent_spi_regW(PMU_CSR__PMU_CR, PMU_CR__CSR_LDSTR_EN_MASK, NOTCARE);

    cent_switch_fun_enable(SWITCH_FORCE_RXEND_PATCH);
    cent_switch_fun_enable(SWITCH_WAITBY_NOP_ON);
}

void cent_radio_config(uint32_t Frequency)
{
	uint32_t rf_channel_rg;

    if (Frequency) {
    	rf_channel_rg = CentauriCsrRead(RF_CHANNEL_FREQ);
		rf_channel_rg = rf_channel_rg & 0xc000000;
        CentauriCsrWrite(RF_CHANNEL_FREQ, rf_channel_rg|Frequency);
    }

    TransceiverPmeLenSetByRate(RomSymRateRead());   //rex, 20180830

	/* IQC setting */
	CentauriCsrWrite(0x4002c0d0,0x2A878000);
	CentauriCsrWrite(0x4002c0c8,0xC880000);

 	if (cent_get_version() == 0x7000B3) {
        /* B3 */
        /* Gear Shift Ver.2 Setting */
        cent_switch_fun_enable(SWITCH_GEAR_SHIFT_ON);
        CentauriCsrWrite(0x4002c0b4,0xF1B1B1B1);	
        CentauriCsrWrite(0x4002c0b8,0x00066180);
        CentauriCsrWrite(0x40028030,0x00000000);
        CentauriCsrWrite(0x40028008,0xC000E07);

        /* LQI issue */
        #if 0
        U32 csr_tmp;
        csr_tmp = CentauriCsrRead(0x4002c0b0);
        csr_tmp = (csr_tmp & 0xFFFFF7FF);
        CentauriCsrWrite(0x4002c0b0,csr_tmp);
        #endif
 	} else { // B4 set here
        cent_switch_fun_enable(SWITCH_GEAR_SHIFT_ON);
        CentauriCsrWrite(0x4002c0b4,0xF1B1B103);
	}

#if HOST_IF_ON	
	rx16m_en = RomRx16MhzEnRead(); // load 16MHz mode flag in init state,keep it in the last
	lowsideinj = RomLowSideInjRead();
#endif
}
