#ifndef CENTAURI_HOST_H
#define CENTAURI_HOST_H

#ifdef __cplusplus
extern "C" {
#endif

/* China standard DL/T 698.44  */
#define DLT_698p44_FLAG 0

/* centauri front-end state */
#define FRONT_END_STATE_ELNA_EN          0x1
#define FRONT_END_STATE_EPA_EN           0x2
#define FRONT_END_STATE_ANT_DIVERSITY_EN 0x4

#define FCS_32 0
#define FCS_16 1
#define FCS_NONE 2

#define FCS_MODE FCS_32

#define DEFAULT_PERIOD_TIME 5000

typedef enum {
    /* below command will send to centauri */
	RF_HCMD_INIT,
	RF_HCMD_SYSTEM_STATUS,
	RF_HCMD_IDLE,
    RF_HCMD_SLEEP,
	RF_HCMD_SHUTDOWN,
    RF_HCMD_CALIB_32K,
    RF_HCMD_CALIB_4M,
    RF_HCMD_CALIB_VCO,
	RF_HCMD_CALIB_IQ,
	RF_HCMD_CALIB_RX_ADC,
	RF_HCMD_CALIB_PERIOD_CHG, 
	RF_HCMD_CCA,
	RF_HCMD_TX,
	RF_HCMD_TX_REFILLED,
	RF_HCMD_RX,
	RF_HCMD_RX_READED,
	RF_HCMD_TXPWR,
	RF_HCMD_RSSI,
	RF_HCMD_RSSI_OFFSET,	
	RF_HCMD_BAND,
	RF_HCMD_MODI,
	RF_HCMD_RATE,
	RF_HCMD_TXCW,
	RF_HCMD_TXCM,
	RF_HCMD_GFILTER,
	RF_HCMD_PSDU_ORDER,
	RF_HCMD_DW,
	RF_HCMD_PMB,
	RF_HCMD_RXLP,
	RF_HCMD_PASEL,
	RF_HCMD_DCTUNE,
	RF_HCMD_ADC,	
	RF_HCMD_SW_CTRL_TEST,
	RF_HCMD_GPIO_TEST,
	RF_HCMD_STATE_CHANGE,	
	RF_HCMD_MAC_LOOPBACK,
	RF_HCMD_STAT_CLEAR,
    RF_HCMD_ANTENNA,
    RF_HCMD_ELNA,	
} RF_HCMD_CMD_T;

typedef enum {
    RF_EVENT_PMU_HOST_IRQn = 1,
    RF_EVENT_MAC_IRQn = 2,
    RF_EVENT_PHY_IRQn = 3,

    RF_EVENT_STATE_CHANGE = 16,
    RF_EVENT_PMB_DET = 17,
    RF_EVENT_CMD_ACK = 18,
    RF_EVENT_STATUS = 19,
    RF_EVENT_CMD_ERR = 20,
    RF_EVENT_CAL_HANDLE = 21,
    RF_EVENT_SLEEP_WAKEUP = 22,
    RF_EVENT_POWER_WAKEUP = 23,
} CENT_EVENT_T;

typedef enum {
    PMU_HOST_IRQn_MASK = (0x01 << RF_EVENT_PMU_HOST_IRQn),
    MAC_IRQn_MASK = (0x01 << RF_EVENT_MAC_IRQn),
    PHY_IRQn_MASK = (0x01 << RF_EVENT_PHY_IRQn),

    STATE_CHANGE_MASK = (0x01 << RF_EVENT_STATE_CHANGE),
    PMB_DET_MASK = (0x01 << RF_EVENT_PMB_DET),
    CMD_ACK_MASK = (0x01 << RF_EVENT_CMD_ACK),
    CCMD_STATUS_MASK = (0x01 << RF_EVENT_STATUS),
    CMD_ERR_MASK = (0x01 << RF_EVENT_CMD_ERR),
    CAL_DONE_MASK = (0x01 << RF_EVENT_CAL_HANDLE),
    SLEEP_WAKEUP_MASK = (0x01 << RF_EVENT_SLEEP_WAKEUP),
    POWER_WAKEUP_MASK = (0x01 << RF_EVENT_POWER_WAKEUP),
} CENT_EVENT_NOTIFY_T;

typedef struct {
    uint32_t cmd : 15;
	uint32_t ack : 1;
    uint32_t param : 16;
} RF_CMD_T;

typedef struct {
    uint32_t cmd : 15;
	uint32_t ack : 1;
    uint32_t param : 16;
} RF_EVENT_T;

typedef enum {
	SYS_IDLE,
	SYS_STANDBY_TX,
	SYS_STANDBY_RX,
	SYS_TX,
	SYS_RX,
	SYS_STATE_ALL,
	SYS_CAL,
	SYS_SLEEP,
	SYS_PWR_DWN,
	SYS_STATE_EVENT_END,
} SYS_STATE_T;

typedef struct CENT_NV_PARA {
    uint32_t series_number;
	uint32_t date;
    uint32_t carrier_frequency;
    uint32_t xtal_offset;
    uint32_t pa_sel;
    uint32_t tx_power_default;
	uint32_t tx_power_cal_offset;
	uint32_t rssi_offset;
}cent_nv_para_t;

struct STAT_INFO_T {
    uint32_t pmb;
    uint32_t sfd;    
    uint32_t phr;
    uint32_t antenna;	
    uint32_t rx_pkt;
    uint32_t tc1;
	uint32_t rssi_less;
	uint32_t rssi_over;
	uint32_t rx_drop_by_len;
	uint32_t tx_pkt;
	uint32_t txcmp;
	uint32_t rxcmp;
	uint32_t fcs_err;
    uint32_t rx_drop_by_addr;
    uint32_t rev2;
    uint32_t rev3;        
};

void cent_cal_load(void);

void cent_get_statistic(struct STAT_INFO_T *info);

uint32_t cent_get_cmd_status(void);

uint32_t cent_get_state(void);

uint32_t cent_get_pkt_len(void);

uint32_t cent_get_pkt_sr(void);

uint32_t cent_get_pkt_lqi(void);

int32_t cent_get_pkt_rssi(void);

int32_t cent_get_rssi(void);

int cent_get_receiving_status(void);

uint32_t cent_nv_get_front_end(void);

int32_t cent_nv_get_elna_rssi_offset(void);

void cent_nv_set_front_end(uint32_t febs);

void cent_nv_set_pa_select(int on);

uint32_t cent_get_version(void);

uint32_t cent_get_adc_status(void);

void cent_set_adc_status(uint32_t status);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_HOST_H */
