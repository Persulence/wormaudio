package com.neep.neepsound2;

import java.lang.ref.ReferenceQueue;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedDeque;

public interface NativeResourceHandle
{
    ReferenceQueue<NativeResourceHandle> REF_QUEUE = new ReferenceQueue<>();
    Deque<NativeResource> REF_LIST = new ConcurrentLinkedDeque<>();

    interface NativeResource
    {
        void dispose();
    }

    static void cleanup()
    {
        try
        {
            NativeResource resource = (NativeResource) REF_QUEUE.remove();
            resource.dispose();
        }
        catch (InterruptedException e)
        {
            // oops
        }
    }
}
