# Raspberry Pi Graphics Features Comparison Table

| Model | Analog Video Out - RCA Jack | Analog Video Out - 3.5mm Adapter | Analog Video Out - Header Pins | H.264 Encode | H.264 Decode | H.265 Encode | H.265 Decode | OpenGL ES Max | CPU |
|-------|------------------------------|-----------------------------------|--------------------------------|--------------|--------------|--------------|--------------|----------------|-----|
| **Pi 1 (All Models)** | Yes¹ | Yes² | No | Hardware | Hardware | Software | Software | 2.0 | BCM2835 |
| **Pi 2 Model B** | No | Yes | No | Hardware | Hardware | Software | Software | 2.0 | BCM2836 |
| **Pi 3 Model B** | No | Yes | No | Hardware | Hardware | Software | Software | 2.0 | BCM2837 |
| **Pi 3 Model B+** | No | Yes | No | Hardware | Hardware | Software | Software | 2.0 | BCM2837B0 |
| **Pi 3 Model A+** | No | Yes | No | Hardware | Hardware | Software | Software | 2.0 | BCM2837B0 |
| **Pi 4 Model B** | No | Yes³ | No | Hardware | Hardware | Software | Hardware | 3.1⁶ | BCM2711 |
| **Pi 400** | No | Yes³ | No | Hardware | Hardware | Software | Hardware | 3.1⁶ | BCM2711 |
| **Pi 5** | No | Yes³ | No | Software | Software | Software | Hardware | 3.1 | BCM2712 |
| **Pi Zero (Original)** | No | No | Yes | Hardware | Hardware | Software | Software | 2.0 | BCM2835 |
| **Pi Zero v1.3** | No | No | Yes | Hardware | Hardware | Software | Software | 2.0 | BCM2835 |
| **Pi Zero W** | No | No | Yes | Hardware | Hardware | Software | Software | 2.0 | BCM2835 |
| **Pi Zero WH** | No | No | Yes | Hardware | Hardware | Software | Software | 2.0 | BCM2835 |
| **Pi Zero 2 W** | No | No | Yes⁴ | Hardware | Hardware | Software | Software | 2.0 | RP3A0 |
| **Pi Zero 2 WH** | No | No | Yes⁴ | Hardware | Hardware | Software | Software | 2.0 | RP3A0 |
| **Pi 500** | No | Yes³ | No | Software | Software | Software | Hardware | 3.1 | BCM2712 |
| **Compute Module 1** | No | No | Yes⁵ | Hardware | Hardware | Software | Software | 2.0 | BCM2835 |
| **Compute Module 3** | No | No | Yes⁵ | Hardware | Hardware | Software | Software | 2.0 | BCM2837 |
| **Compute Module 3+** | No | No | Yes⁵ | Hardware | Hardware | Software | Software | 2.0 | BCM2837B0 |
| **Compute Module 4** | No | No | Yes⁵ | Hardware | Hardware | Software | Hardware | 3.1⁶ | BCM2711 |
| **Compute Module 5** | No | No | Yes⁵ | Software | Software | Software | Hardware | 3.1 | BCM2712 |

## Notes:

**¹ Pi 1 RCA Jack:** RCA jack only available on Model A and original Model B. Model B+/A+ use 3.5mm adapter instead.

**² Pi 1 3.5mm Adapter:** 3.5mm analog video output only available on Model B+/A+. Earlier models use RCA jack.

**³ Pi 4/Pi 5/Pi 500 Analog Video:** On Pi 4, Pi 5, and Pi 500, analog video output via 3.5mm requires specific configuration in `/boot/config.txt` and may disable HDMI output.

**⁴ Pi Zero 2 W Header Pins:** Unlike original Pi Zero models, the Pi Zero 2 W has composite video pads relocated to the backside of the board as solder test points rather than accessible header holes.

**⁵ Compute Module Analog Video:** Compute Modules expose analog video through their board connectors, requiring implementation on the carrier board.

**⁶ Pi 4 / Pi 400 / CM4 OpenGL ES:** VideoCore VI hardware is capable of OpenGL ES 3.2, but Raspberry Pi’s driver/conformance notes identify OpenGL ES 3.1 as the supported conformant level in practice.
