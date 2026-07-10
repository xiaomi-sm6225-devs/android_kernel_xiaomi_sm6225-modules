/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2026, The LineageOS Project
 */

#include <linux/gpio.h>
#include <linux/of_gpio.h>

#include "mi_dsi_panel.h"
#include "dsi_panel.h"

int mi_dsi_panel_parse_esd_gpio_config(struct dsi_panel *panel,
				       struct drm_panel_esd_config *esd_config)
{
	int rc = 0;

	if (!panel)
		return -EINVAL;

	esd_config->mi_cfg.esd_err_irq_gpio = of_get_named_gpio_flags(
		panel->panel_of_node, "qcom,esd-err-irq-gpio", 0,
		(enum of_gpio_flags *)&esd_config->mi_cfg.esd_err_irq_flags);

	if (!gpio_is_valid(esd_config->mi_cfg.esd_err_irq_gpio))
		return -EINVAL;

	esd_config->mi_cfg.esd_err_irq =
		gpio_to_irq(esd_config->mi_cfg.esd_err_irq_gpio);

	rc = gpio_request(esd_config->mi_cfg.esd_err_irq_gpio,
			  "esd_err_irq_gpio");
	if (rc) {
		DSI_ERR("failed to request esd irq gpio %d, rc=%d\n",
			esd_config->mi_cfg.esd_err_irq_gpio, rc);
		return rc;
	}

	gpio_direction_input(esd_config->mi_cfg.esd_err_irq_gpio);

	return rc;
}
