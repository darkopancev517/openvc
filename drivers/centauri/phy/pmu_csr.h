#ifndef PMU_CSR_H
#define PMU_CSR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))
#endif

/** Block pmu_csr

*/
#define PMU_CSR_BASE 0x4002C000

/*****************************************************************************/

/** Reg PMU_CCMD_CR
Centauri command (to PMU) Control Register
*/
#define PMU_CSR__PMU_CCMD_CR CSR_ACCESS(PMU_CSR_BASE + 0x00000000)

/** Field csr_ccmd_sdn
PMU Target state, MCU need to clear the signal. HW use raising edge as the trigger.
*/
#define PMU_CCMD_CR__CSR_CCMD_SDN_POS 0
#define PMU_CCMD_CR__CSR_CCMD_SDN_MASK 0x00000001

/** Field csr_ccmd_slp
PMU Target state
*/
#define PMU_CCMD_CR__CSR_CCMD_SLP_POS 1
#define PMU_CCMD_CR__CSR_CCMD_SLP_MASK 0x00000002

/** Field csr_ccmd_pattern
Match Pattern=0xA55A to enable state change
*/
#define PMU_CCMD_CR__CSR_CCMD_PATTERN_POS 16
#define PMU_CCMD_CR__CSR_CCMD_PATTERN_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg PMU_CR
PMU Control Register
*/
#define PMU_CSR__PMU_CR CSR_ACCESS(PMU_CSR_BASE + 0x00000004)

/** Field csr_srstpor12_en
Does POR12 reset whole SOC
*/
#define PMU_CR__CSR_SRSTPOR12_EN_POS 0
#define PMU_CR__CSR_SRSTPOR12_EN_MASK 0x00000001

/** Field csr_ldstr_en
Load/Store Enable, default 0 (nothing to load back at the first boot-up)
*/
#define PMU_CR__CSR_LDSTR_EN_POS 2
#define PMU_CR__CSR_LDSTR_EN_MASK 0x00000004

/** Field csr_fepwd_en
Enable FE33 Power Down (0x10)
*/
#define PMU_CR__CSR_FEPWD_EN_POS 3
#define PMU_CR__CSR_FEPWD_EN_MASK 0x00000008

/** Field csr_retif_hold
Hold the write/read data for the async. Retention IF
*/
#define PMU_CR__CSR_RETIF_HOLD_POS 4
#define PMU_CR__CSR_RETIF_HOLD_MASK 0x00000070

/** Field csr_retaddr_clr
Clear the retention address (SW Force to clear)
*/
#define PMU_CR__CSR_RETADDR_CLR_POS 7
#define PMU_CR__CSR_RETADDR_CLR_MASK 0x00000080

/** Field csr_retif_load_swreq
SW could request PMU to load retention CSR from modem by set this CSR
*/
#define PMU_CR__CSR_RETIF_LOAD_SWREQ_POS 8
#define PMU_CR__CSR_RETIF_LOAD_SWREQ_MASK 0x00000100

/** Field csr_retif_store_swreq
SW could request PMU to store retention CSR back to modem by set this CSR
*/
#define PMU_CR__CSR_RETIF_STORE_SWREQ_POS 9
#define PMU_CR__CSR_RETIF_STORE_SWREQ_MASK 0x00000200

/** Field csr_por12_detect
If 1, PMU will wait por12 back to 0, then start the power saving procedure.
If 0, PMU will not detect por12 but just into the power saving mode.
*/
#define PMU_CR__CSR_POR12_DETECT_POS 10
#define PMU_CR__CSR_POR12_DETECT_MASK 0x00000400

/** Field csr_spics_detect
If 1, PMU will wait spi_cs = 1 then start the power saving procedure.
If 0, PMU will not detect spi_cs but just into the power saving mode.
*/
#define PMU_CR__CSR_SPICS_DETECT_POS 11
#define PMU_CR__CSR_SPICS_DETECT_MASK 0x00000800

