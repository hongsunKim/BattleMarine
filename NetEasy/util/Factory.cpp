/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

void*
CFactory::Create() {
	return m_pvCreate();
}

bool
CFactory::Register(CreateCallback pvfCreate_) {
	m_pvCreate = pvfCreate_;
	return true;
}
