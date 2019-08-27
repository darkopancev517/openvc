#ifndef CENTAURI_QUEUE_H
#define CENTAURI_QUEUE_H

#include "centauri_host.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_MSG_Q_NUM       (14)

#define CENT_MSG_LEN        0x40
#define COMM_INFO_LEN       0x40
#define MAC_IRQ_QUEUE_LEN   0x40
#define PHY_IRQ_QUEUE_LEN   0x40

#define CENT_MSG_QUEUE_ADDR 0x20010500
#define CENT_COMM_INFO_ADDR (CENT_MSG_QUEUE_ADDR + CENT_MSG_LEN)
#define CENT_STAT_INFO_ADDR 0x200104C0

/* msg queue */
#define CCMD_Q_MAX MAX_MSG_Q_NUM

typedef struct __QUEUE_DEF_T {
    volatile uint32_t data[MAX_MSG_Q_NUM];
    volatile uint16_t head;
    volatile uint16_t errcode;
    volatile uint32_t tail;
} QUEUE_DEF_T;

typedef enum __CALI_STATUS_E {
    CALI32K_KICK = 0x01,
    CALI4M_KICK = 0x02,
    CALI32K_DONE = 0x03,
    CALI4M_DONE = 0x04,
    CALI_TIMEOUT = 0x05,
    CALI_BEFORE_IQ = 0x06,
    CALI_BEFORE_DTUNE = 0x07,
    CALI_PERIOD_VCOIQ_DONE = 0x08,
} CALI_STATUS_E;

typedef struct __SYS_STATUS_T {
    uint32_t system : 8;
    uint32_t cali32k : 8;
    uint32_t cali4m : 8;
    uint32_t period_expire : 8;
} SYS_STATUS_T;

typedef struct __COMM_INFO_T
{
    uint32_t carrir_sense;
    uint32_t packet_receiving;	
    SYS_STATUS_T    status;
	uint32_t state;
	uint32_t pkt_sr;
	uint32_t packet_len;
	uint32_t pkt_rssi;
	uint32_t cca_rssi;
	uint32_t lqi;
    uint32_t cca; 	
	uint32_t saradc;
    uint32_t cmd_status;
    uint32_t rx_packet_period;
    uint32_t hcmd_duration;
    uint32_t sys_event;
    uint32_t phy_event;      
} COMM_INFO_T;

typedef struct __STAT_INFO_T
{
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
} STAT_INFO_T;

typedef enum {
    CENT_BUSY,
    CENT_IDLE,
} CENT_STATUS;

typedef struct __CENTAURI_QUEUE_T {
    RF_EVENT_T data[CCMD_Q_MAX];
    volatile uint8_t number;
    uint8_t head;
    uint8_t tail;
    uint8_t read_tail; // read data from centauri index
} CENTAURI_QUEUE_T;

void msg_queue_init(void);

void get_msg_queue(void);

uint8_t have_cent_event(void);

uint32_t *get_cent_event(void);

void msg_queue_clear(void);

uint8_t cent_event_current(void);

#ifdef __cplusplus
}
#endif

#endif // CENTAURI_QUEUE_H
