#ifdef _WIN32
  #ifdef WIN_EXPORT
    #define EXPORT __declspec(dllexport)
  #else
    #define EXPORT __declspec(dllimport)
  #endif
#else
  #define EXPORT __attribute__((visibility("default")))
#endif
