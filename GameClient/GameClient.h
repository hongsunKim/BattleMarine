/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Resource.h"

void
REFRESH_USER_LIST();

void
REFRESH_ROOM_LIST();

void
REFRESH_ROOM_MEMBER_LIST();

INT
NetworkUpdate();

void
USER_CHAT_OUT(SUserChatGsToCl o, UINT Extra);

void
REFRESH_INVENTORY_LIST();