/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2026, The LineageOS Project
 */

#ifndef _MI_SDE_CONNECTOR_H_
#define _MI_SDE_CONNECTOR_H_

#include <linux/types.h>

struct sde_connector;

int mi_sde_connector_register_esd_irq(struct sde_connector *c_conn);

#endif /* _MI_SDE_CONNECTOR_H_ */
