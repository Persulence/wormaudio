package com.wormaudio;

import com.wormaudio.wormaudio.WormAudioContext;
import com.wormaudio.wormaudio.generated.*;

import java.io.IOException;

public class WormAudioMain
{
    public static void main(String[] args) throws InterruptedException
    {
        WormAudioContext context = WormAudioContext.getInstance();

        Runtime.getRuntime().addShutdownHook(new Thread(() ->
        {
            WormAudioContext.deleteInstance();
            System.gc();
            System.runFinalization();
        }));

        context.startMessageThread();

        context.callAsync(() -> System.out.println("This was called on the message thread!"));

        context.callAsync(() -> WormAudioContext.getInstance().getRuntime().connectToDevice());

        context.callAsync(() ->
        {
            String path = "test_system/test_system.proj";
            try
            {
                WASystem system = WASystem.load(path);
                WASoundDef def = system.getEventDef("music");
                if (def != null)
                {
                    System.out.println("Found event");
                    WASoundInstance instance = context.getRuntime().instantiate(def);
                    context.getRuntime().setState(TransportState.PLAYING);
                    instance.getTransport().setState(TransportState.STARTING);
                    WormAudioInternal.setInstancePos(instance, 0, 0, 0);
                    instance.getTransport().setState(TransportState.STOPPING);
                    instance.markDone();
                }
                else
                {
                    System.out.println("Did not find event");
                }
            }
            catch (IOException e)
            {
                System.err.printf("Failed to load system %s:\n", path);
                e.printStackTrace(System.err);
            }
        });


        try
        {
            System.out.println("Press ENTER to stop");
            System.in.read();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }

        context.stopMessageThread();
        context.join();
    }
}