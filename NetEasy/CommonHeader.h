/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>
#include <cctype>
#include <ctime>
#include <memory>
#include <typeinfo>
#include <csignal>
#include <iostream>
#include <fstream>

#include <map>
#include <list>

#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <errno.h>			// EWOULDBLOCK / EFAULT
#include <fcntl.h>			// ioctl

#include <winsock2.h>
#include <objidl.h>
#include <gdiplus.h>

#include "ReTypedefined.h"
#include "Defines.h"
#include "Enums.h"
#include "GlobalVariable.h"

#include "db/DbData.h"
#include "db/DbDataList.h"

#include "util/Singleton.h"
#include "util/Factory.h"
#include "util/LogFile.h"
#include "util/Key.h"
#include "util/Locker.h"
#include "util/Utility.h"

#include "net/Protocol.h"
#include "net/Buffer.h"
#include "net/Command.h"
#include "net/Packet.h"
#include "net/Socket.h"
#include "net/Connector.h"
#include "net/Listener.h"
#include "net/Sensor.h"
#include "net/ConnectorFactory.h"

#include "net/data/ID.h"
#include "net/data/INFO.h"
#include "net/data/ITEM.h"
#include "net/data/ROOM.h"
#include "net/data/USER.h"
#include "net/data/OTHER.h"

#include "Item/Item.h"
#include "Item/ItemData.h"

#include "world/Player.h"
#include "world/PlayerMgr.h"
#include "world/PlayerFactory.h"
#include "world/Room.h"
#include "world/RoomFactory.h"
#include "world/RoomHandler.h"
