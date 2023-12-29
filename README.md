# VitaControl
Use bluetooth controllers on your Vita!

### Overview
VitaControl is a plugin that aims to support a wide variety of bluetooth controllers on the PlayStation Vita. It uses an
object-oriented design, which makes it easy to add support for new controllers. VitaControl is based on
[ds34vita](https://github.com/MERLev/ds34vita) by MERLev, which is based on [ds3vita](https://github.com/xerpi/ds3vita)
and [ds4vita](https://github.com/xerpi/ds4vita) by xerpi.

### Downloads
The latest build of VitaControl is automatically provided via GitHub Actions, and can be downloaded from the
[releases page](https://github.com/Hydr8gon/VitaControl/releases).

### Usage
Place `vitacontrol.skprx` in the `ur0:tai/` directory on your Vita. Open `config.txt` in the same folder and add
`ur0:tai/vitacontrol.skprx` under the `*KERNEL` header. Reboot the Vita and pair your controllers through the Settings
app! If you have issues with a controller when it's first paired, it might work after another reboot.

### Supported Controllers
* Sony DualShock 3 Controller
* Sony DualShock 4 Controller
* Sony DualSense Controller
* Sony DualSense Edge Controller
* Microsoft Xbox One Controller
* Nintendo Switch Pro Controller

### Contributing
Pull requests are welcome for this project. I can add support for controllers that I have access to and am interested
in, but anything else is up to the community. If you know your way around code and have a controller that you'd like to
support, it shouldn't be too hard to add. You can check if projects such as
[MissionControl](https://github.com/ndeadly/MissionControl) or [SDL](https://github.com/libsdl-org/SDL) have drivers for
the controller that you can use as a reference.

### Building
To build VitaControl, you need to install [Vita SDK](https://vitasdk.org). With that set up, run
`mkdir -p build && cd build && cmake .. && make -j$(nproc)` in the project root directory to start building.

### Other Links
* [Hydra's Lair](https://hydr8gon.github.io) - Blog where I may or may not write about things
* [Discord Server](https://discord.gg/JbNz7y4) - A place to chat about my projects and stuff
