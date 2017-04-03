/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

bool
CStreamBuffer::Clear() {
	if (NULL != m_acBuffer) {
		memset(m_acBuffer, 0, m_uiMax);
	} else {
		std::cout << "error: m_acBuffer is null" << std::endl;
	}

	SetSize(0);
	return true;
}

UINT
CStreamBuffer::Move(UINT uiSize_) {
	if (uiSize_ < m_uiSize) {
		UINT uiLeftLength = GetSize() - uiSize_;
		if (0 < uiLeftLength) {
			if (uiSize_ >= uiLeftLength) {
				memcpy(m_acBuffer, m_acBuffer + uiSize_, uiLeftLength);
			}
			else {
				memmove(m_acBuffer, m_acBuffer + uiSize_, uiLeftLength);
			}
			SetSize(uiLeftLength);
		} else {
			SetSize(0);
		}
	}
	else {
		SetSize(0);
	}
	return m_uiSize;
}

