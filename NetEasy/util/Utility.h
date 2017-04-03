/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../Retypedefined.h"

struct SPosition {
	SPosition() { memset(this, 0, sizeof(SPosition)); }

	bool operator==(SPosition o) {
		if (x == o.x && y == o.y)
			return true;
		else
			return false;
	}

	INT32	x;
	INT32	y;
};

struct SColor {
	SColor()	{ memset(this, 0, sizeof(SColor)); }

	UINT32	A:8;
	UINT32	R:8;
	UINT32	G:8;
	UINT32	B:8;
};