/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

template <typename T>
class CSingleton {
public:
	CSingleton() {}
	virtual ~CSingleton() {}

	static T* GetInstancePtr() {
		if(false == isptr(ms_Instance)) {
			ms_Instance = new T();
		}
		return (ms_Instance);
	}

	static T& GetInstance() {
		if(false == isptr(ms_Instance)) {
			ms_Instance = new T();
		}
		return (*ms_Instance);
	}

	static void ReleaseInstance() {
		if(isptr(ms_Instance)) {
			delete ms_Instance;
			ms_Instance = NULL;
		}
	}

private:
	static T*		ms_Instance;
};

template <typename T>
T* CSingleton<T>::ms_Instance = NULL;
