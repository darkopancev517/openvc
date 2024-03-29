/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_SOC_H
#define __VC_SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOC_DEBUG
#include <stdio.h>
#define soc_printf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define soc_printf(fmt, ...)
#endif

#include "vcmisc.h"
#include "vcwdt.h"
#include "vcgpio.h"
#include "vcuart.h"
#include "vcspi.h"
#include "vcdma.h"
#include "vctim.h"
#include "vcpmu.h"
#include "vcmem.h"
#include "vcana.h"
#include "vci2c.h"
#include "vcpwm.h"
#include "vcrtc.h"
#include "vcsfio.h"
#include "vccrypt.h"

extern uint32_t SystemCoreClock;

#ifdef __cplusplus
}
#endif

#endif // __VC_SOC_H
