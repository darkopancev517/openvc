#ifndef CENTAURI_PHY_H
#define CENTAURI_PHY_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))  //txpreempt++
#endif

/** Block phy_csr

*/
#define PHY_CSR_BASE 0x40024000 //txpreempt++

/*****************************************************************************/

/** Reg PHYTX_PREEMP_COEF1
PHY TX Pre-emphasis coef 1
*/
#define PHY_CSR__PHYTX_PREEMP_COEF1 CSR_ACCESS(PHY_CSR_BASE + 0x00000064) //txpreempt++

/** Reg PHYTX_PREEMP_COEF2
PHY TX Pre-emphasis coef 2
*/
#define PHY_CSR__PHYTX_PREEMP_COEF2 CSR_ACCESS(PHY_CSR_BASE + 0x00000068)  //txpreempt++

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_PHY_H */