/** Field csr_waitsoc
4M cycle to wait soc ready for load csr back
*/
#define PMU_CR__CSR_WAITSOC_POS 12
#define PMU_CR__CSR_WAITSOC_MASK 0x00007000

/*****************************************************************************/

/** Reg PMU_CGCR
PMU Clock Gating Control Register
*/
#define PMU_CSR__PMU_CGCR CSR_ACCESS(PMU_CSR_BASE + 0x00000008)

/** Field csr_cg_xo32m_core_en
XO32M Core Domain
*/
#define PMU_CGCR__CSR_CG_XO32M_CORE_EN_POS 0
#define PMU_CGCR__CSR_CG_XO32M_CORE_EN_MASK 0x00000001

/** Field csr_cg_xo32m_base_en
XO32M RstGen Domain
*/
#define PMU_CGCR__CSR_CG_XO32M_BASE_EN_POS 1
#define PMU_CGCR__CSR_CG_XO32M_BASE_EN_MASK 0x00000002

/** Field csr_cg_xo32m_ifda_en
XO32M DA Interface Domain
*/
#define PMU_CGCR__CSR_CG_XO32M_IFDA_EN_POS 2
#define PMU_CGCR__CSR_CG_XO32M_IFDA_EN_MASK 0x00000004

/** Field csr_cg_rco4m_core_en
RCO4M Core Domain
*/
#define PMU_CGCR__CSR_CG_RCO4M_CORE_EN_POS 4
#define PMU_CGCR__CSR_CG_RCO4M_CORE_EN_MASK 0x00000010

/** Field csr_cg_rco4m_base_en
RCO4M RstGen Domain
*/
#define PMU_CGCR__CSR_CG_RCO4M_BASE_EN_POS 5
#define PMU_CGCR__CSR_CG_RCO4M_BASE_EN_MASK 0x00000020

/** Field csr_cg_rco32k_core_en
RCO32K Core Domain
*/
#define PMU_CGCR__CSR_CG_RCO32K_CORE_EN_POS 6
#define PMU_CGCR__CSR_CG_RCO32K_CORE_EN_MASK 0x00000040

/** Field csr_cg_rco32k_base_en
RCO32K RstGen Domain
*/
#define PMU_CGCR__CSR_CG_RCO32K_BASE_EN_POS 7
#define PMU_CGCR__CSR_CG_RCO32K_BASE_EN_MASK 0x00000080

/** Field csr_cg_xo32m_pmucsr_en
PMU CSR Clock Gating. If 0, always on. If 1, auto on when hsel, auto off when csr access done.
*/
#define PMU_CGCR__CSR_CG_XO32M_PMUCSR_EN_POS 8
#define PMU_CGCR__CSR_CG_XO32M_PMUCSR_EN_MASK 0x00000100

/** Field csr_cg_xo32m_fe33csr_en
FE33 CSR Clock Gating. If 0, always on. If 1, auto on when hsel, auto off when csr access done.
*/
#define PMU_CGCR__CSR_CG_XO32M_FE33CSR_EN_POS 9
#define PMU_CGCR__CSR_CG_XO32M_FE33CSR_EN_MASK 0x00000200

/*****************************************************************************/

/** Reg PMU_FEPWD_CR
FE33 Power Down Control Register
*/
#define PMU_CSR__PMU_FEPWD_CR CSR_ACCESS(PMU_CSR_BASE + 0x00000010)

/** Field csr_ldoa12if_swpwd
LDOA12IF SW Power Down Control
*/
#define PMU_FEPWD_CR__CSR_LDOA12IF_SWPWD_POS 0
#define PMU_FEPWD_CR__CSR_LDOA12IF_SWPWD_MASK 0x00000001

