# VitaControl
Use bluetooth controllers on your Vita!

### Overview
VitaControl aims to support a wide variety of bluetooth controllers on the PlayStation Vita, as well as making it easy to add support for new ones. Pull requests are welcome!

### Downloads
Automatic builds are provided via GitHub Actions; you can download the latest one from the [releases page](https://github.com/Hydr8gon/VitaControl/releases).

### Usage
Place `vitacontrol.skprx` in the `ur0:tai/` directory on your Vita. Open `config.txt` in the same folder and add `ur0:tai/vitacontrol.skprx` under the `*KERNEL` header. Reboot the Vita and pair your controllers through the Settings app!

### Supported Controllers
* Sony DualShock 3 Controller
* Sony DualShock 4 Controller
* Sony DualSense Controller
* Microsoft Xbox One Controller
* Nintendo Switch Pro Controller

### Compiling
If you want to compile VitaControl yourself, you'll need to set up [Vita SDK](https://vitasdk.org). The project uses CMake, so you can build it with the following command: `mkdir -p build && cd build && cmake .. && make`.

### References
* [ds3vita](https://github.com/xerpi/ds3vita) and [ds4vita](https://github.com/xerpi/ds4vita) by xerpi - The plugins that ds34vita is based on
* [ds34vita](https://github.com/MERLev/ds34vita) by MERLev - The plugin that this is based on
* [MissionControl](https://github.com/ndeadly/MissionControl) by ndeadly - Inspiration for this project, and driver reference
* [SDL](https://github.com/libsdl-org/SDL) by libsdl-org - Another good driver reference
