#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* SSID = "Wi-Fi Grátis";  

DNSServer dnsServer;
WebServer webServer(80);

const byte DNS_PORT = 53;
const char* YOUTUBE_URL = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

const char* redirectPage = R"(
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="refresh" content="0; url=https://www.youtube.com/watch?v=dQw4w9WgXcQ">
  <script>window.location.href = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";</script>
</head>
<body>Redirecionando...</body>
</html>
)";

void handleRedirect() {
  webServer.sendHeader("Location", YOUTUBE_URL, true);
  webServer.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP()); 

  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  webServer.onNotFound(handleRedirect);
  webServer.on("/", handleRedirect);

  webServer.on("/generate_204", handleRedirect);       // Android
  webServer.on("/hotspot-detect.html", handleRedirect); // iOS/macOS
  webServer.on("/connecttest.txt", handleRedirect);     // Windows
  webServer.on("/ncsi.txt", handleRedirect);            // Windows
  webServer.on("/redirect", handleRedirect);

  webServer.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
