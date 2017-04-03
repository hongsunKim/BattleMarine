/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

struct SRespawnPosition : SPosition {
	SRespawnPosition() { memset(this, 0, sizeof(SRespawnPosition)); }
};

struct SRespawnColor : SColor {
	SRespawnColor() { memset(this, 0, sizeof(SRespawnColor)); }

	bool	used;
};
