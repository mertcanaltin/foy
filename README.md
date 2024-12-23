
# Foy: A Custom JavaScript Runtime

Foy is a custom JavaScript runtime built using the [V8 JavaScript engine](https://v8.dev/) and [libuv](https://libuv.org/). It is designed to execute JavaScript files, providing a lightweight runtime environment similar to Node.js and Deno.

## Features

- **V8 Engine**: Utilizes the powerful V8 engine to execute JavaScript efficiently.
- **libuv Integration**: Manages asynchronous I/O operations using libuv, providing non-blocking event-driven capabilities.
- **Cross-Platform**: Designed to work across multiple platforms, including macOS, Linux, and Windows.

## Getting Started

### Prerequisites

- CMake (version 3.15 or higher)
- C++17 compatible compiler
- [V8](https://v8.dev/docs/build) JavaScript engine and [libuv](https://libuv.org/)

### Cloning the Repository

Since the project uses submodules (for V8 and libuv), you need to clone the repository with its submodules using the following command:

```bash
git clone --recurse-submodules https://github.com/mertcanaltin/foy.git
cd foy
```

If you've already cloned the repository without submodules, you can initialize and update them with:

```bash
git submodule update --init --recursive
```

### Building the Project

1. Configure the build:

   ```bash
   mkdir build && cd build
   cmake ..
   ```

2. Build the project:

   ```bash
   make
   ```

3. Run a JavaScript file:

   ```bash
   ./foy your-script.js
   ```

## Contributing

Contributions are welcome! If you find any issues or have feature suggestions, feel free to open a pull request or file an issue.

## License

This project is licensed under the MIT License.
