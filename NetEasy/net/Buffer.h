/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../GlobalVariable.h"
#include "../Defines.h"

class CStreamBuffer {
public:
	CStreamBuffer() : m_acBuffer(NULL), m_uiMax(0), m_uiSize(0) {}
	~CStreamBuffer()	{}

	bool	Clear();
	UINT	Move(UINT);

	UINT	GetMax()		{ return m_uiMax; }
	UINT	RestSize()		{ return (GetMax() - GetSize()); }

	UINT	GetSize()		{ return m_uiSize; }
	void	SetSize(UINT o)	{ m_uiSize = o; }
	UINT	AddSize(UINT o)	{ return (m_uiSize += o); }

	char*	GetBuffer()			{ return m_acBuffer; }
	char*	GetBuffer(UINT o)	{ return m_acBuffer + o; }
	void	SetBuffer(char* o, UINT p)	{ m_acBuffer = o; m_uiMax = p; m_uiSize = 0; }

	char&	GetLast()			{ return *(m_acBuffer + GetSize()); }

private:
	char*	m_acBuffer;
	UINT	m_uiMax;
	UINT	m_uiSize;

};