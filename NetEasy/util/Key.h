/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

//struct SRoomKey {
//	SRoomKey() : channel(0), index(0) {}
//	SRoomKey(UINT16 o, UINT16 p) : channel(o - 1), index(p) {}
//	SRoomKey(const UINT16 o) : channel((o >> 10) - 1), index(UINT16(o) & 0x03FF) {}
//
//	UINT16 GetKey()	{ return ((channel + 1) << 10) | index; }
//
//	//	UINT16 operator()() {
//	//		return ((channel+1)<<10) | index;
//	//	}
//
//	void operator()(UINT16 o, UINT16 p) {
//		channel = o - 1;
//		index = p;
//	}
//
//	void operator()(UINT16 o) {
//		channel = (o >> 10) - 1;
//		index = (UINT16(o) & 0x03FF);
//	}
//
//	UINT16 channel : 6;
//	UINT16 index : 10;
//};
//
//inline UINT16 GenerateRoomKey(UINT16 o, UINT16 p) { return (((o + 1) << 10) | p); }
