#include "FirmwareUpdate.h"

String otaErrorCode;

const char* otaURL = "https://ota.tbspace.de/scrolldisplay/update.php?key=KRVZIqfH0l2Q8OT3XPco";

const char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"FonhmIJBf3iHWhM3RHxu0BIpBx/u\n" \
"-----END CERTIFICATE-----";

uint8_t tryOTAUpdate()
{
	if (WiFi.status() == wl_status_t::WL_CONNECTED)
	{
		setClock();
		WiFiClientSecure client;
		client.setCACert(rootCACertificate);
		client.setTimeout(12000);
		t_httpUpdate_return ret = httpUpdate.update(client, otaURL);
		switch (ret) {
			case HTTP_UPDATE_FAILED:
                otaErrorCode = httpUpdate.getLastErrorString();
                return OTAResult::SERVER_ERROR;
				//Serial.printf("Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
				break;
			case HTTP_UPDATE_NO_UPDATES:
				return OTAResult::NO_UPDATE;
				break;
			case HTTP_UPDATE_OK:
				return OTAResult::UPDATING;
				break;
		}
	}
	return OTAResult::NO_WIFI_CONNECTION;
}

// Set time via NTP, as required for x.509 validation
void setClock() {
	configTime(0, 0, "pool.ntp.org", "time.nist.gov");  // UTC

	Serial.print(F("Waiting for NTP time sync: "));
	time_t now = time(nullptr);
	while (now < 8 * 3600 * 2) {
		yield();
		delay(500);
		Serial.print(F("."));
		now = time(nullptr);
	}

	Serial.println(F(""));
	struct tm timeinfo;
	gmtime_r(&now, &timeinfo);
	Serial.print(F("Current time: "));
	Serial.print(asctime(&timeinfo));
}
