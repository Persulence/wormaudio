// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include <iostream>
#include <memory>

#include <jni.h>

#include "juce_events/juce_events.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_com_wormaudio_wormaudio_WormAudioContext_nativeThing(JNIEnv* env, jobject thisObject)
    {
        std::cout << "eeeeeeeeeeee\n";

    }


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
