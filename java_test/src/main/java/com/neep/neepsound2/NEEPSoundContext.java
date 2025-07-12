package com.neep.neepsound2;

import com.neep.neepsound.MessageThreadManager;

import java.util.ArrayDeque;
import java.util.Queue;

public class NEEPSoundContext extends MessageThreadManager
{
    Thread messageThread = new Thread(MessageThreadManager::claimMessageThread);

    private final Queue<Runnable> asyncQueue = new ArrayDeque<>();

    private native void requestFlushAsync();

    public NEEPSoundContext()
    {
    }

    @SuppressWarnings("unused")
    public void flushAsyncCallbacks()
    {
        synchronized (asyncQueue)
        {
            for (var callback : asyncQueue)
            {
                callback.run();
            }

            asyncQueue.clear();
        }
    }

    public void callAsync(Runnable callback)
    {
        synchronized (asyncQueue)
        {
            asyncQueue.add(callback);
            requestFlushAsync();
        }
    }

    public void startMessageThread()
    {
        messageThread.start();
    }

    public void stopMessageThread()
    {
        MessageThreadManager.requestMessageThreadStop();
    }

    public void join() throws InterruptedException
    {
        messageThread.join();
    }
}
