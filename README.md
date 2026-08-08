# SolarUI

A lightweight UI library built for OpenGL / FreeGLUT.

## Features

- Buttons
- Sliders
- Labels
- Tiles

## Installation

Link against:

libSolarUI.a

Include:

#include "SolarUI.h"

## Example

```cpp
SolarUI::Button btn(50, 50, 120, 40, "Hello");
btn.Draw();
```
## License

SolarUI is licensed under the MIT License.

See LICENSE for details.

## File structure
SolarUI/
│
├── include/
│   ├── SolarUI.h
│   ├── SolarUI_exp.h
│   └── SolarUI_com.h
│
├── src/
│   ├── Solar_UI.c
│   │
│   ├── external/
│   │   ├── freeglut/
│   │   ├── stb_image.h
│   │   ├── miniaudio.h
│   │   └── libVLC.h
│   │
│   ├── bridges/
│   │   ├── Solar_UI_freeGLUT_Bridge.c
│   │   └── Solar_UI_Input_Bridge.c
│   │
│   ├── internal/
│   │   ├── Solar_UI_Input.c
│   │   ├── Solar_UI_Render.c
│   │   └── Solar_UI_Media.c
│   │
│   └── elements/
│       ├── Label/
│       │   ├── Label.h
│       │   └── Label.c
│       │
│       ├── Button/
│       │   ├── Button.h
│       │   └── Button.c
│       │
│       ├── Slider/
│       │   ├── Slider.h
│       │   └── Slider.c
│       │
│       ├── Checkbox/
│       │   ├── Checkbox.h
│       │   └── Checkbox.c
│       │
│       ├── Image/
│       │   ├── Image.h
│       │   └── Image.c
│       │
│       ├── Video/
│       │   ├── Video.h
│       │   └── Video.c
│       │
│       ├── Dropdown/
│       │   ├── Dropdown.h
│       │   └── Dropdown.c
│       │
│       └── LabelInput/
│           ├── LabelInput.h
│           └── LabelInput.c
│
└── CMakeLists.txt