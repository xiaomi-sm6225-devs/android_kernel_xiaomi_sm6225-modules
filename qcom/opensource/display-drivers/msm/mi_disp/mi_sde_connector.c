/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2026, The LineageOS Project
 */

#include <linux/interrupt.h>

#include "mi_sde_connector.h"
#include "dsi_display.h"
#include "sde_dbg.h"
#include "sde_connector.h"
#include "sde_encoder.h"
#include "msm_drv.h"

static irqreturn_t mi_esd_err_irq_handle(int irq, void *data)
{
	struct dsi_display *dsi_display;
	struct sde_connector *conn = data;
	struct drm_event event;

	if (!conn || !conn->display || conn->panel_dead)
		return IRQ_HANDLED;

	dsi_display = (struct dsi_display *)conn->display;
	if (dsi_display->panel && !dsi_display->panel->panel_initialized)
		return IRQ_HANDLED;

	SDE_EVT32(SDE_EVTLOG_ERROR);
	conn->panel_dead = true;
	sde_encoder_display_failure_notification(conn->encoder, false);

	event.type = DRM_EVENT_PANEL_DEAD;
	event.length = sizeof(bool);
	msm_mode_object_event_notify(&conn->base.base, conn->base.dev, &event,
				     (u8 *)&conn->panel_dead);

	return IRQ_HANDLED;
}

int mi_sde_connector_register_esd_irq(struct sde_connector *c_conn)
{
	int rc = 0;
	struct dsi_display *dsi_display;

	if (!c_conn)
		return -EINVAL;

	if (c_conn->connector_type != DRM_MODE_CONNECTOR_DSI)
		return 0;

	dsi_display = (struct dsi_display *)c_conn->display;

	if (!dsi_display->panel)
		return -EINVAL;

	if (dsi_display->panel->esd_config.mi_cfg.esd_err_irq_gpio > 0) {
		rc = request_threaded_irq(
			dsi_display->panel->esd_config.mi_cfg.esd_err_irq, NULL,
			mi_esd_err_irq_handle,
			dsi_display->panel->esd_config.mi_cfg.esd_err_irq_flags,
			"esd_err_irq", c_conn);
		if (rc < 0)
			SDE_ERROR("request irq %d failed (rc=%d)\n",
				  dsi_display->panel->esd_config.mi_cfg
					  .esd_err_irq,
				  rc);
		else
			SDE_INFO("esd irq request succeed\n");
	}

	return rc;
}
