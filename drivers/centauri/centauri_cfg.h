#ifndef CENT_CFG_H
#define CENT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CENTAURI_HOSTIF_TRIG_GPIO   0

#define CENTAURI_SWITCH_CTRL1_EN	1
#define CENTAURI_SWITCH_CTRL1_PIN	4
#define CENTAURI_SWITCH_CTRL1_RX 	1
#define CENTAURI_SWITCH_CTRL1_TX 	0
#define CENTAURI_SWITCH_CTRL2_EN	1
#define CENTAURI_SWITCH_CTRL2_PIN	5
#define CENTAURI_SWITCH_CTRL2_RX 	0
#define CENTAURI_SWITCH_CTRL2_TX 	1

#define CENTAURI_SWITCH_ELNA_EN	    1
#define CENTAURI_SWITCH_ELNA_PIN	1
#define CENTAURI_SWITCH_ELNA_AH     1

#define SW_CTRL1_GPIO_POS			0
#define SW_CTRL1_GPIO_MASK			0x0000000f
#define SW_CTRL1_RX_POS				4
#define SW_CTRL1_RX_MASK			0x00000010
#define SW_CTRL1_TX_POS				5
#define SW_CTRL1_TX_MASK			0x00000020
#define SW_CTRL1_EN_POS				6
#define SW_CTRL1_EN_MASK			0x00000040
#define SW_CTRL2_GPIO_POS			8
#define SW_CTRL2_GPIO_MASK			0x00000f00
#define SW_CTRL2_RX_POS				12
#define SW_CTRL2_RX_MASK			0x00001000
#define SW_CTRL2_TX_POS				13
#define SW_CTRL2_TX_MASK			0x00002000
#define SW_CTRL2_EN_POS				14
#define SW_CTRL2_EN_MASK			0x00004000
#define SW_ANT_GPIO_POS			    16
#define SW_ANT_GPIO_MASK			0x000f0000
#define SW_ANT_EN_POS				22
#define SW_ANT_EN_MASK			    0x00400000
#define SW_ELNA_GPIO_POS			24
#define SW_ELNA_GPIO_MASK			0x0f000000
#define SW_ELNA_AH_POS				28
#define SW_ELNA_AH_MASK			    0x10000000
#define SW_ELNA_EN_POS				30
#define SW_ELNA_EN_MASK			    0x40000000

/************************/
/* PMU_RTN_RX_PARAM1 */
#define EARLY_DROP_RX_MAXLEN_POS	0
#define EARLY_DROP_RX_MAXLEN_MASK	0x00000fff
#define EARLY_DROP_SFD_TIMEOUT_POS	12
#define EARLY_DROP_SFD_TIMEOUT_MASK	0x000ff000
#define LISTEN_THR_POS				20
#define LISTEN_THR_MASK				0x0ff00000
#define LISTEN_CNT_POS				28
#define LISTEN_CNT_MASK				0xf0000000

#define PMU_CGCR_IDLE				0x3D1

/************************/
/* PMU_RTN_RX_PARAM2 */
#define PKT_DROP_THR_POS	0
#define PKT_DROP_THR_MASK	0x00000007
#define PKT_DROP_CNT_POS	4
#define PKT_DROP_CNT_MASK	0x000000F0
#define PKT_OVER_THR_POS	8
#define PKT_OVER_THR_MASK	0x00000700
#define PKT_OVER_CNT_POS	12
#define PKT_OVER_CNT_MASK	0x0000F000
#define CCA_MODE_POS		16
#define CCA_MODE_MASK		0x00030000
#define CCA_THR_POS			20
#define	CCA_THR_MASK		0x0FF00000
#define CCA_DELAY_POS		28
#define	CCA_DELAY_MASK		0xF0000000	// symbols

#define CCA_MODE			(3)
#define CCA_THRESHOLD		(90)	// absolute value
#define CCA_DELAY			(15)	// symbols

/************************/
/* PMU_RTN_LP_LISTEN */
#define LP_LISTEN_ON_PERIOD_POS		0
#define LP_LISTEN_ON_PERIOD_MASK	0x000003FF	//symbols
#define LP_LISTEN_OFF_PERIOD_POS	12
#define LP_LISTEN_OFF_PERIOD_MASK	0x00FFF000	//us
#define LP_LISTEN_OFF_STATE_POS		24
#define LP_LISTEN_OFF_STATE_MASK	0x03000000	//state: 0: idle, 1:rx_standby

