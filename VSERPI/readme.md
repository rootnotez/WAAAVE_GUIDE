# VSERPI - Video Synthesis Ecosphere for Raspberry Pi

## Raspberry Pi Hardware versions
[RPI Foundation Docs on Board revisions](https://github.com/raspberrypi/documentation/blob/master/documentation/asciidoc/computers/raspberry-pi/revision-codes.adoc#new-style-revision-codes-in-use)
### Raspberry Pi 3b
Unclear if VSERPI will run on Pi 3b.

### Raspberry Pi 3b+
There are rev 1.3 and 1.4 of the RPI 3b+. The rev 1.3 has been tested with the images published by Andrei. It appears that rev. 1.4 needs a fix to be bootable. The fix involves copying files from the `/boot` partition of a newer working installation of Raspberry Pi OS.

<details>
<summary>
It is probably some subset of these files, maybe only <code>bootcode.bin</code> <code>fixup.dat</code> <code>start.elf</code> but needs testing.
</summary>
  
![343353825-7466fa47-d386-4786-9f73-d69c151358fa](https://github.com/user-attachments/assets/ff4404eb-2f69-4fdd-838a-9c33a6e95277)
</details>

It is difficult to visually determine if you have a 1.3 or 1.4 board.  
Do `cat /proc/cpuinfo` and look at the table.
```
a020d3 - 3B+ 1.3
a020d4 - 3B+ 1.4
```

On a stock version of Raspberry Pi OS you can use the `pinout` command

<details>
<summary>Images from: `Pi3B-Revision-9-PCN-3.pdf`</summary>

![image](https://github.com/user-attachments/assets/9d483fe3-6df4-4995-b38c-20056773db27)
![image](https://github.com/user-attachments/assets/2369bf52-d8ea-4795-91fb-6cd57d57c4c2)
</details>

### Raspberry Pi 4
There is no official support for RPI4. 
Kyle Brown has attempted a port:
- [kyleBrownVserpi4.img.gz](https://drive.google.com/file/d/17PuhhM6yrgX3qrxHM127snkpHbwh-FiJ/view?usp=sharing)
- [VSERPI4_dev_BUSTER0.img](https://drive.google.com/file/d/1Jiap8gEHD5eiI6mFzx-O8PfK6PWQQ5tL/)

#### Composite on RPI4
There are anecdotal reports of graphics stuttering on RPI4, which is why folks have not been sucessful at porting VSERPI to RPI4. 


## Other Notes
### Analog out via headphone jack
The correct cable is 3.5mm TRRS CTIA/Apple standard.  
https://www.mycablemart.com/store/cart.php?p=602  
![trrs-diagram3](https://github.com/user-attachments/assets/f2f06900-2e7c-4939-a01b-718626e09cf7)

### Raspberry Pi GPU

https://ttt.io/glsl-raspberry-pi  
https://forums.raspberrypi.com/viewtopic.php?t=317511  
https://forums.raspberrypi.com/viewtopic.php?t=268356  
https://retropie.org.uk/docs/Overclocking/

### Linux Versions
| Debian | Codename  | Release Date  |
|---------|----------|--------------|
| 12      | Bookworm | 2023-06-10   |
| 11      | Bullseye | 2021-08-14   |
| 10      | Buster   | 2019-07-06   |
| 9       | Stretch  | 2017-06-17   |

**Raspberry PI OS Versions**  
https://www.raspberrypi.com/software/operating-systems/

### How many amps can the HDMI port supply?
Possilby 700mA  
https://raspberrypi.stackexchange.com/questions/45001/how-much-current-can-i-draw-from-each-models-hdmi-socket


## Troubleshooting
Default Password is Password. You can change this via TODO

## Compatible Accessories
Only some drivers are built in, such as for audio hats.
