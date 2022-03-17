#pragma once

// check (required) parameters passed from the ini
// create your own private_config.ini with the data. See private_config.template.ini
#ifndef WIFI_SSID
#error Need to pass WIFI_SSID
#endif
// Password of the WiFi network
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"
#endif