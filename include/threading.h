#ifndef LIB_DIESEL_THREADING_H
#define LIB_DIESEL_THREADING_H

#include "types.h"
#include "platform.h"
#include "_export.h"

#if defined(DISTRO_WIN32)
#include <Windows.h>

/**
 * @brief Cross-platform thread type
 */
typedef HANDLE thread_t;

/**
 * @brief Cross-platform mutex type
 */
typedef CRITICAL_SECTION mutex_t;

#else // POSIX
#include <pthread.h>
#include <sched.h>

/**
 * @brief Cross-platform thread type
 */
typedef pthread_t thread_t;

/**
 * @brief Cross-platform mutex type
 */
typedef pthread_mutex_t mutex_t;

#endif // DISTRO_WIN32

/**
 * @brief Creates a new thread
 * @param func Pointer to the function to run in the new thread. Signature: void func(void* arg)
 * @param arg Argument to pass to the thread function
 * @return thread_t The handle or identifier for the created thread
 */
DIESEL_API thread_t thread_create(void (*func)(void*), void* arg);

/**
 * @brief Waits for the specified thread to finish
 * @param thread The thread handle/identifier to join
 * @return void
 */
DIESEL_API void thread_join(thread_t thread);

/**
 * @brief Yields the current thread's execution to other threads
 * @return void
 */
DIESEL_API void thread_yield(void);

/**
 * @brief Initializes a mutex
 * @param mutex Pointer to the mutex to initialize
 * @return void
 */
DIESEL_API void mutex_init(mutex_t* mutex);

/**
 * @brief Locks a mutex
 * @param mutex Pointer to the mutex to lock
 * @return void
 */
DIESEL_API void mutex_lock(mutex_t* mutex);

/**
 * @brief Unlocks a mutex
 * @param mutex Pointer to the mutex to unlock
 * @return void
 */
DIESEL_API void mutex_unlock(mutex_t* mutex);

/**
 * @brief Destroys a mutex
 * @param mutex Pointer to the mutex to destroy
 * @return void
 */
DIESEL_API void mutex_destroy(mutex_t* mutex);

#endif // LIB_DIESEL_THREADING_H