/* PMU_RTN_SYS_CTRL */
#define RTN_SYS_CTRL_PROBE_ENABLE_POS   0
#define RTN_SYS_CTRL_PROBE_ENABLE_MASK  0x000000fful
#define RTN_DIV_PDTO_POS   8
#define RTN_DIV_PDTO_MASK  0x0000ff00ul
#define RTN_DIV_LOW_TH_POS   16
#define RTN_DIV_LOW_TH_MASK  0x00ff0000ul   // in minus dbm
#define RTN_DIV_HIGH_TH_POS   24
#define RTN_DIV_HIGH_TH_MASK  0xff000000ul  // in minus dbm


typedef enum __SYS_SWITCH_T {
    SWITCH_MSG_Q_ON                 = 0x00000001ul,
    SWITCH_WAITBY_NOP_ON            = 0x00000004ul,	
    SWITCH_MAC_INT_QUEUE_ON         = 0x00000008ul,
    SWITCH_PHY_INT_QUEUE_ON         = 0x00000010ul,
    SWITCH_BYPASS_ROM       		= 0x00000020ul,    
    SWITCH_CAL_PERIOD_ON            = 0x00000040ul,
    SWITCH_CAL_PERIOD_32K_ON        = 0x00000080ul,
    SWITCH_LATER_CHK_CAL32K_DOWN    = 0x00000100ul,    
    SWITCH_CAL_PERIOD_ADC		    = 0x00000200ul,
	SWITCH_CAL_PERIOD_VCO		    = 0x00000400ul,
    SWITCH_CAL_PERIOD_IQ		    = 0x00000800ul,	    
    SWITCH_EARLY_DROP_RX	        = 0x00001000ul,    
    SWITCH_SFD_TIMEOUT_RESTART		= 0x00002000ul,
    SWITCH_PKT_DROP_RESTART			= 0x00004000ul,
    SWITCH_PKT_OVER_RESTART			= 0x00008000ul,
	SWITCH_LP_LISTEN_ON 			= 0x00010000ul,
	SWITCH_LISTEN_THR_ON 			= 0x00020000ul,
	SWITCH_NO_WFI					= 0x00040000ul,
    SWITCH_FAST_RX_RESTART_PATCH    = 0x00100000ul,
    SWITCH_GEAR_SHIFT_ON            = 0x00400000ul,
    SWITCH_FCS_FILTER               = 0x01000000ul, 
    SWITCH_ADDRESS_FILTER           = 0x02000000ul,  
    SWITCH_EXT_LNA                  = 0x10000000ul, 
    SWITCH_FORCE_RXEND_PATCH        = 0x20000000ul, 
} SYS_SWITCH_T;

/* CENT_RTN_REG_SYS_CTRL */
#define RTN_REG_SYS_CTRL_PROBE_ENABLE_POS       0
#define RTN_REG_SYS_CTRL_PROBE_ENABLE_MASK      0x0000FF00

/* CENT_RTN_REG_PROBE_PIN */
#define RTN_REG_PROBE_PIN_POS                   0
#define RTN_REG_PROBE_PIN_MASK                  0xFFFFFFFF
#define DRV_PROBE_PIN_DISABLED                  0

#define CENTAURI_PROBE_PIN_CCA               	0
#define CENTAURI_PROBE_PIN_STATE_CHANGE         1
#define CENTAURI_PROBE_PIN_CALB                 DRV_PROBE_PIN_DISABLED
#define CENTAURI_PROBE_PIN_RXPKT_LEN            DRV_PROBE_PIN_DISABLED
#define CENTAURI_PROBE_PIN_MAC_IRQ              DRV_PROBE_PIN_DISABLED
#define CENTAURI_PROBE_PIN_PHY_IRQ              DRV_PROBE_PIN_DISABLED
#define CENTAURI_PROBE_PIN_HCMD_IRQ             2
#define CENTAURI_PROBE_PIN_GEAR_SHIFT           6

enum {
    DRV_PROBE_TYPE_CCA = 0,
    DRV_PROBE_TYPE_STATE_CHANGE,
    DRV_PROBE_TYPE_CALB,
    DRV_PROBE_TYPE_RXPKT_LEN,
    DRV_PROBE_TYPE_MAC_IRQ,
    DRV_PROBE_TYPE_PHY_IRQ,
    DRV_PROBE_TYPE_HCMD_IRQ,
    DRV_PROBE_TYPE_GEAR_SHIFT,    
};

/* CENT_RTN_CALI_SETTING */
typedef enum __RCO32K_MODE {
    RCO32K_THERMAL = 0x00,
    RCO32K_BINARY = 0x01,
}RCO32K_MODE_E;