/** Field csr_ldoa12dig_swpwd
LDOA12DIG SW Power Down Control
*/
#define PMU_FEPWD_CR__CSR_LDOA12DIG_SWPWD_POS 1
#define PMU_FEPWD_CR__CSR_LDOA12DIG_SWPWD_MASK 0x00000002

/** Field csr_ldoasz4_swpwd
LDOASZ4 SW Power Down Control
*/
#define PMU_FEPWD_CR__CSR_LDOASZ4_SWPWD_POS 2
#define PMU_FEPWD_CR__CSR_LDOASZ4_SWPWD_MASK 0x00000004

/** Field csr_rco32k_bgclp_swpwd
RCO32K BG SW Power Down Control
*/
#define PMU_FEPWD_CR__CSR_RCO32K_BGCLP_SWPWD_POS 3
#define PMU_FEPWD_CR__CSR_RCO32K_BGCLP_SWPWD_MASK 0x00000008

/** Field csr_rco32k_swpwd
RCO32K SW Power Down Control
*/
#define PMU_FEPWD_CR__CSR_RCO32K_SWPWD_POS 4
#define PMU_FEPWD_CR__CSR_RCO32K_SWPWD_MASK 0x00000010

/** Field csr_rco4m_swpwd
RCO4M SW Power Down Control
*/
#define PMU_FEPWD_CR__CSR_RCO4M_SWPWD_POS 5
#define PMU_FEPWD_CR__CSR_RCO4M_SWPWD_MASK 0x00000020

/** Field csr_swpwd_pattern
Match Pattern=0x5AA5 to enable sw power down
*/
#define PMU_FEPWD_CR__CSR_SWPWD_PATTERN_POS 16
#define PMU_FEPWD_CR__CSR_SWPWD_PATTERN_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg PMU_PROBE_CR
PMU Probe Select Control Register
*/
#define PMU_CSR__PMU_PROBE_CR CSR_ACCESS(PMU_CSR_BASE + 0x00000018)

/** Field csr_pmu_probe_sel
PMU probe select
*/
#define PMU_PROBE_CR__CSR_PMU_PROBE_SEL_POS 0
#define PMU_PROBE_CR__CSR_PMU_PROBE_SEL_MASK 0x000000FF

/*****************************************************************************/

/** Reg PMU_4M_TIMER_SR
4M Timer Setting Register
*/
#define PMU_CSR__PMU_4M_TIMER_SR CSR_ACCESS(PMU_CSR_BASE + 0x0000001C)

/** Field csr_4mtmr_target
Timer to ensure 32M clock source is ready [12bits, PMU 4M timer, default 500us in 6M]
*/
#define PMU_4M_TIMER_SR__CSR_4MTMR_TARGET_POS 0
#define PMU_4M_TIMER_SR__CSR_4MTMR_TARGET_MASK 0x00000FFF

/*****************************************************************************/

/** Reg PMU_32K_TIMER_SR1
32K Timer Setting Register1
*/
#define PMU_CSR__PMU_32K_TIMER_SR1 CSR_ACCESS(PMU_CSR_BASE + 0x00000024)

/** Field csr_32ktmr1_target
the target value for timer 1
*/
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_TARGET_POS 0
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_TARGET_MASK 0x000FFFFF

/** Field csr_32ktmr1_mode
0: reach the target, tie, until disabled.
1: reach the target, reset and restart the counter until disabled.
2: reach the target, still count (as a freerun counter), until disabled.
*/
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_MODE_POS 24
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_MODE_MASK 0x03000000

/** Field csr_32ktmr1_wakeup
If 1, PMU will take the timeout signal as a wakeup event
*/
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_WAKEUP_POS 26
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_WAKEUP_MASK 0x04000000

/** Field csr_32ktmr1_active
The enable signal for the timer 1, also be a clear signal when deassered.
*/
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_ACTIVE_POS 27
#define PMU_32K_TIMER_SR1__CSR_32KTMR1_ACTIVE_MASK 0x08000000

