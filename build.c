#include "ForgeC/build.h"

#define DEBUG_BUILD 1 // 1 for debug 0 for release

int main() {
    build_env_t* build_enviroment = forgec_init();
    forgec_select_compiler(build_enviroment, "gcc");
    forgec_add_include_dir(build_enviroment, "include");
    forgec_add_source_files_from_dir(build_enviroment, "src");

    #ifdef _WIN32
        forgec_add_compiler_arg(build_enviroment, "-lws2_32");
        forgec_build_shared(build_enviroment, "LibDiesel.dll", DEBUG_BUILD);
        system("mkdir Build\\include");
        system("xcopy include Build\\include /E /I /Y");
    #elif defined(__APPLE__)
        forgec_build_shared(build_enviroment, "LibDiesel.dylib", DEBUG_BUILD);
        system("mkdir -p Build/include");
        system("cp -r include/* Build/include");
    #else
        forgec_build_shared(build_enviroment, "LibDiesel.so", DEBUG_BUILD);
        system("mkdir -p Build/include");
        system("cp -r include/* Build/include");
    #endif

    forgec_cleanup(build_enviroment);
}
