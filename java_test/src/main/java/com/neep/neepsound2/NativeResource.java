package com.neep.neepsound2;

import java.lang.ref.ReferenceQueue;
import java.util.ArrayList;
import java.util.List;

public interface NativeResource
{
    ReferenceQueue<NativeResource> REF_QUEUE = new ReferenceQueue<>();
    List<NativeResourceImpl> REF_LIST = new ArrayList<>();

    void dispose();

    interface NativeResourceImpl
    {

    }

    static void cleanupLoop()
    {
        while (true)
        {
//            NativeResource resource = REF_QUEUE.remove();
        }
    }
}