/** Field csr_32k_prescaler1
0: div2, 1: div4, 2: div8, 3: div16, 4: div 32
*/
#define PMU_32K_TIMER_SR1__CSR_32K_PRESCALER1_POS 28
#define PMU_32K_TIMER_SR1__CSR_32K_PRESCALER1_MASK 0x70000000

/** Field csr_32k_prescaler1_en

*/
#define PMU_32K_TIMER_SR1__CSR_32K_PRESCALER1_EN_POS 31
#define PMU_32K_TIMER_SR1__CSR_32K_PRESCALER1_EN_MASK 0x80000000

/*****************************************************************************/

/** Reg PMU_32K_TIMER_IR
Timer Information
*/
#define PMU_CSR__PMU_32K_TIMER_IR CSR_ACCESS(PMU_CSR_BASE + 0x0000002C)

/** Field csr_32ktmr1
current 32k timer1 value
*/
#define PMU_32K_TIMER_IR__CSR_32KTMR1_POS 0
#define PMU_32K_TIMER_IR__CSR_32KTMR1_MASK 0x000FFFFF

/*****************************************************************************/

/** Reg PMU_HCMD_CR
Host Command Register
*/
#define PMU_CSR__PMU_HCMD_CR CSR_ACCESS(PMU_CSR_BASE + 0x00000030)

/** Field hcmd_tstate
Target State
*/
#define PMU_HCMD_CR__HCMD_TSTATE_POS 0
#define PMU_HCMD_CR__HCMD_TSTATE_MASK 0x0000000F

/** Field hcmd_tnstate
The target state after TX. The state machine in MCU automatically goes to the target state after the end of TX. (only valid if hcmd_state is TX)
*/
#define PMU_HCMD_CR__HCMD_TNSTATE_POS 4
#define PMU_HCMD_CR__HCMD_TNSTATE_MASK 0x000000F0

/** Field hcmd_rnstate
The target state after RX. The state machine in MCU automatically goes to the target state after the end of RX. (only valid if hcmd_state is RX)
*/
#define PMU_HCMD_CR__HCMD_RNSTATE_POS 8
#define PMU_HCMD_CR__HCMD_RNSTATE_MASK 0x00000F00

/** Field hcmd_wnstate
The target state after wakeup. The state machine in MCU automatically goes to the target state when back to idle (from power saving state) . (How MCU to decide form power saving or not? Can it be done by hcmd_state?)
*/
#define PMU_HCMD_CR__HCMD_WNSTATE_POS 12
#define PMU_HCMD_CR__HCMD_WNSTATE_MASK 0x0000F000

/** Field lpl_mode
Low Power Listen Mode. It's a sub state of the RX mode. Centauri MCU will switch its state between SLEEP and RX.
*/
#define PMU_HCMD_CR__LPL_MODE_POS 16
#define PMU_HCMD_CR__LPL_MODE_MASK 0x00010000

/*****************************************************************************/

/** Reg PMU_CST_IR
Centauri State Information Register
*/
#define PMU_CSR__PMU_CST_IR CSR_ACCESS(PMU_CSR_BASE + 0x0000003C)

/** Field hcmd_cstate
Current State. [Centauri MCU Write, Host MCU Read], let 16bits to store more information
*/
#define PMU_CST_IR__HCMD_CSTATE_POS 0
#define PMU_CST_IR__HCMD_CSTATE_MASK 0x0000000F

/** Field csr_pmu_cs
MCU could count itself or polling this CSR
*/
#define PMU_CST_IR__CSR_PMU_CS_POS 4
#define PMU_CST_IR__CSR_PMU_CS_MASK 0x000000F0

/** Field csr_modem_rdy
CSR are all load-back to modem side
*/
#define PMU_CST_IR__CSR_MODEM_RDY_POS 8
#define PMU_CST_IR__CSR_MODEM_RDY_MASK 0x00000100

