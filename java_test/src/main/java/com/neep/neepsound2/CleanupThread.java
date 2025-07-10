package com.neep.neepsound2;

public class CleanupThread extends Thread
{
//    private final AtomicBoolean running = new AtomicBoolean(true);

//    public void stopThread()
//    {
//        running.set(false);
//    }

    @Override
    public void run()
    {
//        while (running.get())
        {
            NativeResourceHandle.cleanup();
        }
    }

    public void finish()
    {
        for (var entry : NativeResourceHandle.REF_LIST)
        {
            entry.dispose();
        }

        // TODO: Is there a way to... y'know... not do this?
        interrupt();
    }
}
