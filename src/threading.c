#include "threading.h"
#include "_export.h"

#if defined(DISTRO_WIN32)

// -------------------- Windows Implementation --------------------

DIESEL_API thread_t thread_create(void (*func)(void*), void* arg) {
    return CreateThread(
        NULL,                // default security
        0,                   // default stack size
        (LPTHREAD_START_ROUTINE)func,
        arg,                 // argument to pass
        0,                   // run immediately
        NULL                 // thread id not needed
    );
}

DIESEL_API void thread_join(thread_t thread) {
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
}

DIESEL_API void thread_yield(void) {
    SwitchToThread();
}

DIESEL_API void mutex_init(mutex_t* mutex) {
    InitializeCriticalSection(mutex);
}

DIESEL_API void mutex_lock(mutex_t* mutex) {
    EnterCriticalSection(mutex);
}

DIESEL_API void mutex_unlock(mutex_t* mutex) {
    LeaveCriticalSection(mutex);
}

DIESEL_API void mutex_destroy(mutex_t* mutex) {
    DeleteCriticalSection(mutex);
}

#else

// -------------------- POSIX Implementation --------------------

DIESEL_API thread_t thread_create(void (*func)(void*), void* arg) {
    pthread_t thread;
    pthread_create(&thread, NULL, (void* (*)(void*))func, arg);
    return thread;
}

DIESEL_API void thread_join(thread_t thread) {
    pthread_join(thread, NULL);
}

DIESEL_API void thread_yield(void) {
    sched_yield();
}

DIESEL_API void mutex_init(mutex_t* mutex) {
    pthread_mutex_init(mutex, NULL);
}

DIESEL_API void mutex_lock(mutex_t* mutex) {
    pthread_mutex_lock(mutex);
}

DIESEL_API void mutex_unlock(mutex_t* mutex) {
    pthread_mutex_unlock(mutex);
}

DIESEL_API void mutex_destroy(mutex_t* mutex) {
    pthread_mutex_destroy(mutex);
}

#endif