/** Field csr_rco32k_wakeup
the status of rco32k_wakeup bit
*/
#define PMU_CST_IR__CSR_RCO32K_WAKEUP_POS 9
#define PMU_CST_IR__CSR_RCO32K_WAKEUP_MASK 0x00000200

/** Field csr_ccmd_sdn_en
MCU could polling this bit to ensure the unlock
*/
#define PMU_CST_IR__CSR_CCMD_SDN_EN_POS 12
#define PMU_CST_IR__CSR_CCMD_SDN_EN_MASK 0x00001000

/** Field csr_ccmd_slp_en
MCU could polling this bit to ensure the unlock
*/
#define PMU_CST_IR__CSR_CCMD_SLP_EN_POS 13
#define PMU_CST_IR__CSR_CCMD_SLP_EN_MASK 0x00002000

/*****************************************************************************/

/** Reg PMU_IER
PMU Interrupt Enable Register
*/
#define PMU_CSR__PMU_IER CSR_ACCESS(PMU_CSR_BASE + 0x00000040)

/** Field ier_host_trigger
IER for host trigger
*/
#define PMU_IER__IER_HOST_TRIGGER_POS 0
#define PMU_IER__IER_HOST_TRIGGER_MASK 0x00000001

/** Field ier_itcr1
IER for ITCR1
*/
#define PMU_IER__IER_ITCR1_POS 1
#define PMU_IER__IER_ITCR1_MASK 0x00000002

/** Field ier_itcr2
IER for ITCR2
*/
#define PMU_IER__IER_ITCR2_POS 2
#define PMU_IER__IER_ITCR2_MASK 0x00000004

/** Field ier_itcr3
IER for ITCR3
*/
#define PMU_IER__IER_ITCR3_POS 3
#define PMU_IER__IER_ITCR3_MASK 0x00000008

/** Field ier_itcr4
IER for ITCR4
*/
#define PMU_IER__IER_ITCR4_POS 4
#define PMU_IER__IER_ITCR4_MASK 0x00000010

/** Field ier_retif_swreq_done
IER for retention if, sw load/store request
*/
#define PMU_IER__IER_RETIF_SWREQ_DONE_POS 5
#define PMU_IER__IER_RETIF_SWREQ_DONE_MASK 0x00000020

/** Field ier_32ktmr1_timeout
IER for 32ktimer1 timeout
*/
#define PMU_IER__IER_32KTMR1_TIMEOUT_POS 8
#define PMU_IER__IER_32KTMR1_TIMEOUT_MASK 0x00000100

/*****************************************************************************/

/** Reg PMU_ISR
PMU Interrupt Status Register
*/
#define PMU_CSR__PMU_ISR CSR_ACCESS(PMU_CSR_BASE + 0x00000044)

/** Field isr_host_trigger
ISR for host trigger
*/
#define PMU_ISR__ISR_HOST_TRIGGER_POS 0
#define PMU_ISR__ISR_HOST_TRIGGER_MASK 0x00000001

/** Field isr_itcr1
ISR for ITCR1
*/
#define PMU_ISR__ISR_ITCR1_POS 1
#define PMU_ISR__ISR_ITCR1_MASK 0x00000002

/** Field isr_itcr2
ISR for ITCR2
*/
#define PMU_ISR__ISR_ITCR2_POS 2
#define PMU_ISR__ISR_ITCR2_MASK 0x00000004

/** Field isr_itcr3
ISR for ITCR3
*/
#define PMU_ISR__ISR_ITCR3_POS 3
#define PMU_ISR__ISR_ITCR3_MASK 0x00000008

/** Field isr_itcr4
ISR for ITCR4
*/
#define PMU_ISR__ISR_ITCR4_POS 4
#define PMU_ISR__ISR_ITCR4_MASK 0x00000010

/** Field isr_retif_swreq_done
ISR for retention if, sw load/store request
*/
#define PMU_ISR__ISR_RETIF_SWREQ_DONE_POS 5
#define PMU_ISR__ISR_RETIF_SWREQ_DONE_MASK 0x00000020