typedef enum __RCO4M_MODE {
    RCO4M_THERMAL = 0x00,
    RCO4M_BINARY = 0x01,
}RCO4M_MODE_E;

// 00:1000ppm, 01:900ppm, 10:800ppm, 11:700ppm
typedef enum __RCO32K_WIN {
    WIN_32K_1000PPM = 0x00,
    WIN_32K_900PPM = 0x01,
    WIN_32K_800PPM = 0x02,
    WIN_32K_700PPM = 0x03,
}RCO32K_WIN_E;

// 00:1000ppm, 01:900ppm, 10:800ppm, 11:700ppm
typedef enum __RCO4M_WIN {
    WIN_4M_600PPM = 0x00,
    WIN_4M_800PPM = 0x01,
    WIN_4M_1000PPM = 0x02,
    WIN_4M_1200PPM = 0x03,
}RCO4M_WIN_E;

typedef struct __CALI_SETTING_T {
    uint32_t cali_32k_win : 2;
    uint32_t cali_32k_mode : 1;
    uint32_t rev0 : 5;
    uint32_t cali_32k_timeout : 8;  // ms
    uint32_t cali_4m_win : 2;
    uint32_t cali_4m_mode : 1;
    uint32_t rev1 : 5;
    uint32_t cali_4m_timeout : 8;   // ms
}CALI_SETTING_T;

#define RTN_32K_CTRL_TARGET_POS     0
#define RTN_32K_CTRL_TARGET_MASK    0x000ffffful
#define RTN_32K_CTRL_RES_POS        20
#define RTN_32K_CTRL_RES_MASK       0x00f00000
#define RTN_32K_CTRL_MODE_POS       24
#define RTN_32K_CTRL_MODE_MASK      0x03000000ul
#define RTN_32K_CTRL_WAKEUP_POS     26
#define RTN_32K_CTRL_WAKEUP_MASK    0x04000000ul
#define RTN_32K_CTRL_WAKEUP         RTN_32K_CTRL_WAKEUP_MASK
#define RTN_32K_CTRL_ACT_POS        27
#define RTN_32K_CTRL_ACT_MASK       0x08000000ul
#define RTN_32K_CTRL_ENABLE         RTN_32K_CTRL_ACT_MASK
#define RTN_32K_CTRL_DIV_POS        28
#define RTN_32K_CTRL_DIV_MASK       0x70000000ul
#define RTN_32K_CTRL_DIV_ENABLE     0x80000000ul

#define TIMER32K_TICK_MAX           RTN_32K_CTRL_TARGET_MASK

typedef struct __TIMER_32K_FIELDS_T {
    uint32_t target : 20;
    uint32_t resl : 4;
    uint32_t mode : 2;
    uint32_t wakeup : 1;
    uint32_t enable : 1;
    uint32_t div : 3;
    uint32_t div_en : 1;
} TIMER_32K_FIELDS_T;

typedef enum __SLEEP_TIME_RES {
    SLP_RES_125us,    // max 32    secs
    SLP_RES_250us,    // max 32    secs
    SLP_RES_500us,    // max 32    secs
    SLP_RES_1ms,      // max 32    secs
    SLP_RES_2ms,      // max 64    secs
    SLP_RES_4ms,      // max 128   secs
    SLP_RES_8ms,      // max 256   secs
    SLP_RES_16ms,     // max 512   secs
    SLP_RES_32ms,     // max 1024  secs

    SLP_RES_ALL,
} SLEEP_TIME_RES;

typedef enum __TIMER32K_MODE {
    TIMER32K_TIE = 0,
    TIMER32K_RELOAD = 1,
    TIMER32K_FREERUN = 2,           /* not to use TIMER32K_FREERUN implement sleep */
} TIMER32K_MODE;

typedef enum __TIMER32K_DIV {
    TIMER32K_DIV2,
    TIMER32K_DIV4,
    TIMER32K_DIV8,
    TIMER32K_DIV16,
    TIMER32K_DIV32,
} TIMER32K_DIV;

void cent_spi_delay_config(void);

void cent_switch_fun_disable(SYS_SWITCH_T fun_disable);

void cent_switch_fun_enable(uint32_t fun_enable);

uint32_t is_cent_switch_fun_enable(uint32_t fun_enable);

void cent_if_config(void);

void cent_misc_config(int bufsz);

void cent_radio_config(uint32_t Frequency);

void cent_elna_enable(uint32_t enable);

#ifdef __cplusplus
}
#endif

#endif /* CENT_CFG_H */
