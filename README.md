# VoDi

VoDi is a simple GUI for calculating electric parts like

* series resistors for LEDs
* resistors for voltage dividers
* shunt resistor voltage values

## Build and run

This is an CMake base project. Qt development packages have to be installed.
On linux you can run:
```
mkdir build
cd build
cmake ..
make -j$(nproc)
```
To start the application:
```
./vodi_gui
```
