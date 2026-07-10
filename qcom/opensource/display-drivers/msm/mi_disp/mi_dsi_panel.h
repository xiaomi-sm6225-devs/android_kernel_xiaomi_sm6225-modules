/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2026, The LineageOS Project
 */

#ifndef _MI_DSI_PANEL_H_
#define _MI_DSI_PANEL_H_

#include <linux/types.h>

struct dsi_panel;
struct drm_panel_esd_config;

struct mi_drm_panel_esd_config {
	int esd_err_irq;
	int esd_err_irq_flags;
	int esd_err_irq_gpio;
};

int mi_dsi_panel_parse_esd_gpio_config(struct dsi_panel *panel,
				       struct drm_panel_esd_config *esd_config);

#endif /* _MI_DSI_PANEL_H_ */
