//================
// WiFiHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <esp_event_loop.h>
#include <esp_wifi.h>
#include "Network/WiFi/WiFiConnection.h"
#include "WiFiHelper.h"

using namespace Network::WiFi;


//=========
// Globals
//=========

BYTE RTC_DATA_ATTR WiFiChannel=0;


//===========
// Callbacks
//===========

esp_err_t CallbackProc(VOID* parg, system_event_t* pevent)
{
auto hcon=WiFiConnection::Current;
if(!hcon)
	return ESP_OK;
system_event_info_t *pinfo=&pevent->event_info;
switch(pevent->event_id)
	{
	case SYSTEM_EVENT_AP_STACONNECTED:
		{
		hcon->Notify(WiFiEvent::ClientConnected, nullptr);
		break;
		}
	case SYSTEM_EVENT_AP_STADISCONNECTED:
		{
		hcon->Notify(WiFiEvent::ClientDisconnected, nullptr);
		break;
		}
	case SYSTEM_EVENT_STA_DISCONNECTED:
		{
		hcon->Notify(WiFiEvent::StationDisconnected, nullptr);
		break;
		}
	case SYSTEM_EVENT_STA_GOT_IP:
		{
		BYTE uch=0;
		wifi_second_chan_t usec=WIFI_SECOND_CHAN_NONE;
		if(esp_wifi_get_channel(&uch, &usec)==ESP_OK)
			{
			DebugPrint("WiFi Channel %u\r\n", uch);
			WiFiChannel=uch;
			}
		WiFiEventArgs args;
		auto pparam=&pinfo->got_ip;
		args.Gateway=pparam->ip_info.gw.addr;
		args.Ip=pparam->ip_info.ip.addr;
		args.Subnet=pparam->ip_info.netmask.addr;
		hcon->Notify(WiFiEvent::StationConnected, &args);
		break;
		}
	case SYSTEM_EVENT_STA_START:
		{
		hcon->Notify(WiFiEvent::StationStarted, nullptr);
		break;
		}
	default:
		break;
	}
return ESP_OK;
}


//===========
// Namespace
//===========

namespace Network {
	namespace WiFi {


//========
// Common
//========

VOID WiFiClose()
{
if(esp_wifi_disconnect()!=ESP_OK)
	{
	DebugPrint("esp_wifi_disconnect() failed\r\n");
	}
if(esp_wifi_stop()!=ESP_OK)
	{
	DebugPrint("esp_wifi_stop() failed\r\n");
	}
}

VOID WiFiInit()
{
tcpip_adapter_init();
if(esp_event_loop_init((system_event_cb_t)CallbackProc, nullptr)!=ESP_OK)
	{
	DebugPrint("esp_event_loop_init() failed\r\n");
	return;
	}
wifi_init_config_t cfg;
ZeroMemory(&cfg, sizeof(wifi_init_config_t));
cfg.event_handler=&esp_event_send;
cfg.rx_ampdu_buf_num=WIFI_AMPDU_RX_AMPDU_BUF_NUM;
cfg.rx_ampdu_buf_len=WIFI_AMPDU_RX_AMPDU_BUF_LEN;
cfg.rx_max_single_pkt_len=WIFI_RX_MAX_SINGLE_PKT_LEN;
cfg.rx_buf_len=WIFI_HW_RX_BUFFER_LEN;
cfg.rx_buf_num=CONFIG_ESP8266_WIFI_RX_BUFFER_NUM;
cfg.rx_pkt_num=CONFIG_ESP8266_WIFI_RX_PKT_NUM;
cfg.left_continuous_rx_buf_num=CONFIG_ESP8266_WIFI_LEFT_CONTINUOUS_RX_BUFFER_NUM;
cfg.tx_buf_num=CONFIG_ESP8266_WIFI_TX_PKT_NUM;
cfg.nvs_enable=WIFI_NVS_ENABLED;
cfg.magic=WIFI_INIT_CONFIG_MAGIC;
if(esp_wifi_init(&cfg)!=ESP_OK)
	{
	DebugPrint("esp_wifi_init() failed\r\n");
	return;
	}
}

VOID WiFiAccessPointClose()
{
tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_AP);
}

VOID WiFiAccessPointConfig(Handle<String> hnetwork, Handle<String> hpassword, UINT uip, UINT ugateway, UINT usubnet)
{
wifi_config_t conf;
ZeroMemory(&conf, sizeof(wifi_config_t));
conf.ap.authmode=hpassword? WIFI_AUTH_WPA2_PSK: WIFI_AUTH_OPEN;
conf.ap.beacon_interval=100;
conf.ap.channel=1;
conf.ap.max_connection=4;
conf.ap.ssid_len=StringCopy((LPSTR)conf.ap.ssid, 32, hnetwork? hnetwork->Begin(): nullptr);
StringCopy((LPSTR)conf.ap.password, 64, hpassword? hpassword->Begin(): nullptr);
if(esp_wifi_set_config(ESP_IF_WIFI_AP, &conf)!=ESP_OK)
	{
	DebugPrint("esp_wifi_set_config(AP) failed\r\n");
	return;
	}
tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
tcpip_adapter_ip_info_t info;
info.ip.addr=uip;
info.gw.addr=ugateway;
info.netmask.addr=usubnet;
if(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &info)!=ESP_OK)
	{
	DebugPrint("tcpip_adapter_set_ip_info(AP) failed\r\n");
	return;
	}
if(tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP)!=ESP_OK)
	{
	DebugPrint("tcpip_adapter_dhcps_start(AP) failed\r\n");
	return;
	}
}

VOID WiFiStationClose()
{
tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);
}

VOID WiFiStationConfig(Handle<String> hnetwork, Handle<String> hpassword)
{
wifi_config_t conf;
ZeroMemory(&conf, sizeof(wifi_config_t));
conf.sta.channel=WiFiChannel;
StringCopy((LPSTR)conf.sta.ssid, 32, hnetwork->Begin());
StringCopy((LPSTR)conf.sta.password, 64, hpassword->Begin());
if(esp_wifi_set_config(ESP_IF_WIFI_STA, &conf)!=ESP_OK)
	{
	DebugPrint("esp_wifi_set_config(STA) failed\r\n");
	return;
	}
if(tcpip_adapter_dhcpc_start(TCPIP_ADAPTER_IF_STA)!=ESP_OK)
	{
	DebugPrint("tcpip_adapter_dhcpc_start(STA) failed\r\n");
	return;
	}
}

VOID WiFiStationSetHostName(Handle<String> hhostname)
{
esp_err_t status=tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, hhostname->Begin());
if(status!=ESP_OK)
	{
	DebugPrint("tcpip_adapter_set_hostname(STA) failed (%i)\r\n", (INT)status);
	}
}

}}