# verifytapn

VerifyTAPN is a stand-alone verification engine for timed-arc Petri nets, developed for the verification tool TAPAAL.

## Linux

Install dependencies:
```bash
sudo apt update
sudo apt install cmake ninja-build make flex bison gcc-16 g++-16
```

Build a release:
```bash
export PATH="$(brew --prefix bison)/bin:$(brew --prefix flex)/bin:$PATH"
cmake --workflow release
```

## Mac OS

Install Xcode through the App Store.

Install dependencies:
```bash
brew install cmake ninja flex bison gcc@16
```

Build a release:
```bash
cmake --workflow release
```

## Windows (Cross Compile)

Install dependencies:
```bash
sudo apt update
sudo apt install cmake ninja-build make flex bison mingw-w64
```

Build a Windows release:
```bash
cmake --workflow win64-release
```

## CMake Workflows

| Workflow | Purpose | Build directory |
| --- | --- | --- |
| `release` | Release build | `build-release` |
| `debug` | Debug build | `build-debug` |
| `win64-release` | Windows cross-compiled release | `build-win64-release` |