/** Field isr_32ktmr1_timeout
ISR for 32ktimer1 timeout
*/
#define PMU_ISR__ISR_32KTMR1_TIMEOUT_POS 8
#define PMU_ISR__ISR_32KTMR1_TIMEOUT_MASK 0x00000100

/*****************************************************************************/

/** Reg PMU_HOST_INTR_TR
Host Interrupt Trigger Register
*/
#define PMU_CSR__PMU_HOST_INTR_TR CSR_ACCESS(PMU_CSR_BASE + 0x00000048)

/** Field isr_hcmd_trigger
Interrupt set by Host MCU to trigger Centauri MCU
*/
#define PMU_HOST_INTR_TR__ISR_HCMD_TRIGGER_POS 0
#define PMU_HOST_INTR_TR__ISR_HCMD_TRIGGER_MASK 0x00000001

/*****************************************************************************/

/** Reg SEM1
Semaphore Register1
*/
#define PMU_CSR__SEM1 CSR_ACCESS(PMU_CSR_BASE + 0x00000080)

/** Field csr_sem1
Semaphore Register1
*/
#define SEM1__CSR_SEM1_POS 0
#define SEM1__CSR_SEM1_MASK 0x00000001

/*****************************************************************************/

/** Reg SEM2
Semaphore Register2
*/
#define PMU_CSR__SEM2 CSR_ACCESS(PMU_CSR_BASE + 0x00000084)

/** Field csr_sem2
Semaphore Register2
*/
#define SEM2__CSR_SEM2_POS 0
#define SEM2__CSR_SEM2_MASK 0x00000001

/*****************************************************************************/

/** Reg SEM3
Semaphore Register3
*/
#define PMU_CSR__SEM3 CSR_ACCESS(PMU_CSR_BASE + 0x00000088)

/** Field csr_sem3
Semaphore Register3
*/
#define SEM3__CSR_SEM3_POS 0
#define SEM3__CSR_SEM3_MASK 0x00000001

/*****************************************************************************/

/** Reg SEM4
Semaphore Register4
*/
#define PMU_CSR__SEM4 CSR_ACCESS(PMU_CSR_BASE + 0x0000008C)

/** Field csr_sem4
Semaphore Register4
*/
#define SEM4__CSR_SEM4_POS 0
#define SEM4__CSR_SEM4_MASK 0x00000001

/*****************************************************************************/

/** Reg HCMD_ITCR1
Host Command Interrupt Triggered Control Register 1
*/
#define PMU_CSR__HCMD_ITCR1 CSR_ACCESS(PMU_CSR_BASE + 0x00000090)

/** Field csr_hcmd_itcr1
Host Command Interrupt Triggered Control Register 1
*/
#define HCMD_ITCR1__CSR_HCMD_ITCR1_POS 0
#define HCMD_ITCR1__CSR_HCMD_ITCR1_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HCMD_ITCR2
Host Command Interrupt Triggered Control Register 2
*/
#define PMU_CSR__HCMD_ITCR2 CSR_ACCESS(PMU_CSR_BASE + 0x00000094)

/** Field csr_hcmd_itcr2
Host Command Interrupt Triggered Control Register 2
*/
#define HCMD_ITCR2__CSR_HCMD_ITCR2_POS 0
#define HCMD_ITCR2__CSR_HCMD_ITCR2_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HCMD_ITCR3
Host Command Interrupt Triggered Control Register 3
*/
#define PMU_CSR__HCMD_ITCR3 CSR_ACCESS(PMU_CSR_BASE + 0x00000098)

/** Field csr_hcmd_itcr3
Host Command Interrupt Triggered Control Register 3
*/
#define HCMD_ITCR3__CSR_HCMD_ITCR3_POS 0
#define HCMD_ITCR3__CSR_HCMD_ITCR3_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HCMD_ITCR4
Host Command Interrupt Triggered Control Register 4
*/
#define PMU_CSR__HCMD_ITCR4 CSR_ACCESS(PMU_CSR_BASE + 0x0000009C)

