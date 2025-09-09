# Instala as ferramentas WiFi (se não estiverem presentes)
emerge --ask net-wireless/iw net-wireless/wpa_supplicant

# Verifica as interfaces wireless
iw dev

# Conecta à rede WiFi
wpa_supplicant -B -i wlan0 -c <(wpa_passphrase "SSID" "senha")
dhcpcd wlan0