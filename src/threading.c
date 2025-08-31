#include "threading.h"

#if defined(DISTRO_WIN32)

// -------------------- Windows Implementation --------------------

thread_t thread_create(void (*func)(void*), void* arg) {
    return CreateThread(
        NULL,                // default security
        0,                   // default stack size
        (LPTHREAD_START_ROUTINE)func,
        arg,                 // argument to pass
        0,                   // run immediately
        NULL                 // thread id not needed
    );
}

void thread_join(thread_t thread) {
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
}

void thread_yield(void) {
    SwitchToThread();
}

void mutex_init(mutex_t* mutex) {
    InitializeCriticalSection(mutex);
}

void mutex_lock(mutex_t* mutex) {
    EnterCriticalSection(mutex);
}

void mutex_unlock(mutex_t* mutex) {
    LeaveCriticalSection(mutex);
}

void mutex_destroy(mutex_t* mutex) {
    DeleteCriticalSection(mutex);
}

#else

// -------------------- POSIX Implementation --------------------

thread_t thread_create(void (*func)(void*), void* arg) {
    pthread_t thread;
    pthread_create(&thread, NULL, (void* (*)(void*))func, arg);
    return thread;
}

void thread_join(thread_t thread) {
    pthread_join(thread, NULL);
}

void thread_yield(void) {
    sched_yield();
}

void mutex_init(mutex_t* mutex) {
    pthread_mutex_init(mutex, NULL);
}

void mutex_lock(mutex_t* mutex) {
    pthread_mutex_lock(mutex);
}

void mutex_unlock(mutex_t* mutex) {
    pthread_mutex_unlock(mutex);
}

void mutex_destroy(mutex_t* mutex) {
    pthread_mutex_destroy(mutex);
}

#endif
