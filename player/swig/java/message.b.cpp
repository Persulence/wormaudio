// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include <iostream>
#include <memory>

#include <jni.h>

#include "juce_events/juce_events.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_com_wormaudio_wormaudio_WormAudioContext_requestFlushAsync(JNIEnv* env, jobject thisObject)
    {
        auto global = env->NewGlobalRef(thisObject);

        JavaVM* jvm = nullptr;
        env->GetJavaVM(&jvm);

        juce::MessageManager::callAsync([env, global, jvm]
        {
            jvm->AttachCurrentThread((void**) &env, nullptr);

            // keEpinG THis arouND aS a heLpfuL ExAMPle
            // jclass cls = env->FindClass("java/lang/Class");
            // jmethodID mid_getName = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
            // jstring name1 = (jstring) env->CallObjectMethod(cls, mid_getName);
            // std::cout << env->GetStringChars(name1, nullptr) << "\n";

            // I am in blood stepped in so far
            const auto oc = env->GetObjectClass(global);
            const auto method = env->GetMethodID(oc, "flushAsyncCallbacks", "()V");
            env->CallVoidMethod(global, method);
            env->DeleteGlobalRef(global);
        });
    }
}
