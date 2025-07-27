# Raspberry Pi Graphics Features Comparison Table

| Model | Analog Video Out - RCA Jack | Analog Video Out - 3.5mm Adapter | Analog Video Out - Header Pins | H.264 Encode | H.264 Decode | H.265 Encode | H.265 Decode | CPU |
|-------|------------------------------|-----------------------------------|--------------------------------|--------------|--------------|--------------|--------------|-----|
| **Pi 1 (All Models)** | Yes¹ | Yes² | No | Hardware | Hardware | Software | Software | BCM2835 |
| **Pi 2 Model B** | No | Yes | No | Hardware | Hardware | Software | Software | BCM2836 |
| **Pi 3 Model B** | No | Yes | No | Hardware | Hardware | Software | Software | BCM2837 |
| **Pi 3 Model B+** | No | Yes | No | Hardware | Hardware | Software | Software | BCM2837B0 |
| **Pi 3 Model A+** | No | Yes | No | Hardware | Hardware | Software | Software | BCM2837B0 |
| **Pi 4 Model B** | No | Yes³ | No | Hardware | Hardware | Software | Hardware | BCM2711 |
| **Pi 400** | No | Yes³ | No | Hardware | Hardware | Software | Hardware | BCM2711 |
| **Pi 5** | No | Yes³ | No | Software | Software | Software | Hardware | BCM2712 |
| **Pi Zero (Original)** | No | No | Yes | Hardware | Hardware | Software | Software | BCM2835 |
| **Pi Zero v1.3** | No | No | Yes | Hardware | Hardware | Software | Software | BCM2835 |
| **Pi Zero W** | No | No | Yes | Hardware | Hardware | Software | Software | BCM2835 |
| **Pi Zero WH** | No | No | Yes | Hardware | Hardware | Software | Software | BCM2835 |
| **Pi Zero 2 W** | No | No | Yes⁴ | Hardware | Hardware | Software | Software | RP3A0 |
| **Pi Zero 2 WH** | No | No | Yes⁴ | Hardware | Hardware | Software | Software | RP3A0 |
| **Pi 500** | No | Yes³ | No | Software | Software | Software | Hardware | BCM2712 |
| **Compute Module 1** | No | No | Yes⁵ | Hardware | Hardware | Software | Software | BCM2835 |
| **Compute Module 3** | No | No | Yes⁵ | Hardware | Hardware | Software | Software | BCM2837 |
| **Compute Module 3+** | No | No | Yes⁵ | Hardware | Hardware | Software | Software | BCM2837B0 |
| **Compute Module 4** | No | No | Yes⁵ | Hardware | Hardware | Software | Hardware | BCM2711 |
| **Compute Module 5** | No | No | Yes⁵ | Software | Software | Software | Hardware | BCM2712 |

## Notes:

**¹ Pi 1 RCA Jack:** RCA jack only available on Model A and original Model B. Model B+/A+ use 3.5mm adapter instead.

**² Pi 1 3.5mm Adapter:** 3.5mm analog video output only available on Model B+/A+. Earlier models use RCA jack.

**³ Pi 4/Pi 5/Pi 500 Analog Video:** On Pi 4, Pi 5, and Pi 500, analog video output via 3.5mm requires specific configuration in `/boot/config.txt` and may disable HDMI output.

**⁴ Pi Zero 2 W Header Pins:** Unlike original Pi Zero models, the Pi Zero 2 W has composite video pads relocated to the backside of the board as solder test points rather than accessible header holes.

**⁵ Compute Module Analog Video:** Compute Modules expose analog video through their board connectors, requiring implementation on the carrier board.

## Key Information:

### CPU/SoC Generations:
- **BCM2835:** Original VideoCore IV, single-core ARM11 (Pi 1, Zero series)
- **BCM2836:** Identical to BCM2835 but quad-core Cortex-A7 (Pi 2)
- **BCM2837:** Identical to BCM2836 but quad-core Cortex-A53 (Pi 3)
- **BCM2837B0:** Improved version of BCM2837 with better thermal management (Pi 3B+, 3A+)
- **BCM2711:** New VideoCore VI, quad-core Cortex-A72, added H.265 decode (Pi 4, 400, CM4)
- **BCM2712:** VideoCore VII, quad-core Cortex-A76, removed H.264 hardware (Pi 5, 500, CM5)
- **RP3A0:** System-in-Package containing BCM2710A1 (equivalent to BCM2837) + 512MB RAM (Zero 2 W)

## Key Information:

### Codec Performance Specifications:

**H.264 Hardware Capabilities:**
- **Encode:** Up to 1080p30 (All models with VideoCore IV: Pi 1-Pi 4, Zero series, CM1-CM4)
- **Decode:** Up to 1080p60 (All models with VideoCore IV: Pi 1-Pi 4, Zero series, CM1-CM4)

**H.265 Hardware Capabilities:**
- **Encode:** Not available on any Pi model
- **Decode:** Up to 4K60 (Pi 4, Pi 5, CM4, CM5)

**Software Codec Performance (Pi 5):**
- **H.264 Encode:** Up to 1080p60 achievable
- **H.264 Decode:** 4K capable with improved ARM cores
- **H.265 Encode:** Limited performance, not recommended for real-time
- **H.265 Decode:** Handled by hardware (4K60)

### Analog Video Output Details:
- **RCA Jack:** Composite video only, found on original Pi 1 models
- **3.5mm TRRS:** Combined audio/video output requiring special cable with correct pinout
- **Header Pins:** Exposed pads requiring soldering, composite video signal only
- **Resolution:** All analog outputs limited to standard definition (NTSC/PAL)

### Pi 5 Codec Changes:
The Raspberry Pi 5 represents a significant shift in codec strategy:
- Removed legacy H.264 hardware encoder/decoder
- Retained custom H.265 hardware decoder (4K60)
- Relies on improved ARM Cortex-A76 CPU for software H.264 processing
- Better software codec flexibility but requires more CPU resources

*Last updated: July 27, 2025*