# Simple Direct Chat

C++ Console client-server application for communicating with server-connected clients.

## Dependencies

The project uses the following libraries and tools:
- [Boost.Asio](https://www.boost.org/doc/libs/1_84_0/doc/html/boost_asio.html).

## Installation

Before starting the installation, make sure you have the following components installed:
- CMake
- vcpkg
- Boost C++ libraries

### Installation Instructions

1. Set the `VCPKG_HOME` PATH env. variable with the path to your `vcpkg` folder.

2. Clone the repository:

```bash
git clone https://github.com/strukfit/simple-direct-chat.git
```

3. Go to the project directory:
```bash
cd simple-direct-chat
```

4. Create a build directory and go to it:
```bath
mkdir build
cd build
```

5. Generate the build files using CMake:
```bath
cmake ..
```

## Usage

To launch the server use command:

```bash
serverapp <port>
```

To launch the client use command:

```bash
clientapp <host> <port>
```
