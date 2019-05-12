void tryOTAUpdate()
{
    Wifi.
	if ((WiFi) == WL_CONNECTED))
	{
		setClock();
		WiFiClientSecure client;
		client.setCACert(rootCACertificate);
		client.setTimeout(12000);
		t_httpUpdate_return ret = httpUpdate.update(client, otaURL);
		switch (ret) {
			case HTTP_UPDATE_FAILED:
				Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
				break;

			case HTTP_UPDATE_NO_UPDATES:
				Serial.println("HTTP_UPDATE_NO_UPDATES");
				break;

			case HTTP_UPDATE_OK:
				Serial.println("HTTP_UPDATE_OK");
				break;
		}
	}
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
