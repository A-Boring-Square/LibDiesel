#ifdef _WIN32
  #ifdef WIN_EXPORT
    #define DIESEL_API __declspec(dllexport)
  #else
    #define DIESEL_API __declspec(dllimport)
  #endif
#else
  #define DIESEL_API __attribute__((visibility("default")))
#endif
