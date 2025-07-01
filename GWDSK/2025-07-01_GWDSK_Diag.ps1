# GWDSK System Information Collector
# PowerShell script to automatically gather system information for support requests
#
# IMPORTANT: EXECUTION POLICY SETUP
# Windows may block this script by default. Choose ONE of these methods:
#
# METHOD 1 - Recommended (Copy & Paste):
#   1. Open PowerShell as Administrator (Win+X, select "Windows PowerShell (Admin)")
#   2. Copy this entire script and paste it into PowerShell
#   3. Press Enter to run
#
# METHOD 2 - Save as File:
#   1. Save this as "gwdsk_sysinfo.ps1" 
#   2. Open PowerShell as Administrator
#   3. Run: Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
#   4. When prompted, type "Y" and press Enter
#   5. Navigate to the script location: cd "C:\path\to\script"
#   6. Run: .\gwdsk_sysinfo.ps1
#
# METHOD 3 - One-time Bypass:
#   1. Right-click on the .ps1 file
#   2. Select "Run with PowerShell"
#   3. If blocked, open PowerShell as Admin and run:
#      PowerShell.exe -ExecutionPolicy Bypass -File "C:\path\to\gwdsk_sysinfo.ps1"
#
# NOTE: The Bypass setting only affects the current PowerShell session and
#       does not permanently change your system security settings.

Write-Host "GWDSK System Information Collector" -ForegroundColor Green
Write-Host "=================================" -ForegroundColor Green
Write-Host ""

# Check if running with appropriate permissions
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")
if (-not $isAdmin) {
    Write-Host "WARNING: Running without Administrator privileges." -ForegroundColor Yellow
    Write-Host "Some information may not be available. For best results, run as Administrator." -ForegroundColor Yellow
    Write-Host ""
}

# Display execution policy info
$executionPolicy = Get-ExecutionPolicy
Write-Host "Current PowerShell Execution Policy: $executionPolicy" -ForegroundColor Cyan
if ($executionPolicy -eq "Restricted") {
    Write-Host "NOTE: If you had trouble running this script, see the instructions at the top of the file." -ForegroundColor Yellow
}
Write-Host ""

# Function to safely get WMI information
function Get-SafeWMI {
    param($Class, $Property)
    try {
        $result = Get-WmiObject -Class $Class | Select-Object -ExpandProperty $Property -First 1
        return $result
    }
    catch {
        return "Unable to retrieve"
    }
}

# Function to format bytes to readable format
function Format-Bytes {
    param($bytes)
    if ($bytes -gt 1GB) {
        return "{0:N2} GB" -f ($bytes / 1GB)
    }
    elseif ($bytes -gt 1MB) {
        return "{0:N2} MB" -f ($bytes / 1MB)
    }
    else {
        return "{0:N0} bytes" -f $bytes
    }
}

# Initialize output string
$output = @()
$output += "GWDSK SYSTEM INFORMATION REPORT"
$output += "Generated: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')"
$output += "=" * 50
$output += ""

# Windows Version Information
Write-Host "Gathering Windows version information..." -ForegroundColor Yellow
try {
    $osInfo = Get-ComputerInfo
    $output += "WINDOWS INFORMATION:"
    $output += "Windows Version: $($osInfo.WindowsProductName)"
    $output += "Build Number: $($osInfo.WindowsBuildLabEx)"
    $output += "Version: $($osInfo.WindowsVersion)"
    $output += "Architecture: $($osInfo.OSArchitecture)"
    $output += "Install Date: $($osInfo.WindowsInstallDateFromRegistry)"
}
catch {
    $winver = Get-SafeWMI "Win32_OperatingSystem" "Caption"
    $build = Get-SafeWMI "Win32_OperatingSystem" "BuildNumber"
    $output += "WINDOWS INFORMATION:"
    $output += "Windows Version: $winver"
    $output += "Build Number: $build"
}
$output += ""

# System Hardware Information
Write-Host "Gathering system hardware information..." -ForegroundColor Yellow
try {
    $computerSystem = Get-WmiObject -Class Win32_ComputerSystem
    $processor = Get-WmiObject -Class Win32_Processor | Select-Object -First 1
    $memory = Get-WmiObject -Class Win32_PhysicalMemory | Measure-Object -Property Capacity -Sum
    
    $output += "SYSTEM HARDWARE:"
    $output += "CPU: $($processor.Name)"
    $output += "CPU Cores: $($processor.NumberOfCores)"
    $output += "Total RAM: $(Format-Bytes $memory.Sum)"
}
catch {
    $output += "SYSTEM HARDWARE: Unable to retrieve detailed information"
}
$output += ""

# Graphics Information
Write-Host "Gathering graphics information..." -ForegroundColor Yellow
try {
    $gpus = Get-WmiObject -Class Win32_VideoController | Where-Object { $_.Name -notlike "*Basic*" }
    $output += "GRAPHICS INFORMATION:"
    
    foreach ($gpu in $gpus) {
        $output += "GPU: $($gpu.Name)"
        $output += "Driver Version: $($gpu.DriverVersion)"
        $output += "Driver Date: $($gpu.DriverDate)"
        if ($gpu.AdapterRAM -gt 0) {
            $output += "Video Memory: $(Format-Bytes $gpu.AdapterRAM)"
        }
        $output += "Status: $($gpu.Status)"
        $output += "---"
    }
}
catch {
    $output += "GRAPHICS INFORMATION: Unable to retrieve"
}
$output += ""

