package com.neep;

import com.neep.neepsound.*;
import com.neep.neepsound2.NEEPSoundContext;

import java.io.IOException;

public class NEEPSoundMain
{
    private static NRuntime runtime;

    public static void main(String[] args) throws InterruptedException
    {
        NEEPSoundContext context = NEEPSoundContext.getInstance();

        NEEPSound.sanityCheck();
        Runtime.getRuntime().addShutdownHook(new Thread(() ->
        {
            NEEPSoundContext.deleteInstance();
            System.gc();
            System.runFinalization();
        }));

        context.startMessageThread();

        context.callAsync(() -> System.out.println("This was called on the message thread!"));
        context.callAsync(() ->
        {
            System.out.println("Before instantiating NRuntime");
            runtime = new NRuntime();
            runtime.connectToDevice();
        });

        context.callAsync(() ->
        {
            String path = "test_system/test_system.proj";
            try
            {
                NSystem system = NSystem.load(path);
                NEventDef def = system.getEventDef("music");
                if (def != null)
                {
                    System.out.println("Found event");
                    EventInstance instance = runtime.instantiate(def);
                    runtime.setState(TransportState.PLAYING);
                    instance.setState(TransportState.STARTING);
                    NEEPSound.setInstancePos(instance, 0, 0, 0);
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
        runtime.disconnect();
        runtime.delete();

        context.stopMessageThread();
        context.join();
    }
}