#include "ForgeC/build.h"

#define DEBUG_BUILD 0 // 1 = Debug, 0 = Release

int main() {
    build_env_t* build_enviroment = forgec_init();

    forgec_select_compiler(build_enviroment, "gcc");
    forgec_add_include_dir(build_enviroment, "include");
    forgec_add_source_files_from_dir(build_enviroment, "src");

    // Common compiler flags
    forgec_add_compiler_arg(build_enviroment, "-Wno-discarded-qualifiers");

    #ifdef _WIN32
        // Export symbols when building the DLL
        forgec_add_compiler_arg(build_enviroment, "-DWIN_EXPORT");

        // Link against Windows system libraries
        forgec_add_compiler_arg(build_enviroment, "-lws2_32");
        forgec_add_compiler_arg(build_enviroment, "-ldbghelp");

        // Generate DLL + .lib import library for MinGW
        forgec_add_compiler_arg(build_enviroment, "-Wl,--out-implib,Build/LibDiesel.lib");

        // Build the DLL
        forgec_build_shared(build_enviroment, "LibDiesel.dll", DEBUG_BUILD);

        // Copy public headers to Build/include
        system("mkdir Build\\include");
        system("xcopy include Build\\include /E /I /Y");

    #elif defined(__APPLE__)
        forgec_add_compiler_arg(build_enviroment, "-fPIC");
        forgec_build_shared(build_enviroment, "LibDiesel.dylib", DEBUG_BUILD);
        system("mkdir -p Build/include");
        system("cp -r include/* Build/include");

    #else
        forgec_add_compiler_arg(build_enviroment, "-fPIC");
        forgec_build_shared(build_enviroment, "LibDiesel.so", DEBUG_BUILD);
        system("mkdir -p Build/include");
        system("cp -r include/* Build/include");
    #endif

    forgec_cleanup(build_enviroment);
}
