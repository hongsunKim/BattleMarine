/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../Defines.h"

class CFactory {
	typedef void*	(*CreateCallback)();

public:
	CFactory()									{ m_pvCreate = NULL; }
	virtual ~CFactory()							{ m_pvCreate = NULL; }

	virtual void	Clear()						{ m_pvCreate = NULL; }

			void*	Create();

			bool	Register(CreateCallback pvfCreate_);
			bool	Unregister(INT iTypeId_)	{ m_pvCreate = NULL; return true; }

			bool	Working()					{ return (isptr(m_pvCreate)); }

private:
	CreateCallback	m_pvCreate;
};