/** Field csr_hcmd_itcr4
Host Command Interrupt Triggered Control Register 4
*/
#define HCMD_ITCR4__CSR_HCMD_ITCR4_POS 0
#define HCMD_ITCR4__CSR_HCMD_ITCR4_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR1
Reserved Register 1
*/
#define PMU_CSR__RESR1 CSR_ACCESS(PMU_CSR_BASE + 0x000000A0)

/** Field csr_rsvd1

*/
#define RESR1__CSR_RSVD1_POS 0
#define RESR1__CSR_RSVD1_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR2
Reserved Register 2
*/
#define PMU_CSR__RESR2 CSR_ACCESS(PMU_CSR_BASE + 0x000000A4)

/** Field csr_rsvd2

*/
#define RESR2__CSR_RSVD2_POS 0
#define RESR2__CSR_RSVD2_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR3
Reserved Register 3
*/
#define PMU_CSR__RESR3 CSR_ACCESS(PMU_CSR_BASE + 0x000000A8)

/** Field csr_rsvd3

*/
#define RESR3__CSR_RSVD3_POS 0
#define RESR3__CSR_RSVD3_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR4
Reserved Register 4
*/
#define PMU_CSR__RESR4 CSR_ACCESS(PMU_CSR_BASE + 0x000000AC)

/** Field csr_rsvd4

*/
#define RESR4__CSR_RSVD4_POS 0
#define RESR4__CSR_RSVD4_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR5
Reserved Register 5
*/
#define PMU_CSR__RESR5 CSR_ACCESS(PMU_CSR_BASE + 0x000000B0)

/** Field csr_rsvd5

*/
#define RESR5__CSR_RSVD5_POS 0
#define RESR5__CSR_RSVD5_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR6
Reserved Register 6
*/
#define PMU_CSR__RESR6 CSR_ACCESS(PMU_CSR_BASE + 0x000000B4)

/** Field csr_rsvd6

*/
#define RESR6__CSR_RSVD6_POS 0
#define RESR6__CSR_RSVD6_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR7
Reserved Register 7
*/
#define PMU_CSR__RESR7 CSR_ACCESS(PMU_CSR_BASE + 0x000000B8)

/** Field csr_rsvd7

*/
#define RESR7__CSR_RSVD7_POS 0
#define RESR7__CSR_RSVD7_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR8
Reserved Register 8
*/
#define PMU_CSR__RESR8 CSR_ACCESS(PMU_CSR_BASE + 0x000000BC)

/** Field csr_rsvd8

*/
#define RESR8__CSR_RSVD8_POS 0
#define RESR8__CSR_RSVD8_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR9
Reserved Register 9
*/
#define PMU_CSR__RESR9 CSR_ACCESS(PMU_CSR_BASE + 0x000000C0)

/** Field csr_rsvd9

*/
#define RESR9__CSR_RSVD9_POS 0
#define RESR9__CSR_RSVD9_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR10
Reserved Register 10
*/
#define PMU_CSR__RESR10 CSR_ACCESS(PMU_CSR_BASE + 0x000000C4)

/** Field csr_rsvd10

*/
#define RESR10__CSR_RSVD10_POS 0
#define RESR10__CSR_RSVD10_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR11
Reserved Register 11
*/
#define PMU_CSR__RESR11 CSR_ACCESS(PMU_CSR_BASE + 0x000000C8)

/** Field csr_rsvd11

*/
#define RESR11__CSR_RSVD11_POS 0
#define RESR11__CSR_RSVD11_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR12
Reserved Register 12
*/
#define PMU_CSR__RESR12 CSR_ACCESS(PMU_CSR_BASE + 0x000000CC)

