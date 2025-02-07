# VSERPI Midi Notes

## WAAAVEPOOL
Attempting to understand which controls for WAAAVEPOOL are uni-polar vs bi-polar. Looking at `ofApp.cpp` there are two numbers used for scaling. Hardcoded `127.0` for uni-polar, and the value of the variable `MIDI_Magic 63.50` for bi-polar. This validates the hand-drawn control scheme map.  

<details>
<summary>
WavePool NanoKontrol2 default button positions
</summary>

![wp-controls](https://github.com/user-attachments/assets/eb3da170-9384-42d1-afa9-6d4ac1ee2370)  
</details>

Note for slider values, there is an additional scaling factor if `S,M,R` buttons next to the fader is pressed.


| **Param #** | **MIDI Control Number** | **Parameter Affected**         | **Type** |
|------------|-------------------------|--------------------------------|-----------|
| **1**  | **16**  | `vLumakeyValue` (Luma Key Threshold) | **Uni** |
| **2**  | **17**  | `vMix` (Blending between video layers) | **Bi** |
| **3**  | **18**  | `vHue` (Hue shift) | **Bi** |
| **4**  | **19**  | `vSaturation` (Color saturation) | **Bi** |
| **5**  | **20**  | `vBright` (Brightness) | **Bi** |
| **6**  | **21**  | `vTemporalFilterMix` (Temporal Filter Mix) | **Bi** |
| **7**  | **22**  | `vTemporalFilterResonance` (Temporal Filter Brightness) | **Uni** |
| **8**  | **23**  | `vSharpenAmount` (Sharpening filter strength) | **Uni** |
| **9**  | **120** | `vX` (X displacement) | **Bi** |
| **10** | **121** | `vY` (Y displacement) | **Bi** |
| **11** | **122** | `vZ` (Z displacement) | **Bi** |
| **12** | **123** | `vRotate` (Rotation) | **Bi** |
| **13** | **124** | `vHuexMod` (Hue modulation) | **Uni** |
| **14** | **125** | `vHuexOff` (Hue offset) | **Bi** |
| **15** | **126** | `vHuexLfo` (Hue LFO mod) | **Bi** |
| **16** | **127** | `???` (Framebuffer Delay) | **Uni** |
| **A**  | **43**  | `brightInvert` (Brightness Inversion) | **Toggle** |
| **B**  | **44**  | `saturationInvert` (Saturation Inversion) | **Toggle** |
| **C**  | **42**  | `hueInvert` (Hue Inversion) | **Toggle** |
| **D**  | **41**  | `horizontalMirror` (Horizontal Mirroring) | **Toggle** |
| **E**  | **45**  | `verticalMirror` (Vertical Mirroring) | **Toggle** |
| **F**  | **46**  | `toroidSwitch` (Toroid Wraparound Effect) | **Toggle** |
| **G**  | **60**  | `lumakeyInvertSwitch` (Luma Key Inversion) | **Toggle** |
| **H**  | **61**  | `mirrorSwitch` (Mirror Switch - Might affect both horizontal & vertical) | **Toggle** |
| **I**  | **62**  | `hdmi_aspect_ratio_switch` (HD/SD Aspect Ratio) | **Toggle** |
| **J**  | **58**  | `clear_switch` (Clear Framebuffer) | **Momentary** |
| **K**  | **59**  | `multiple` (Parameter reset/Motion recording clear/video reactive parameter reset) | **Momentary** |
| **L**  | **71**  | `wet_dry_switch` (Feedback/Feedforward delay shift) | **Toggle** |
| **M**  | **55**  | `p_lock_switch` (Motion Recording) | **Toggle** |
| **N**  | **39**  | `videoReactiveSwitch` (Enable/Disable Video Reactive Mode) | **Toggle** |





