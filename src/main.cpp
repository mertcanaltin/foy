#include <uv.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <v8.h>
#include <libplatform/libplatform.h>

// Timer callback function
void OnTimeout(uv_timer_t* handle) {
    std::cout << "Timer triggered!" << std::endl;
}

// Function to read JavaScript file
std::string ReadJSFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        exit(1);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to execute JavaScript code using V8
void ExecuteJS(const std::string& js_code) {
    // Initialize V8
    v8::V8::InitializeICUDefaultLocation("");
    v8::V8::InitializeExternalStartupData("");
    std::unique_ptr<v8::Platform> platform = v8::platform::NewSingleThreadedDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    // Create a new Isolate and make it the current one
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);

    {
        v8::Isolate::Scope isolate_scope(isolate);
        v8::HandleScope handle_scope(isolate);

        // Create a new context
        v8::Local<v8::Context> context = v8::Context::New(isolate);
        v8::Context::Scope context_scope(context);

        // Compile and run the JavaScript code
        v8::Local<v8::String> source =
            v8::String::NewFromUtf8(isolate, js_code.c_str()).ToLocalChecked();
        v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
        v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

        // Convert the result to a string and print it
        v8::String::Utf8Value utf8(isolate, result);
        std::cout << *utf8 << std::endl;
    }

    // Dispose the isolate and tear down V8
    isolate->Dispose();
    v8::V8::Dispose();
    delete create_params.array_buffer_allocator;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./my_runtime <js_file>" << std::endl;
        return 1;
    }

    // Read JavaScript file
    std::string js_code = ReadJSFile(argv[1]);

    // Initialize libuv event loop
    uv_loop_t* loop = uv_default_loop();
    
    // Create a timer
    uv_timer_t timer_req;
    uv_timer_init(loop, &timer_req);
    uv_timer_start(&timer_req, OnTimeout, 1000, 0);  // 1 second delay

    // Execute JavaScript code
    ExecuteJS(js_code);

    // Run the event loop
    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}
