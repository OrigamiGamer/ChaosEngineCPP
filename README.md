# ChaosEngineCPP
 A version of ChaosEngine for C++ is developing...

# Build

### 1. Make sure your computer had installed CMake

### 2. Clone repository
- `https://github.com/OrigamiGamer/ChaosEngineCPP.git`

### 3. Build `ChaosEngine.lib`

- #### in `Visual Studio`(recommend):
- 1. Open the project folder (root path, the source codes of `ChaosEngine.lib`) in Visual Studio,
      choose the cmake configuration `x64-Debug`;
- 2. Build the project (hot-key is `Ctrl+Shift+B`), by default, it'll be compiled in `\build\x64-Debug\` in root path;

<!--
- #### If you want to use `Visual Studio Code` to make games:
- 1. Press `Ctrl+Shift+P` to open Command Palette, and execute `CMake: Install`;
- 2. Then execute `CMake: Build`.
-->

### 4. Prepare folder for making new game
- Finally, copy a backup of "NewGame" folder, rename the folder (instead of any file in the folder), then begin making your game!



# Dependence
| name					| url											| Author			| License				|
|-----------------------|-----------------------------------------------|-------------------|-----------------------|
| JSON					| https://github.com/nlohmann/json				| Niels Lohmann		| MIT					|
| ChakraCore			| https://github.com/chakra-core/ChakraCore		| Microsoft			| MIT					|
| FMOD					|												| 					|						|
