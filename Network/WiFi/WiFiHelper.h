//==============
// WiFiHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Network {
	namespace WiFi {


//========
// Common
//========

VOID WiFiClose();
VOID WiFiInit();
VOID WiFiAccessPointClose();
VOID WiFiAccessPointConfig(Handle<String> Network, Handle<String> Password, UINT Ip, UINT Gateway, UINT Subnet);
VOID WiFiStationClose();
VOID WiFiStationConfig(Handle<String> Network, Handle<String> Password);
VOID WiFiStationSetHostName(Handle<String> HostName);

}}