/** Field csr_rsvd12

*/
#define RESR12__CSR_RSVD12_POS 0
#define RESR12__CSR_RSVD12_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR13
Reserved Register 13
*/
#define PMU_CSR__RESR13 CSR_ACCESS(PMU_CSR_BASE + 0x000000D0)

/** Field csr_rsvd13

*/
#define RESR13__CSR_RSVD13_POS 0
#define RESR13__CSR_RSVD13_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR14
Reserved Register 14
*/
#define PMU_CSR__RESR14 CSR_ACCESS(PMU_CSR_BASE + 0x000000D4)

/** Field csr_rsvd14

*/
#define RESR14__CSR_RSVD14_POS 0
#define RESR14__CSR_RSVD14_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR15
Reserved Register 15
*/
#define PMU_CSR__RESR15 CSR_ACCESS(PMU_CSR_BASE + 0x000000D8)

/** Field csr_rsvd15

*/
#define RESR15__CSR_RSVD15_POS 0
#define RESR15__CSR_RSVD15_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR16
Reserved Register 16
*/
#define PMU_CSR__RESR16 CSR_ACCESS(PMU_CSR_BASE + 0x000000DC)

/** Field csr_rsvd16

*/
#define RESR16__CSR_RSVD16_POS 0
#define RESR16__CSR_RSVD16_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR17
Reserved Register 17
*/
#define PMU_CSR__RESR17 CSR_ACCESS(PMU_CSR_BASE + 0x000000E0)

/** Field csr_rsvd17

*/
#define RESR17__CSR_RSVD17_POS 0
#define RESR17__CSR_RSVD17_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR18
Reserved Register 18
*/
#define PMU_CSR__RESR18 CSR_ACCESS(PMU_CSR_BASE + 0x000000E4)

/** Field csr_rsvd18

*/
#define RESR18__CSR_RSVD18_POS 0
#define RESR18__CSR_RSVD18_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR19
Reserved Register 19
*/
#define PMU_CSR__RESR19 CSR_ACCESS(PMU_CSR_BASE + 0x000000E8)

/** Field csr_rsvd19

*/
#define RESR19__CSR_RSVD19_POS 0
#define RESR19__CSR_RSVD19_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR20
Reserved Register 20
*/
#define PMU_CSR__RESR20 CSR_ACCESS(PMU_CSR_BASE + 0x000000EC)

/** Field csr_rsvd20

*/
#define RESR20__CSR_RSVD20_POS 0
#define RESR20__CSR_RSVD20_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR21
Reserved Register 21
*/
#define PMU_CSR__RESR21 CSR_ACCESS(PMU_CSR_BASE + 0x000000F0)

/** Field csr_rsvd21

*/
#define RESR21__CSR_RSVD21_POS 0
#define RESR21__CSR_RSVD21_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR22
Reserved Register 22
*/
#define PMU_CSR__RESR22 CSR_ACCESS(PMU_CSR_BASE + 0x000000F4)

/** Field csr_rsvd22

*/
#define RESR22__CSR_RSVD22_POS 0
#define RESR22__CSR_RSVD22_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR23
Reserved Register 23
Note : Use for save iqc_coeffcient_AB

*/
#define PMU_CSR__RESR23 CSR_ACCESS(PMU_CSR_BASE + 0x000000F8)

/** Field csr_rsvd23

*/
#define RESR23__CSR_RSVD23_POS 0
#define RESR23__CSR_RSVD23_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RESR24
Reserved Register 24
 Note : Use for save iqc_coeffcient_C
*/
#define PMU_CSR__RESR24 CSR_ACCESS(PMU_CSR_BASE + 0x000000FC)

/** Field csr_rsvd24

*/
#define RESR24__CSR_RSVD24_POS 0
#define RESR24__CSR_RSVD24_MASK 0xFFFFFFFF

#ifdef __cplusplus
}
#endif

#endif /* PMU_CSR_H */
