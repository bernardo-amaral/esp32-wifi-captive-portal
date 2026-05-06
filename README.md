# ESP32 Captive Portal — YouTube Redirect

A lightweight captive portal built with ESP32 that creates a fake Wi-Fi access point and automatically redirects connected users to a YouTube video (or any URL). Useful for educational demonstrations, artistic installations, events, or security research in controlled environments.

---

## Features

- Creates an open Wi-Fi access point with a custom SSID
- Intercepts all DNS queries (DNS spoofing) and resolves them to the ESP32's IP
- Serves an HTTP redirect page on port 80
- Handles captive portal detection endpoints for Android, iOS/macOS, and Windows
- Zero external dependencies beyond the Arduino ESP32 core

---

## Requirements

### Hardware

- ESP32 development board (any variant)
- USB cable for flashing

### Software

- [Arduino IDE](https://www.arduino.cc/en/software) 1.8+ or 2.x
- ESP32 board package by Espressif (`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`)
- Built-in libraries (no extra installation needed):
  - `WiFi.h`
  - `WebServer.h`
  - `DNSServer.h`

---

## Installation

1. Open Arduino IDE and go to **File → Preferences**
2. Add the following URL to _Additional Boards Manager URLs_:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools → Board → Boards Manager**, search for `esp32`, and install the package by Espressif
4. Clone or download this repository
5. Open `captive_portal.ino` in Arduino IDE
6. Select your board under **Tools → Board → ESP32 Arduino**
7. Select the correct port under **Tools → Port**
8. Click **Upload**

---

## Configuration

Edit the following constants at the top of `captive_portal.ino` before uploading:

```cpp
const char* SSID        = "Wi-Fi Grátis";   // Network name visible to users
const char* YOUTUBE_URL = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"; // Target URL
```

| Constant      | Description                    | Default          |
| ------------- | ------------------------------ | ---------------- |
| `SSID`        | Name of the fake Wi-Fi network | `"Wi-Fi Grátis"` |
| `YOUTUBE_URL` | URL users are redirected to    | Rick Roll video  |
| `DNS_PORT`    | UDP port for the DNS server    | `53`             |

---

## How It Works

```
User device connects to ESP32 AP
        ↓
OS sends DNS query for any domain
        ↓
ESP32 DNS server replies with its own IP (192.168.4.1)
        ↓
OS opens captive portal browser
        ↓
ESP32 web server returns HTTP 302 redirect
        ↓
Browser navigates to YouTube URL
```

### Captive Portal Detection Endpoints

Modern operating systems probe specific URLs immediately after connecting to a new network to detect captive portals. The firmware handles all of them:

| Endpoint               | Platform    |
| ---------------------- | ----------- |
| `/generate_204`        | Android     |
| `/hotspot-detect.html` | iOS / macOS |
| `/connecttest.txt`     | Windows     |
| `/ncsi.txt`            | Windows     |
| `/redirect`            | Generic     |
| `/*` (catch-all)       | All others  |

---

## Usage

1. Power on the ESP32
2. On any device, open Wi-Fi settings and connect to the network defined in `SSID`
3. The captive portal browser window opens automatically
4. The page redirects to the configured YouTube URL

> **Note:** Since the ESP32 does not provide actual internet access, the redirect works within the captive portal browser. After the portal page opens, the user's browser will navigate to YouTube — this requires the device to have independent internet access (e.g., mobile data) for the video to load.

---

## Project Structure

```
esp32-wifi-captive-portal/
├── captive_portal.ino   # Main Arduino sketch
└── README.md
```

---

## Limitations

- The ESP32 does not route internet traffic — it only serves the redirect page
- Some devices may show a warning that the network has no internet and block the portal
- iOS 14+ and Android 11+ have stricter captive portal handling; the HTTP 302 redirect works but behavior may vary by OS version
- YouTube (HTTPS) requires the device to have its own internet connection to actually load after the redirect

---

## Legal & Ethical Notice

This project is intended for:

- Educational and research purposes
- Personal experiments on your own network
- Art installations and events where participants are informed

**Do not** deploy this on public networks or use it to intercept, deceive, or collect data from users without their explicit consent. Unauthorized use may violate local telecommunications and computer fraud laws.

---

## License

MIT License — free to use, modify, and distribute with attribution.
