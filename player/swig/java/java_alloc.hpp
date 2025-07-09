#pragma once

#include <stdexcept>
#include "jni.h"

/**
 *  A stash area embedded in each allocation to hold java handles
 */
struct Jalloc
{
    jbyteArray jba;
    jobject ref;
};

static JavaVM *cached_jvm = nullptr;

inline JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    cached_jvm = jvm;
    return JNI_VERSION_1_2;
}

static JNIEnv *JNU_GetEnv()
{
    JNIEnv *env;
    jint rc = cached_jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_2);

    if (rc == JNI_EDETACHED)
        throw std::runtime_error("current thread not attached");

    if (rc == JNI_EVERSION)
        throw std::runtime_error("jni version not supported");
    return env;
}

inline void *operator new(size_t t)
{
    if (t == 0)
        t++;

    std::cout << "Operator new\n";

    if (cached_jvm != nullptr)
    {
        JNIEnv *env = JNU_GetEnv();
        jbyteArray jba = env->NewByteArray(static_cast<int>(t) + sizeof(Jalloc));

        if (env->ExceptionOccurred())
            throw std::bad_alloc();

        void *jbuffer = env->GetByteArrayElements(jba, nullptr);

        if (env->ExceptionOccurred())
            throw std::bad_alloc();

        auto *pJalloc = static_cast<Jalloc *>(jbuffer);
        pJalloc->jba = jba;
        /* Assign a global reference so byte array will persist until delete'ed */
        pJalloc->ref = env->NewGlobalRef(jba);

        if (env->ExceptionOccurred())
            throw std::bad_alloc();

        return static_cast<char *>(jbuffer) + sizeof(Jalloc);
    }
    else
    {
        /* JNI_OnLoad not called, use malloc and mark as special */
        auto *pJalloc = static_cast<Jalloc*>(malloc(static_cast<int>(t) + sizeof(Jalloc)));

        if (!pJalloc)
            throw std::bad_alloc();

        pJalloc->ref = nullptr;

        return static_cast<char *>(static_cast<void *>(pJalloc)) + sizeof(Jalloc);
    }
}

inline void operator delete(void *v)
{
    std::cout << "Operator delete\n";

    if (v != nullptr)
    {
        void *buffer = static_cast<char*>(v) - sizeof(Jalloc);
        auto *pJalloc = static_cast<Jalloc *>(buffer);
        if (pJalloc->ref)
        {
            JNIEnv *env = JNU_GetEnv();
            env->DeleteGlobalRef(pJalloc->ref);
            env->ReleaseByteArrayElements(pJalloc->jba, static_cast<jbyte*>(buffer), 0);
        }
        else
        {
            free(buffer);
        }
    }
}