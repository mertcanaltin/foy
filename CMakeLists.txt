# C++ standardını belirliyoruz
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.14)

project(MyRuntime)

# Derleyici seçenekleri ve C++ kütüphanesi ayarları
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

# V8 kütüphanesini ve include dizinlerini ekliyorum
include_directories(${PROJECT_SOURCE_DIR}/deps/v8/include)
link_directories(${PROJECT_SOURCE_DIR}/deps/v8/out.gn/arm64.release/obj)

# Libuv'i ekliyorum
include_directories(${PROJECT_SOURCE_DIR}/deps/libuv/include)

# Ana executable tanımları
add_executable(my_runtime src/main.cpp src/lib/my_module.cpp)

# Libuv statik bağlama (libuv.a dosyasını kullan)
target_link_libraries(my_runtime ${PROJECT_SOURCE_DIR}/deps/libuv/.libs/libuv.a v8_monolith pthread dl)
