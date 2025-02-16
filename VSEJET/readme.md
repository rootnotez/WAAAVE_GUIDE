# VSEJET - Video Synthesis Ecosphere for Jetson Nano 
These are the `myapps` directories from the Jetson Nano ISOs. Unclear how much duplication there is between the two ISOs.

## GW_1_5_testRelease2.iso
[GW_1_5_testRelease2.iso](/VSEJET/GW_1_5_testRelease2.iso)  
From: https://drive.google.com/file/d/1j6_BXQ-FenFTK65NYZlcWxqbMdWpzbXL/

## VSEJET/WPHD_1_0_release.iso
[WPHD_1_0_release.iso](/VSEJET/WPHD_1_0_release.iso)  
From: https://drive.google.com/file/d/1lLfQAMANsRtDjGq4dsXq8g-Jl7pj93qN/

## Jetson Nano Hardware
### Jetson Hardware Details
The jetson part numbers are confusing.  
**Jetson Modules**
They make 2GB ram and 4GB ram modules, you want 4GB.
- P3448-0000 (Original 4GB module, no eMMC boots off sd-card)
- P3448-0002 (Production module with 16GB eMMC storage)

**Jetson Carrier Boards**
- Revision A02
- Revision B01
  - Adds support for emmc Jetson Module. 
  - Revision B01 placed power pin headers at the front of the case, which interferes with several enclosures such as the Geekwork metal case.
  - A possible workaround is to extend the pin headers: [Reddit](https://www.reddit.com/r/JetsonNano/comments/f2z5jp/how_i_made_my_rev_b01_board_work_with_my_rev_a02/)

<details>
<summary>Visual identification of A02 and B01 carrier boards</summary>

![Jetson_Nan0_A02 B01_Compare](https://github.com/user-attachments/assets/76c58850-dbe5-4396-9fa1-9525eb573279)

</details>


**Jetson Developer Kits**  
These include a Module and a carrier board. Usually the dev kits contain the `P3448-0000` module with microSD boot support  
- 945-13450-0000-000 (Original 4GB Dev Kit, no eMMC, uses microSD card). 
  - A02 Carrier Board Revision
- 945-13450-0000-100 (Updated 4GB Dev Kit, no eMMC, uses microSD card). 
  - B01 Carrier Board Revision
### Flashing Jetson Nano (advanced)
Typically a user should burn an SD card, and boot that way. However, if the user has an emmc version of the Jetson Nano, or wishes to boot off of USB, there may be options, this needs investigation.

https://docs.nvidia.com/jetson/archives/r36.4.3/DeveloperGuide/SD/FlashingSupport.html#sd-flashingsupport  
https://github.com/JetsonHacksNano/bootFromUSB
