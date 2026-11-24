# WAAAVE_GUIDE
A community guide to the video synthesizers made by [Andrei Jay](https://andreijaycreativecoding.com/about-me). These instruments generate and process video in real time. They delay, mix, key, and warp it, and feed it back into itself. People use them for video art and live performance, with cameras, video mixers, other video gear, or no video input at all.

There are three families, named for what they run on. VSE stands for Video Synthesis Ecosphere.

| Family | Runs on | What to expect |
|---|---|---|
| [VSEDSK](#vsedsk-desktop) | Windows or macOS computer | Software to download, free and paid. Most new development happens here |
| [VSERPI](#vserpi-raspberry-pi) | Raspberry Pi 3B or 3B+ | Standalone units in standard definition. Buy one or build your own |
| [VSEJET](#vsejet-jetson-nano) | Nvidia Jetson Nano 4GB | Standalone units in HD. Build your own, or buy one in an occasional limited run |

This page lists every instrument with its official pages, manual, source code, and videos. Open **Videos** under an instrument to see its list. The repo also holds [community notes](#community-notes-in-this-repo) on hardware, MIDI control, and troubleshooting.

## Where to start
- **Try one for free:** install [Waaave Pool DSK Pro Free](#waaave-pool-dsk-pro-wpdsk-pro) or [Waaave Pool DSK](#waaave-pool-dsk-wpdsk) on your computer.
- **Choose an instrument:** use the [table below](#find-an-instrument) to compare them by what they do.
- **Set up a unit you own:** go to its family, [VSERPI](#vserpi-raspberry-pi) or [VSEJET](#vsejet-jetson-nano), then to the instrument's manual and videos.
- **Build your own:** follow the DIY links under [VSERPI](#vserpi-raspberry-pi) or [VSEJET](#vsejet-jetson-nano).
- **Learn video feedback:** watch the [general videos](#general-videos).
- **Fix a problem:** see [Getting help](#getting-help).

## Find an instrument

| What it does | VSEDSK (desktop) | VSERPI (Raspberry Pi) | VSEJET (Jetson Nano) |
|---|---|---|---|
| Video delay and feedback | [WPDSK Pro](#waaave-pool-dsk-pro-wpdsk-pro), [WPDSK](#waaave-pool-dsk-wpdsk) | [WAAAVE_POOL](#waaave_pool) | [WAAAVE_POOL_HD](#waaave_pool_hd), [LTD](#waaave_pool_hd-ltd) |
| Video delay and feedback, audio reactive | | [AUTO_WAAAVE](#auto_waaave) | |
| Two channel mixer with two delay lines | [GWDSK](#gravity-waaaves-dsk-gwdsk) | | [GRAVITY_WAAAVES](#gravity_waaaves) |
| Chaotic video oscillators | | [ARTIFICIAL_LIFE](#artificial_life) | [HD version](#gravity_waaaves) |
| Scan processing | | [SPECTRAL_MESH](#spectral_mesh) | |
| Scan processing, audio reactive | | [AUTO_MESH](#auto_mesh) | |
| Slitscan | | [TEMPORAL_VORTEX](#temporal_vortex) | [HD version](#gravity_waaaves) |
| Colorizing and solarizing | | [CHROMATIC_ABERRATION](#chromatic_aberration) | [HD version](#gravity_waaaves) |
| Audio and video together, for vector displays and lasers | | [PHOSPHORM](#phosphorm) | |
| Convolution feedback | | [CONVOLUTIONAL_CHAOS](#convolutional_chaos) | |
| Geometric transformations | | [GENERIC_GEOMETRY_UTILITY](#generic_geometry_utility) | |
| Text for keying | | [HELLO_WORD](#hello_word) | |
| Superformula shapes | | [SUPER_HAECKEL_ADVENTURES_64](#super_haeckel_adventures_64) | |
| Older open source suite | [VIDEO_WAAAVES](#video_waaaves-legacy) | | |

## Getting help
Check the [official FAQ](https://videosynthesisecosphere.com/faq) first.

- **Desktop software:** gather the details in the [help guide](/GWDSK/GWDSK-help.md), then fill out the [official support form](https://videosynthesisecosphere.com/support).
- **VSERPI or VSEJET bought from Andrei:** fill out the form on the same [support page](https://videosynthesisecosphere.com/support).
- **DIY or secondhand units:** ask the community on [Discord](https://discord.gg/jarb32Aymg) or [scanlines.xyz](https://scanlines.xyz/c/vse/21).

## Community notes in this repo
- [VSEDSK](/VSEDSK): names, versions, and a comparison of the WPDSK Pro versions
- [GWDSK](/GWDSK): media folders and virtual cameras for GWDSK and WPDSK
- [VSERPI](/VSERPI): Raspberry Pi hardware, including a fix for newer boards that won't boot
- [VSERPI MIDI](/VSERPI/midi.md): MIDI controls and their ranges
- [VSEJET](/VSEJET): Jetson Nano hardware and SD card images
- [MIDI controller overlays](/midi-controller-overlays): printable overlays and mappings for the Korg nanoKONTROL2 and Novation Launch Control XL
- [Manuals](/manuals): PDF copies for GRAVITY_WAAAVES and WAAAVE_POOL_HD

## VSEDSK (desktop)
Video Synthesis Ecosphere Desktop: software for Windows and macOS. On older pages, VSEDSK means [VIDEO_WAAAVES](#video_waaaves-legacy). [Compare names and versions](/VSEDSK).
- [VSEDSK website](https://videosynthesisecosphere.com/vsedsk)
- [Downloads and manuals](https://videosynthesisecosphere.com/downloads)
- [YouTube playlist](https://www.youtube.com/playlist?list=PLTAAQQpCNd6TWnhnUpDyA_kKPMMIZ9qA-)

### WAAAVE POOL DSK PRO (WPDSK Pro)
Semi-modular video synthesizer based on Waaave Pool, with a new engine. Free, Basic, and Advanced versions.
- [Info and downloads](https://videosynthesisecosphere.com/waaave-pool-dsk-pro)
- [Kickstarter](https://www.kickstarter.com/projects/andreijay/waaave-pool-dsk-pro)

<details>
<summary>Videos (3)</summary>

- Playlist: [Waaave Pool DSK Pro](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SAxn-Tzdpwqlfpvo9pqA5X)

**Guides and demos**

- [Waaave Pool DSK Pro Quickstart](https://www.youtube.com/watch?v=4nioCd6qTAQ) (2026-06-03, 21 min)
- [WPDSKPRO v0.2.0 infodump](https://www.youtube.com/watch?v=u8_bHMswi8Q) (2026-11-13, 36 min)
- [Waaave Pool DSK Pro Kickstarter pitch](https://www.youtube.com/watch?v=78rBeuxjNLw) (2026-06-25, 2 min)

</details>

### GRAVITY WAAAVES DSK (GWDSK)
Two channel video mixer with two delay lines. Paid desktop port of the VSEJET GRAVITY_WAAAVES, with added media players and presets.
- [Info](https://videosynthesisecosphere.com/gravity-waaaves-dsk)
- [Buy](https://shop.videosynthesisecosphere.com/products/gravity-waaaves-dsk)
- [Community notes](/GWDSK)
- [Kickstarter](https://www.kickstarter.com/projects/gravitywaaaves/gravity-waaaves-dsk)
- [Info (old site)](https://andreijaycreativecoding.com/GRAVITY_WAAAVES-DSK)

<details>
<summary>Videos (5)</summary>

- Playlist: [gravity waaaves DSK](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SBfXLvCsc8EcmAOkhGrDhu)

**Guides and demos**

- [Gravity Waaaves DSK quickstart guide](https://www.youtube.com/watch?v=yDmR9_Arkes) (2025-09-23, 21 min)
- [gravity waaaves DSK preset speedrun 1](https://www.youtube.com/watch?v=YGZI_1vEPfw) (2025-09-23, 89 min)
- [gravity waaaves DSK - media player intro v1.19](https://www.youtube.com/watch?v=jkmV4WAS394) (2025-11-21, 11 min)
- [Gravity Waaaves DSK Kickstarter Video](https://www.youtube.com/watch?v=LMbjJgzrg88) (2024-11-21, 2 min)

**Made with it**

- [boredoms & side projects mix](https://www.youtube.com/watch?v=KtS9vhpICpE) (2025-09-24, 411 min)

</details>

### WAAAVE POOL DSK (WPDSK)
Video delay and feedback. Free desktop port of the VSERPI WAAAVE_POOL.
- [Info](https://videosynthesisecosphere.com/waaave-pool-dsk)
- [Community notes](/GWDSK)

<details>
<summary>Videos (3)</summary>

- Playlist: [waaave pool dsk](https://www.youtube.com/playlist?list=PLTAAQQpCNd6R66Wh8nyVESPFwJEzFwQrR)

**Guides and demos**

- [whats up with Waaave Pool DSK](https://www.youtube.com/watch?v=uioR2YQr7Tc) (2025-09-24, 53 min)
- [a five minute romp through Waaave Pool Dsk](https://www.youtube.com/watch?v=fyk0v4PJm0w) (2025-09-23, 5 min)
- [Waaave Pool DSK: introducing the built in media player](https://www.youtube.com/watch?v=3T2sJC5eQro) (2025-11-13, 8 min)

</details>

### VIDEO_WAAAVES (legacy)
The original open source desktop suite, also called VSEDSKP. You build it from source with openFrameworks.
- [Info](https://andreijaycreativecoding.com/video-synthesis-ecosphere-DSKP)
- [History and names](https://andreijaycreativecoding.com/video-synthesis-ecosphere-DSKP-legacy)
- [Getting started](https://andreijaycreativecoding.com/VIDEO-WAAAVES-GETTING-STARTED)
- [How to use NDI](https://andreijaycreativecoding.com/VIDEO-WAAAVES-how-to-use-NDI)
- [Source code 2.718](https://github.com/ex-zee-ex/VIDEO_WAAAVES_2.718)
- [Source code 2.5](https://github.com/ex-zee-ex/VIDEO_WAAAVES_2.5_suite)

<details>
<summary>Videos (25)</summary>

- Playlist: [video_waaaves_2.718 info, demos, and fun](https://www.youtube.com/playlist?list=PLTAAQQpCNd6TGopdftksAGA_gRmfTCWo-)
- Playlist: [VIDEO_WAAAVES tutorials](https://www.youtube.com/playlist?list=PLTAAQQpCNd6TX20It6tGmy2z7-hjtOxD2)
- Playlist: [Livestream Workshop Series](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SN-bre0gsD-WBG7tMdYsGm)

**Guides and demos**

- [WTF is Video_Waaaves 2022 edition](https://www.youtube.com/watch?v=3MeMrqqxpfM) (2022-04-28, 70 min)
- [How TO INStall VIDEO waaaves on WINDOWS from scratch](https://www.youtube.com/watch?v=UE6-zD9qqVY) (2022-09-20, 39 min)
- [video_waaaves 2.718 how to update your existing installs](https://www.youtube.com/watch?v=oDbGmeBGehU) (2022-09-12, 24 min)
- [Video_Waaaves v2.718 Trailer](https://www.youtube.com/watch?v=wskuUEQAlBg) (2022-08-31, 3 min)
- [Video Waaaves updates: wipes, color, geometry, and more!](https://www.youtube.com/watch?v=vna2bF79TB0) (2022-06-11, 47 min)
- [video waaaves v2.718... updates: new color and geometry biz](https://www.youtube.com/watch?v=OP4HX9PcmCk) (2022-05-19, 47 min)
- [Video Waaaves, Gravity Waaaves, and thoughts on Work and Jobs updates](https://www.youtube.com/watch?v=qd7IaJgaYxI) (2022-05-27, 34 min)
- [VIDEO WAAAVES 2.5 IS RELEASED](https://www.youtube.com/watch?v=ANCh_u1gFGY) (2020-10-15, 1 min)
- [video_waaaves 2.5 coming soon...](https://www.youtube.com/watch?v=CVpR-vKe67o) (2020-09-29, 13 min)
- [video_waaaves 2.5 update sneak peek 09-01-20](https://www.youtube.com/watch?v=rDs6RXaGoLo) (2020-09-02, 38 min)
- [video_waaaves class 08 11 20](https://www.youtube.com/watch?v=u05Y-WG-hco) (2020-08-12, 55 min)
- [video_waaaves workshop 07 22 20 chaotic hue modulation for complex patterns](https://www.youtube.com/watch?v=rBGB64Q2mFY) (2020-07-24, 63 min)
- [VIDEO_WAAAVES_2.0 out now](https://www.youtube.com/watch?v=x4s2LxRUYcA) (2020-04-04, 3 min)
- [VIDEO_WAAAVES_SIZZLE_REEL](https://www.youtube.com/watch?v=IX4BuKDD8v8) (2019-09-17, 2 min)

**Made with it**

- [⊰ ⎊ ⊱ ∳ ⊰ ⋄ ⊱](https://www.youtube.com/watch?v=pp5V3IQ-e1c) (2022-09-18, 63 min)
- [hi fidelity total lack of anything resembling a beat music to relax/study perturbation series to](https://www.youtube.com/watch?v=cPTImkBTTTo) (2022-04-27, 44 min)
- [XZX: psychedelic electronic music from the early 21st century](https://www.youtube.com/watch?v=MIdXXYiwd4I) (2024-04-12, 105 min)
- [a rather very long mix of various softer synthy things](https://www.youtube.com/watch?v=4nthVrEs41U) (2022-10-31, 428 min)
- [Tetsu Inoue techno mix remix](https://www.youtube.com/watch?v=QpTbALKEDYo) (2025-10-04, 191 min)
- [a cilia life rift](https://www.youtube.com/watch?v=qObI7HiWXDg) (2021-03-25, 4 min)
- [reyaler sey](https://www.youtube.com/watch?v=KnrgZj63kUs) (2021-02-25, 42 min)
- [susumu yokota acid techno mix](https://www.youtube.com/watch?v=w6UVDiFSBI8) (2021-01-05, 319 min)
- [Video Synthesis, Video Games, and the Psychedelic Experience (from vidicon 2020)](https://www.youtube.com/watch?v=aKupvyupyrM) (2020-12-01, 57 min)
- [oneiricnumbers remix](https://www.youtube.com/watch?v=8HXvEfMhN2M) (2020-04-10, 6 min)
- [andrei jay 2019 video works](https://www.youtube.com/watch?v=w96D7hKoNkU) (2019-09-19, 5 min)

</details>

## VSERPI (Video Synthesis Ecosphere Raspberry Pi)
These are run on Raspberry Pi 3B+, often these are referred to as WAAAVE_POOL. The software is distributed as ISO files that you burn to an sd-card. Some of the ISO's have multiple programs available on them.
- [Video Synthesis Ecosphere Raspberry Pi](https://andreijaycreativecoding.com/Video-Synthesis-Ecosphere-RPI)
- [Video Synthesis Ecosphere Raspberry Pi Manuals](https://andreijaycreativecoding.com/all-the-manuals)
- [VSERPI Quickstart Guide](https://andreijaycreativecoding.com/VSERPI-QUICKSTART-GUIDE)
- [DIY Hardware List and ISO Images](https://andreijaycreativecoding.com/VSERPI-hardware-and-images)
- [Midi Controller Overlays](/midi-controller-overlays)

<details>
<summary>Videos (7)</summary>

- Playlist: [Exploring the Video Synthesis Ecosphere RPI](https://www.youtube.com/playlist?list=PLTAAQQpCNd6Ss0EACdBVvWVbCs76T9q4w)
- Playlist: [VSERPI 1.5 updates](https://www.youtube.com/playlist?list=PLTAAQQpCNd6Sg_22tB_dUFU_wDHTR4S_j)
- Playlist: [Introduction to video synthesis on the Raspberry Pi 3b/3b+ (parts 2-4 are Patreon only)](https://www.youtube.com/playlist?list=PLTAAQQpCNd6Q2T5G-FvZKY7dfibO-bK3L)

**Covers several instruments**

- [VSERPI 1.5: how to update your images!](https://www.youtube.com/watch?v=lUT1biVSk0s) (2022-01-26, 15 min)
- [VSERPI 1.5 updates: Introducing Hello Word _ & how to edit auto run configurations](https://www.youtube.com/watch?v=FkXYysgiMUw) (2022-01-27, 20 min)
- [VSERPI 1.5 updates: Welcome to Convolutional Chaos & master boot options!](https://www.youtube.com/watch?v=ztdeGePZ7jg) (2022-01-27, 11 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 7: The Mystery and Myth of Master Boot](https://www.youtube.com/watch?v=FUD2UuGjjkA) (2021-08-11, 9 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 5: Chaining Units](https://www.youtube.com/watch?v=G4iAz56NoSA) (2021-07-14, 16 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 8: Getting down into some Lerping!](https://www.youtube.com/watch?v=cDYySOViPj0) (2021-09-07, 18 min)
- [Introduction to Video Synthesis on the Raspberry Pi](https://www.youtube.com/watch?v=Fh95wxSme_Q) (2026-07-14, 74 min)

</details>

### WAAAVE_POOL
- [GitHub - WAAAVE_POOL](https://github.com/ex-zee-ex/waaaave_pool)
- [WAAAVE_POOL](https://andreijaycreativecoding.com/WAAAVE_POOL)
- [WAAAVE_POOL Manual](https://andreijaycreativecoding.com/Waaave_Pool-manual)

<details>
<summary>Videos (25)</summary>

- Playlist: [WAAAVE_POOL tutorials](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SU0xdd43bElwPmF2ETEE_L)
- Playlist: [Waaave Pool demos](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SGQdVX0A0_nrnWOwHXW_om)

**Guides and demos**

- [Waaave_Pool video quickstart guide](https://www.youtube.com/watch?v=Wp1SrkcemFs) (2020-08-01, 40 min)
- [Waaave Pool tutorial episode 1: lumakey, mix, and delay](https://www.youtube.com/watch?v=HL_g-JueJu8) (2020-02-05, 6 min)
- [Waaave Pool tutorial episode 2: hue, saturation, brightness](https://www.youtube.com/watch?v=vhKnNQa0LwA) (2020-02-05, 6 min)
- [Waaave Pool tutorial episode 3: temporal filter](https://www.youtube.com/watch?v=fsNM9XUn7Go) (2020-02-05, 5 min)
- [Waaave Pool tutorial episode 4: x, y, z, theta](https://www.youtube.com/watch?v=1XAAtRPNrC4) (2020-02-05, 8 min)
- [v 1.3 update info and whats up with the chaotic hue controls](https://www.youtube.com/watch?v=kkDklGugcoQ) (2020-04-14, 33 min)
- [Waaave_Pool v1.4 updates and demo!](https://www.youtube.com/watch?v=OXqYyLzmi18) (2020-12-19, 47 min)
- [VSERPI 1.5 updates: Sharpen & Video Reactive modes in Waaave Pool](https://www.youtube.com/watch?v=WKzOVSKeTwA) (2022-01-26, 37 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 1: Waaave Pool Geometry](https://www.youtube.com/watch?v=srA18OmaV7k) (2021-04-15, 15 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 2: Strobing in Waaave Pool (STROBE WARNING)](https://www.youtube.com/watch?v=gF_w1bqC0Iw) (2021-04-28, 13 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 10: Waaave Pool extra acid mode](https://www.youtube.com/watch?v=mUXKDGAY2SA) (2021-10-29, 14 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 11: Phosphorm and Waaave Pool](https://www.youtube.com/watch?v=gavGoFHIHog) (2021-11-10, 28 min)
- [Artificial Life x Waaave Pool](https://www.youtube.com/watch?v=RffzHlw1fbU) (2020-07-01, 2 min)
- [artificial_life+chromatic_aberration+waaaave_pool](https://www.youtube.com/watch?v=Yj5dQnWgsXM) (2020-08-09, 54 min)
- [al wp promo](https://www.youtube.com/watch?v=N_nNJZmcZuM) (2020-08-14, 7 min)
- [SUPER_HAECKEL_ADVENTURES_64+waaave_pool](https://www.youtube.com/watch?v=tA0iZ_aWaSw) (2020-03-25, 9 min)
- [waaave poolquality update1](https://www.youtube.com/watch?v=ekTBE5ujVM4) (2020-02-02, 3 min)
- [waaave poolquality update2](https://www.youtube.com/watch?v=eyufH2ZvVpY) (2020-02-02, 2 min)
- [Waaave Pool Commercial](https://www.youtube.com/watch?v=Q9Kx8YNLTyo) (2020-10-25, 1 min)
- [Waaave Pool Commercial 2](https://www.youtube.com/watch?v=wOrlWk73yPc) (2024-08-05, 1 min)

**Made with it**

- [TANTRICK ACID](https://www.youtube.com/watch?v=IRZ7DAvFnhY) (2022-12-12, 59 min)
- [ULTRATERRESTRIAL](https://www.youtube.com/watch?v=Dd2UwP-fbVE) (2022-02-25, 64 min)
- ["The Strange New Science of Chaos" A/V remix by Andrei Jay](https://www.youtube.com/watch?v=EkWsYGvnow4) (2021-02-22, 58 min)
- [Andrei Jay NYE 2020 Live A/v "Borganismgasm"](https://www.youtube.com/watch?v=VZs7sTbTYqs) (2021-01-01, 32 min)
- [GITs Waaave_Pool remix](https://www.youtube.com/watch?v=NJtwqSJF3pI) (2020-07-27, 84 min)

</details>

### ARTIFICIAL_LIFE
- [Github - ARTIFICIAL_LIFE 1.4](https://github.com/ex-zee-ex/artificial_life)
- [Github - ARTIFICIAL_LIFE 1.1](https://github.com/ex-zee-ex/artificial_life_1.1)
- [ARTIFICIAL_LIFE](https://andreijaycreativecoding.com/ARTIFICIAL_LIFE)
- [ARTIFICIAL_LIFE Manual](https://andreijaycreativecoding.com/Artificial-Life-Manual)

<details>
<summary>Videos (12)</summary>

- Playlist: [artificial_life demos](https://www.youtube.com/playlist?list=PLTAAQQpCNd6RbdQLAQcuEl_h3h6t4yVX2)

**Guides and demos**

- [Artificial Life Video Manual](https://www.youtube.com/watch?v=7hhpWgjskmI) (2020-08-27, 39 min)
- [Artificial life v1.4 updates: fun with feedback and strange colors!](https://www.youtube.com/watch?v=X38-Z9yJq1U) (2020-12-20, 48 min)
- [VSERPI 1.5 updates: Colorizer, PWM, new feedback modes in Artificial Life](https://www.youtube.com/watch?v=joOjknpc3iU) (2022-01-27, 29 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 3: Motion Recording in Artificial Life](https://www.youtube.com/watch?v=FQFhhICBoko) (2021-05-15, 11 min)
- [Artificial Life x Spectral Mesh](https://www.youtube.com/watch?v=vLedF2WYGso) (2020-07-01, 4 min)
- [Artificial Life x Waaave Pool](https://www.youtube.com/watch?v=RffzHlw1fbU) (2020-07-01, 2 min)
- [artificial_life+chromatic_aberration+waaaave_pool](https://www.youtube.com/watch?v=Yj5dQnWgsXM) (2020-08-09, 54 min)
- [al wp promo](https://www.youtube.com/watch?v=N_nNJZmcZuM) (2020-08-14, 7 min)

**Made with it**

- [XZX "arrival"](https://www.youtube.com/watch?v=q2AgWBK0pqU) (2023-11-28, 42 min)
- ["The Strange New Science of Chaos" A/V remix by Andrei Jay](https://www.youtube.com/watch?v=EkWsYGvnow4) (2021-02-22, 58 min)
- [Andrei Jay NYE 2020 Live A/v "Borganismgasm"](https://www.youtube.com/watch?v=VZs7sTbTYqs) (2021-01-01, 32 min)
- [Terence McKenna Live a/v remix by Paloma Kop & Andrei Jay](https://www.youtube.com/watch?v=smIJKRCRqjA) (2020-12-01, 28 min)

</details>

### AUTO_WAAAVE
- [GitHub - AUTO_WAAAVES](https://github.com/ex-zee-ex/auto_waaave)
- [AUTO_WAAAVE Quickstart Visual Guide](https://andreijaycreativecoding.com/auto-waaave-quickstart-pics)
- [AUTO_WAAAVE](https://andreijaycreativecoding.com/AUTO_WAAAVE)
- [AUTO_WAAAVE Manual](https://andreijaycreativecoding.com/AUTO-WAAAVE-MANUAL)

<details>
<summary>Videos (4)</summary>

- Playlist: [auto_waaaves demos](https://www.youtube.com/playlist?list=PLTAAQQpCNd6Q_9B_85HnfmQFks-BP_1tt)

**Guides and demos**

- [introduction to Auto Waaave](https://www.youtube.com/watch?v=JfgfqzUo99k) (2020-06-10, 20 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 4: Quick Start Guide to Auto Waaave](https://www.youtube.com/watch?v=6SPlqdmG8oU) (2021-07-05, 18 min)

**Made with it**

- [auto_waaave live performance 6-8-20](https://www.youtube.com/watch?v=wLabwFTN71s) (2020-06-10, 44 min)
- [auto_waaaves_live_improv](https://www.youtube.com/watch?v=7gi6hB0VgJc) (2020-06-14, 5 min)

</details>

### AUTO_MESH
- [Github - AUTO_MESH](https://github.com/ex-zee-ex/auto_mesh)
- [AUTO_MESH Manual](https://andreijaycreativecoding.com/AUTO-MESH-MANUAL)

<details>
<summary>Videos (1)</summary>

**Guides and demos**

- [Auto Mesh introduction and Demo](https://www.youtube.com/watch?v=PbzLcQtyohw) (2021-12-02, 33 min)

</details>

### CHROMATIC_ABBERATION
- [Github - CHROMATIC_ABBERATION](https://github.com/ex-zee-ex/CHROMATIC_ABERRATION1_the_search_for_sasquatch)
- [CHROMATIC_ABBERATION Manual](https://andreijaycreativecoding.com/CHROMATIC-ABERRATION-MANUAL)

<details>
<summary>Videos (5)</summary>

**Guides and demos**

- [VSERPI 1.5 updates: Introducing the New and Improved Chromatic Aberration: The Search For Sasquatch](https://www.youtube.com/watch?v=QBT0mDzNTHQ) (2022-01-27, 23 min)
- [VSERPI 1.5 updates: Using Chromatic Aberration with Camera feedback](https://www.youtube.com/watch?v=t85WM4kZS0w) (2022-02-01, 44 min)
- [artificial_life+chromatic_aberration+waaaave_pool](https://www.youtube.com/watch?v=Yj5dQnWgsXM) (2020-08-09, 54 min)
- [Video Feedback Techniques 7: colorizers/solarizers and 'post processing' fx on video feedback](https://www.youtube.com/watch?v=WMa89exzgg8) (2021-01-26, 65 min)

**Made with it**

- [;oierhlaiuef](https://www.youtube.com/watch?v=iR61FPMeOvc) (2020-04-08, 6 min)

</details>

### CONVOLUTIONAL CHAOS
- [GITHUB - CONVOLUTIONAL CHAOS](https://github.com/ex-zee-ex/convolutional_chaos)
- [CONVOLUTIONAL CHAOS MANUAL](https://andreijaycreativecoding.com/CONVOLUTIONAL-CHAOS-MANUAL)

<details>
<summary>Videos (1)</summary>

**Guides and demos**

- [VSERPI 1.5 updates: Welcome to Convolutional Chaos & master boot options!](https://www.youtube.com/watch?v=ztdeGePZ7jg) (2022-01-27, 11 min)

</details>

### GENERIC GEOMETRICAL UTILITY
- [Github - GENERIC GEOMETRICAL UTILITY](https://github.com/ex-zee-ex/GENERIC_GEOMETRY_UTILITY)
- [GENERIC GEOMETRICAL UTILITY Manual](https://andreijaycreativecoding.com/GENERIC-GRAPHICS-UTILITY-MANUAL)

<details>
<summary>Videos (1)</summary>

**Guides and demos**

- [VSERPI 1.5 updates: Checking out a Generic Geometrical Utility](https://www.youtube.com/watch?v=INcZ4epwcf0) (2022-01-27, 11 min)

</details>

### HELLO_WORD
- [Github - HELLO_WORD](https://github.com/ex-zee-ex/HELLO_WORD)
- [HELLO_WORD Manual](https://andreijaycreativecoding.com/HELLO-WORD-MANUAL)

<details>
<summary>Videos (1)</summary>

**Guides and demos**

- [VSERPI 1.5 updates: Introducing Hello Word _ & how to edit auto run configurations](https://www.youtube.com/watch?v=FkXYysgiMUw) (2022-01-27, 20 min)

</details>

### PHOSPHORM
- [GitHub - PHOSPHORM](https://github.com/ex-zee-ex/phosphorm)
- [PHOSPHORM](https://andreijaycreativecoding.com/PHOSPHORM)
- [PHOSPHORM Manual](https://andreijaycreativecoding.com/Phosphorm-Manual)

<details>
<summary>Videos (2)</summary>

- Playlist: [Phosphorm demos](https://www.youtube.com/playlist?list=PLTAAQQpCNd6QCcE_TZ5b3xcWgS5r2NzuH)

**Guides and demos**

- [introduction to Phosphorm audio visual synth](https://www.youtube.com/watch?v=eVEV8KhYzuQ) (2020-05-21, 23 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 11: Phosphorm and Waaave Pool](https://www.youtube.com/watch?v=gavGoFHIHog) (2021-11-10, 28 min)

</details>

### SUPER_HAECKEL_ADVENTURES_64
- [Github - SUPER_HAECKEL_ADVENTURES_64](https://github.com/ex-zee-ex/SUPER_HAECKEL_ADVENTURES_64)

<details>
<summary>Videos (4)</summary>

**Guides and demos**

- [SUPER_HAECKEL_ADveneNTURES_^$64](https://www.youtube.com/watch?v=NyhKSoA6Uw0) (2020-03-25, 5 min)
- [SUPER_HAECKEL_ADVENTURES_64+waaave_pool](https://www.youtube.com/watch?v=tA0iZ_aWaSw) (2020-03-25, 9 min)
- [SUPER_HAECKEL_ADVENTURES_64 plus camera feedback](https://www.youtube.com/watch?v=JsjTfDGGkXY) (2020-03-25, 6 min)
- [SUPER_HAECKEL_ADVENTURES_64 plus camera feedback more](https://www.youtube.com/watch?v=aWgWzkbR5fU) (2020-03-25, 7 min)

</details>

### SPECTRAL_MESH
- [GitHub - SPECTRAL_MESH](https://github.com/ex-zee-ex/spectral_mesh)
- [SPECTRAL_MESH](https://andreijaycreativecoding.com/SPECTRAL_MESH)
- [SPECTRAL_MESH Manual](https://andreijaycreativecoding.com/Spectral-Mesh-Manual)

<details>
<summary>Videos (9)</summary>

- Playlist: [Spectral Mesh demos](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SGOxYFaXQcYoRW-AfHxYNu)

**Guides and demos**

- [spectral mesh v 1.3 intro and walkthru](https://www.youtube.com/watch?v=NwRP-9H72ck) (2020-05-08, 34 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 9: Oscillator tips in Spectral Mesh](https://www.youtube.com/watch?v=2qfEWKwdayQ) (2021-09-22, 14 min)
- [Spectral Mesh basic plus edition demo and controls](https://www.youtube.com/watch?v=Mi2tZzgqrKI) (2020-02-18, 13 min)
- [Spectral_Mesh Demo0](https://www.youtube.com/watch?v=OOENycegIzM) (2020-02-17, 4 min)
- [Artificial Life x Spectral Mesh](https://www.youtube.com/watch?v=vLedF2WYGso) (2020-07-01, 4 min)
- [yreesytqesytsesyrgxes](https://www.youtube.com/watch?v=oZ_2q9kEpKY) (2020-03-05, 9 min)

**Made with it**

- [ULTRATERRESTRIAL](https://www.youtube.com/watch?v=Dd2UwP-fbVE) (2022-02-25, 64 min)
- ["The Strange New Science of Chaos" A/V remix by Andrei Jay](https://www.youtube.com/watch?v=EkWsYGvnow4) (2021-02-22, 58 min)
- [Kismet](https://www.youtube.com/watch?v=xVeVcH_1Wu0) (2020-07-16, 6 min)

</details>

### TEMPORAL_VORTEX
- [GITHUB - TEMPORAL_VORTEX](https://github.com/ex-zee-ex/temporal_vortex)
- [TEMPORAL_VORTEX](https://andreijaycreativecoding.com/TEMPORAL-VORTEX-manual)

<details>
<summary>Videos (6)</summary>

**Guides and demos**

- [Temporal Vortex: what the heck is a time oscillator??!!??](https://www.youtube.com/watch?v=8yTZuYnXt3k) (2020-12-20, 64 min)
- [Exploring the Video Synthesis Ecosphere RPI episode 6: WTF Temporal Vortex](https://www.youtube.com/watch?v=2xm3yR76xl4) (2021-07-28, 11 min)

**Made with it**

- [ULTRATERRESTRIAL](https://www.youtube.com/watch?v=Dd2UwP-fbVE) (2022-02-25, 64 min)
- ["The Strange New Science of Chaos" A/V remix by Andrei Jay](https://www.youtube.com/watch?v=EkWsYGvnow4) (2021-02-22, 58 min)
- [Andrei Jay NYE 2020 Live A/v "Borganismgasm"](https://www.youtube.com/watch?v=VZs7sTbTYqs) (2021-01-01, 32 min)
- [trance form](https://www.youtube.com/watch?v=nM6tey_fHNQ) (2020-11-15, 4 min)

</details>

## VSEJET (Video Synthesis Ecosphere Jetson Nano)
These run on the Nvidia Jetson Nano 4gb w/ sd-card (non-emmc version). GRAVITY_WAAAVES is one of the more advanced instruments. WAAAVE_POOL HD also runs on the Jetson Nano. And the GRAVITY_WAAAVES sd-card also has WAAAVE_POOL as a boot option.
- [VSEJET Manuals](https://andreijaycreativecoding.com/VSEJET-Manuals)
- [VSEJET DIY INSTRUCTIONS](https://andreijaycreativecoding.com/VSEJET-DIY-INSTRUCTIONS)
- [VSEJET Images](https://andreijaycreativecoding.com/VSEJET-images)
- [Midi Controller Overlays](/midi-controller-overlays)
  
### GRAVITY_WAAAVES
Contains master boot options for WAAAVEPOOL HD, ARTIFICIAL_LIFE HD, TEMPORAL_VORTEX HD, and CHROMATIC_ABBERATION HD.
- [GRAVITY_WAAAVES](https://andreijaycreativecoding.com/GRAVITY_WAAAVES-INFO)
- [GitHub - GRAVITY_WAAAVES_APP](https://github.com/ex-zee-ex/gravity_waaaves_app)
- [VSEJET Manuals](https://andreijaycreativecoding.com/VSEJET-Manuals)

<details>
<summary>Videos (12)</summary>

- Playlist: [GRAVITY WAAAVES](https://www.youtube.com/playlist?list=PLTAAQQpCNd6QheM2xVGeRzz4nJ9G5Ast9)
- Playlist: [VSEJET](https://www.youtube.com/playlist?list=PLTAAQQpCNd6QpSbuFFNtCGrLHLxoYmip4)

**Guides and demos**

- [a formal introduction to Gravity_Waaaves](https://www.youtube.com/watch?v=C-LE47vDiZg) (2022-11-09, 33 min)
- [gravity waaaves "vector feedback mode"](https://www.youtube.com/watch?v=hgEMUzqPZBE) (2023-11-25, 44 min)
- [gravity waaaves mixing and processing modes](https://www.youtube.com/watch?v=_hPIuHl1t6E) (2024-01-10, 24 min)
- [gravity waaaves doing some weird stuffs](https://www.youtube.com/watch?v=2Be6AMaHOA0) (2024-01-14, 19 min)
- [gravity waaaves patreon wage labor video 1-30](https://www.youtube.com/watch?v=50Aw9Pk1xuA) (2024-01-31, 52 min)
- [gravity waaaves: presets and macros](https://www.youtube.com/watch?v=0EwN1oaUCmM) (2024-05-23, 39 min)
- [Video Waaaves, Gravity Waaaves, and thoughts on Work and Jobs updates](https://www.youtube.com/watch?v=qd7IaJgaYxI) (2022-05-27, 34 min)

**Made with it**

- [andrei jay live a/v minneapolis 7-27-24](https://www.youtube.com/watch?v=9aMPgJV5qWY) (2024-09-26, 31 min)
- [XZX: psychedelic electronic music from the early 21st century](https://www.youtube.com/watch?v=MIdXXYiwd4I) (2024-04-12, 105 min)
- [XZX "arrival"](https://www.youtube.com/watch?v=q2AgWBK0pqU) (2023-11-28, 42 min)
- [synthetic forest performance at coaxial arts 10-31-23](https://www.youtube.com/watch?v=_ByBUr57YVo) (2023-11-26, 25 min)
- [Reality Orp "Out Of Phase"](https://www.youtube.com/watch?v=W3fyn56bgJc) (2023-05-29, 30 min)

</details>

### WAAAVE_POOL_HD
Contains master boot options for ARTIFICIAL_LIFE HD, TEMPORAL_VORTEX HD, CHROMATIC_ABBERATION HD, and The Search for Sasquatch HD.
- [WAAAVE_POOL HD Info](https://andreijaycreativecoding.com/WAAAVE_POOL-HD-INFO)
- [VSEJET Manuals](https://andreijaycreativecoding.com/VSEJET-Manuals)

<details>
<summary>Videos (7)</summary>

- Playlist: [WAAAVE POOL HD](https://www.youtube.com/playlist?list=PLTAAQQpCNd6QexJNnGEO1oLEWGEAjnTkv)

**Guides and demos**

- [Introducing Waaave Pool HD](https://www.youtube.com/watch?v=zUDO97-nNRM) (2023-11-25, 23 min)
- [Waaave Pool HD getting into the details & using feedback oscillators](https://www.youtube.com/watch?v=BQFd6qsyRqQ) (2023-12-03, 42 min)
- [Waaave Pool HD long delays examples](https://www.youtube.com/watch?v=d3HLSAJFqPA) (2024-01-12, 28 min)
- [patreon wage labor: WPHD, ALHD, TVHD, and the VSEJET ports!](https://www.youtube.com/watch?v=LwYg85fwVes) (2024-04-12, 59 min)

**Made with it (strobe warning)**

- [DJ TURD BURGLAR "100 TRANCE COUNTRY HITS"](https://www.youtube.com/watch?v=536nOgF6Jd0) (2026-05-15, 48 min)
- [DJ TURD BURGLAR "SPREAD SPECTRUM](https://www.youtube.com/watch?v=D8XAND815Gg) (2026-05-15, 37 min)
- [DJ TURD BURGLAR "LANGUAGE OF BIRDS"](https://www.youtube.com/watch?v=PkVh0X-ktTQ) (2026-05-15, 47 min)

</details>

### WAAAVE_POOL_HD LTD
Limited 1080p run of WAAAVE_POOL HD with a 4 second delay buffer (the 720p version has 8). A public image is planned for [Q1 2027](https://videosynthesisecosphere.com/faq).
- [WAAAVE_POOL HD LTD](https://videosynthesisecosphere.com/waaave-pool-hd-ltd)
- [Buy WAAAVE_POOL HD LTD @ VideoSynthesisEcosphere.com](https://shop.videosynthesisecosphere.com/products/waaave-pool-hd-limited-edition)

<details>
<summary>Videos (1)</summary>

**Guides and demos**

- [Waaave Pool HD LTD edition: What the Heck is THis??](https://www.youtube.com/watch?v=kfPE9eIRR3w) (2026-11-06, 71 min)

</details>

## General videos
Video feedback techniques, video mixer guides, and other video art software.

<details>
<summary>Videos (33)</summary>

- Playlist: [Video feedback techniques](https://www.youtube.com/playlist?list=PLTAAQQpCNd6Ri-dYis3s7TAjSxWEetB9o)
- Playlist: [Video mixer guides](https://www.youtube.com/playlist?list=PLTAAQQpCNd6SsMv4FAbpgF3l0vBU7iPfg)
- Playlist: [Video signals AMA](https://www.youtube.com/playlist?list=PLTAAQQpCNd6QuNQ0C86YyWk4uXD6Fp6yF)
- Playlist: [Lectures and talks](https://www.youtube.com/playlist?list=PLTAAQQpCNd6Q5B8Wtk-99Lsbiyy5iTh4u)
- Playlist: [Video Synthesis Tarot](https://www.youtube.com/playlist?list=PLTAAQQpCNd6QOYGgVjOZezk_c7xcZysEo)

**Video feedback techniques**

- [video feedback techniques 1 the basics: part 1](https://www.youtube.com/watch?v=mp7QVMx2zBY) (2019-10-09, 23 min)
- [video feedback techniques 1 the basics: part 2](https://www.youtube.com/watch?v=TZofjUsKvvE) (2019-10-09, 26 min)
- [video feedback techniques 1 the basics: part 3](https://www.youtube.com/watch?v=5rFXOaW_d-M) (2019-10-09, 21 min)
- [video feedback techniques 2 HSB: part 1](https://www.youtube.com/watch?v=LOeLpCY3Ln0) (2019-10-27, 28 min)
- [video feedback techniques 2 part 2 LCDs, signal chains, and keying](https://www.youtube.com/watch?v=O8ttX91X5cc) (2019-10-27, 25 min)
- [video feedback techniques 2: part 3 addendum](https://www.youtube.com/watch?v=Hd3XPLfAjZg) (2019-10-27, 28 min)
- [video feedback techniques 3: digital cameras and lcds, splitting signals](https://www.youtube.com/watch?v=qU-k7J-Chy4) (2019-10-27, 24 min)
- [video feedback techniques 4 part 1: PSYCHOKENSIES MODE](https://www.youtube.com/watch?v=xGVMxSmR5qE) (2020-01-30, 32 min)
- [Video Feedback Techniques 4 part 2: PSYCKONEKISIS mode](https://www.youtube.com/watch?v=JW1y_6aqSZQ) (2020-01-30, 27 min)
- [video feedback techniques 4 part3 SIKOKEiNSES MODE](https://www.youtube.com/watch?v=sFgS3WkPVwE) (2020-01-30, 33 min)
- [Video Feedback Techniques 5: 2 cameras part 1](https://www.youtube.com/watch?v=PkJk278kCG4) (2020-04-25, 27 min)
- [Video Feedback Techniques 5: 2 cameras part 2](https://www.youtube.com/watch?v=O1DoXyZVrJU) (2020-04-25, 29 min)
- [Video Feedback Techniques 5: 2 cameras part 3](https://www.youtube.com/watch?v=JcnwL8uRs9c) (2020-04-25, 28 min)
- [Video Feedback Techniques 6: external video processors and enhancers part 1](https://www.youtube.com/watch?v=Xt-IsoW9MgA) (2020-07-24, 47 min)
- [Video Feedback Techniques 6: external video processors and enhancers part 2](https://www.youtube.com/watch?v=vUCL902iSO4) (2020-07-24, 25 min)
- [Video Feedback Techniques 7: colorizers/solarizers and 'post processing' fx on video feedback](https://www.youtube.com/watch?v=WMa89exzgg8) (2021-01-26, 65 min)
- [Video Feedback Techniques 8: Getting Practical (patreon video april 2024)](https://www.youtube.com/watch?v=lEZx5cOTNzg) (2024-04-27, 50 min)

**Video mixer guides**

- [video mixer guide: panasonic mx-30](https://www.youtube.com/watch?v=uRN4In4n_Kk) (2026-07-14, 28 min)
- [Video Mixer Guides: panasonic mx-50](https://www.youtube.com/watch?v=5QKaLSlbIek) (2026-07-14, 29 min)
- [video mixer guide: panasonic mx-70](https://www.youtube.com/watch?v=HVC-RmDq-WQ) (2026-08-03, 40 min)
- [video mixer guide: videonics mx-1](https://www.youtube.com/watch?v=5ffYzRGL84I) (2026-07-14, 32 min)
- [video mixer guide: edirol v-4](https://www.youtube.com/watch?v=bjlFtHz_xJs) (2026-07-14, 29 min)

**Signals, talks, and performance**

- [Introduction to Analog Video Signals](https://www.youtube.com/watch?v=VY4tbBpCGAA) (2023-05-21, 89 min)
- [Fubar presents: Myth and Magic of Analog and Digital](https://www.youtube.com/watch?v=pgxSvd9PKfY) (2021-10-05, 50 min)
- [patreon wage labor video February 2024: VJ tips and tricks & history of Jeff Minter's visualizers](https://www.youtube.com/watch?v=zZjjOqO-5lI) (2024-02-21, 75 min)

**Other software (Vsynth, Hydra, OBS)**

- [digital video synthesis in vsynth: a polyphase portal class](https://www.youtube.com/watch?v=EXDxGz3gtfg) (2024-05-21, 11 min)
- [really really basic ping pong buffer video feedback biz in obs studio](https://www.youtube.com/watch?v=JM_3YSS7puE) (2024-01-11, 15 min)
- [vsynth workshop 07 14 20 modulation and feedback](https://www.youtube.com/watch?v=FbtHGmjGVFM) (2020-07-16, 59 min)
- [vsynth class 08 04 20](https://www.youtube.com/watch?v=_HrvuoxeR4I) (2020-08-05, 58 min)
- [vsynth class 08 25 20](https://www.youtube.com/watch?v=phwwox5Lctw) (2020-08-26, 59 min)
- [hydra workshop 07_12_20: modulation and feedback](https://www.youtube.com/watch?v=fVQxY-OUglI) (2020-07-16, 60 min)
- [hydra class 07 28 20](https://www.youtube.com/watch?v=RIZLGMyTbbs) (2020-07-29, 58 min)
- [hydra class 08 18 20](https://www.youtube.com/watch?v=0zCxBVsy0dc) (2020-08-19, 60 min)

</details>