# Display Information
Write-Host "Gathering display information..." -ForegroundColor Yellow
try {
    $monitors = Get-WmiObject -Class Win32_DesktopMonitor
    $output += "DISPLAY INFORMATION:"
    
    foreach ($monitor in $monitors) {
        if ($monitor.Name -and $monitor.Name -ne "") {
            $output += "Monitor: $($monitor.Name)"
        }
        if ($monitor.ScreenWidth -and $monitor.ScreenHeight) {
            $output += "Resolution: $($monitor.ScreenWidth) x $($monitor.ScreenHeight)"
        }
    }
    
    # Get current display settings
    Add-Type -AssemblyName System.Windows.Forms
    $screens = [System.Windows.Forms.Screen]::AllScreens
    $output += "Active Displays: $($screens.Count)"
    foreach ($screen in $screens) {
        $output += "Display: $($screen.Bounds.Width) x $($screen.Bounds.Height) @ $($screen.BitsPerPixel)-bit"
    }
}
catch {
    $output += "DISPLAY INFORMATION: Unable to retrieve"
}
$output += ""

# Audio Devices
Write-Host "Gathering audio device information..." -ForegroundColor Yellow
try {
    $audioDevices = Get-WmiObject -Class Win32_SoundDevice
    $output += "AUDIO DEVICES:"
    
    foreach ($device in $audioDevices) {
        $output += "Device: $($device.Name)"
        $output += "Manufacturer: $($device.Manufacturer)"
        $output += "Status: $($device.Status)"
        $output += "---"
    }
}
catch {
    $output += "AUDIO DEVICES: Unable to retrieve"
}
$output += ""

# USB Devices (for MIDI controllers and capture devices)
Write-Host "Gathering USB device information..." -ForegroundColor Yellow
try {
    $usbDevices = Get-WmiObject -Class Win32_USBControllerDevice | 
                  Select-Object -ExpandProperty Dependent | 
                  Where-Object { $_.Description -match "MIDI|Audio|Video|Capture|Controller" }
    
    $output += "USB AUDIO/VIDEO/MIDI DEVICES:"
    
    foreach ($device in $usbDevices) {
        $output += "Device: $($device.Description)"
        $output += "Manufacturer: $($device.Manufacturer)"
        $output += "Device ID: $($device.DeviceID)"
        $output += "Status: $($device.Status)"
        $output += "---"
    }
    
    # Also check for generic USB devices that might be MIDI controllers
    $allUSB = Get-WmiObject -Class Win32_USBControllerDevice | Select-Object -ExpandProperty Dependent
    $midiLikeDevices = $allUSB | Where-Object { 
        $_.Description -match "HID|Human Interface|Controller" -and 
        $_.Manufacturer -match "Akai|Novation|Korg|Roland|Yamaha|M-Audio|Arturia|Native Instruments"
    }
    
    if ($midiLikeDevices) {
        $output += "POTENTIAL MIDI CONTROLLERS:"
        foreach ($device in $midiLikeDevices) {
            $output += "Device: $($device.Description)"
            $output += "Manufacturer: $($device.Manufacturer)"
            $output += "---"
        }
    }
}
catch {
    $output += "USB DEVICES: Unable to retrieve"
}
$output += ""



# Installed Software (try to find GWDSK)
Write-Host "Looking for GWDSK installation..." -ForegroundColor Yellow
try {
    $software = Get-WmiObject -Class Win32_Product | Where-Object { $_.Name -like "*GWDSK*" }
    if ($software) {
        $output += "GWDSK INSTALLATION:"
        foreach ($app in $software) {
            $output += "Name: $($app.Name)"
            $output += "Version: $($app.Version)"
            $output += "Install Date: $($app.InstallDate)"
            $output += "Install Location: $($app.InstallLocation)"
        }
    } else {
        $output += "GWDSK INSTALLATION: Not found in installed programs list"
        $output += "Note: Please manually check GWDSK version from the application"
    }
}
catch {
    $output += "GWDSK INSTALLATION: Unable to query installed programs"
}
$output += ""





# Recent Windows Updates
Write-Host "Checking recent Windows updates..." -ForegroundColor Yellow
try {
    $updates = Get-HotFix | Sort-Object InstalledOn -Descending | Select-Object -First 5
    $output += "RECENT WINDOWS UPDATES (Last 5):"
    foreach ($update in $updates) {
        $output += "KB: $($update.HotFixID) - Installed: $($update.InstalledOn)"
    }
}
catch {
    $output += "RECENT WINDOWS UPDATES: Unable to retrieve"
}
$output += ""
$output += "=" * 50
$output += "END OF REPORT"

# Display results
Write-Host "`nSystem information collected successfully!" -ForegroundColor Green
Write-Host "Displaying results...`n" -ForegroundColor Green

# Output to console
$output | ForEach-Object { Write-Host $_ }

# Save to file
$filename = "GWDSK_SystemInfo_$(Get-Date -Format 'yyyyMMdd_HHmmss').txt"
try {
    $output | Out-File -FilePath $filename -Encoding UTF8
    Write-Host "`n" -ForegroundColor Green
    Write-Host "Report saved to: $filename" -ForegroundColor Green
    Write-Host "Location: $(Resolve-Path $filename)" -ForegroundColor Green
}
catch {
    Write-Host "`nUnable to save file to current directory." -ForegroundColor Red
    Write-Host "You can copy the information above and paste it into your support request." -ForegroundColor Yellow
}

Write-Host "`nINSTRUCTIONS FOR SUPPORT REQUEST:" -ForegroundColor Cyan
Write-Host "1. Copy all the information displayed above" -ForegroundColor White
Write-Host "2. Paste it into your GWDSK support request" -ForegroundColor White
Write-Host "3. Include a detailed description of your specific problem" -ForegroundColor White
Write-Host "4. Add any error messages or screenshots if applicable" -ForegroundColor White
Write-Host ""
Write-Host "Press any key to exit..." -ForegroundColor Yellow

# Wait for user input
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")