# GWDSK Community Help Guide

When requesting help, please respect peoples time by giving a full explanation up front. So that folks don't have to request endless information from you. Please provide the following information along with your request

## Creating Your Help Request

When you contact support, please include:

1. **Subject Line**: Brief description of the issue
2. **GWDSK Version**: Your version number
3. **System Summary**: Windows version, GPU, RAM
4. **Problem Description**: Detailed explanation of what's happening
5. **Steps to Reproduce**: Exact steps that cause the issue
6. **Error Messages**: Copy/paste exact error text or attach screenshots
7. **System Information**: All relevant details from the checklist above

### Example Support Request Format

```
Subject: GWDSK crashes when loading MIDI controller

GWDSK Version: 2.1.4
Windows: Windows 11 Build 22621
RAM: 32GB
GPU: NVIDIA RTX 4070 8GB, Driver 531.29
MIDI Controller: Akai MPK Mini MK3

Problem: GWDSK crashes immediately when I connect my MIDI controller...
[Continue with detailed description]
```


## Essential Information Checklist

### System Information
- GWDSK version number
- Windows version and build number
- System RAM amount
- CPU information


### Graphics Information
- GPU model and manufacturer
- GPU driver version
- GPU Memory (VRAM)
- OpenGL version support

### Audio/MIDI Information
- MIDI controller details
- Audio interface information
- MIDI driver versions

### Video Capture Information
- Video output configuration
- Connected display information
- USB video capture device details

### Problem Description
- Detailed description of the issue
- Steps to reproduce the problem
- Error messages (exact text or screenshots)
- When the problem started occurring

---

## How to Find This Information in Windows

### Windows Version and Build
1. Press `Windows key + R`
2. Type `winver` and press Enter
3. Note the version number and build number from the dialog box

![image](https://github.com/user-attachments/assets/99dbda3a-f22d-4b4b-8210-b8b45fc5a735)

**Alternative method:**
1. Start Menu "About Your PC

![image](https://github.com/user-attachments/assets/4c491239-c426-4eff-a0bf-4c0741cd009c)

### System RAM
1. Start Menu "About Your PC"
 
![image](https://github.com/user-attachments/assets/2121b92f-cd20-4fcc-81fa-0eca2d33dd60)

### CPU Information
1. Start Menu "About Your PC"

![image](https://github.com/user-attachments/assets/8c6e0402-aca4-4d3b-8816-b9a49e89cd5c)


### GPU Information
1. Right-click on desktop
2. Select "Display settings"
3. Scroll down and click "Advanced display settings"
4. Click "Display adapter properties"
5. Note the adapter type and dedicated video memory

![image](https://github.com/user-attachments/assets/33f47e20-5bc4-4fac-ad53-be941f1b629e)


**For detailed GPU info:**
1. Press `Windows key + R`
2. Type `dxdiag` and press Enter
3. Click the "Display" tab
4. Note all information under "Device" section

**For driver version:**
1. Right-click on desktop
2. Select your GPU control panel (NVIDIA Control Panel, AMD Radeon Settings, or Intel Graphics Settings)
3. Look for driver version information

### OpenGL Version
1. Press `Windows key + R`
2. Type `dxdiag` and press Enter
3. Click "Display" tab
4. Look for "OpenGL" information in the notes section

**Alternative method:**
1. Download and run GPU-Z (free utility)
2. Check the "Graphics Card" tab for OpenGL version

### MIDI Controller Information
1. Press `Windows key + R`
2. Type `mmsys.cpl` and press Enter
3. Click the "MIDI" tab
4. List all MIDI devices shown

**For device details:**
1. Press `Windows key + X`
2. Select "Device Manager"
3. Expand "Sound, video and game controllers"
4. Look for your MIDI devices and note exact names

### USB Video Capture Device Information
1. Press `Windows key + X`
2. Select "Device Manager"
3. Expand "Cameras" or "Imaging devices"
4. Note the exact device names and models

**Alternative location:**
1. Look under "Sound, video and game controllers" in Device Manager
2. Check for any USB video capture devices

### Audio Interface Information
1. Press `Windows key + R`
2. Type `mmsys.cpl` and press Enter
3. Note all playback and recording devices
4. Check the "Recording" and "Playback" tabs

### Display Configuration
1. Right-click on desktop
2. Select "Display settings"
3. Note resolution, refresh rate, and multiple monitor setup
4. Check "Advanced display settings" for additional details

### GWDSK Version
1. Open GWDSK application
2. Go to Help menu → About
3. Note the version number

**If GWDSK won't start:**
1. Navigate to GWDSK installation folder
2. Right-click on the main executable
3. Select "Properties" → "Details" tab
4. Note the file version

---

## Additional Troubleshooting Information

### System Performance
- Current CPU and GPU usage when problem occurs
- Available disk space on system drive
- Any recent Windows updates installed
- Other applications running simultaneously

### Network Information (if applicable)
- Internet connection status
- Firewall/antivirus software in use
- Any network-related error messages

### Recent Changes
- New hardware installations
- Driver updates
- Software installations or updates
- Windows updates

---

