#include "ForgeC/build.h"

#define DEBUG_BUILD 0 // 1 for debug 0 for release

int main() {
    build_env_t* build_enviroment = forgec_init();
    forgec_select_compiler(build_enviroment, "gcc");
    forgec_add_include_dir(build_enviroment, "include");
    forgec_add_source_files_from_dir(build_enviroment, "src");
    forgec_add_compiler_arg(build_enviroment, "-Wno-discarded-qualifiers");
    forgec_add_compiler_arg(build_enviroment, "-DWIN_EXPORT");


    #ifdef _WIN32
        forgec_add_compiler_arg(build_enviroment, "-lws2_32");
        forgec_add_compiler_arg(build_enviroment, "-ldbghelp");
        forgec_build_shared(build_enviroment, "LibDiesel.dll", DEBUG_BUILD);
        system("mkdir Build\\include");
        system("xcopy include Build\\include /E /I /Y");
        forgec_add_compiler_arg(build_enviroment, "-DWIN_EXPORT");
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
