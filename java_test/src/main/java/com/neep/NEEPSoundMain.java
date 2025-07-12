package com.neep;

import com.neep.neepsound.*;
import com.neep.neepsound2.NEEPSoundContext;

import java.io.IOException;

public class NEEPSoundMain
{
    private static NRuntime runtime;

    public static void main(String[] args) throws InterruptedException
    {
        NEEPSound.sanityCheck();
        Runtime.getRuntime().addShutdownHook(new Thread(() ->
        {
            System.gc();
            System.runFinalization();
        }));

        System.out.println("ullo my luv");

        NEEPSoundContext context = new NEEPSoundContext();
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
            runtime.delete();
            runtime = null;
        });
        context.callAsync(() ->
        {
            System.out.println("Before requesting stop");
            context.stopMessageThread();
        });

        String path = "test_system/test_system.proj";
        try
        {
            NSystem system = NSystem.load(path);
            NEventDef def = system.getEventDef("music");
            if (def != null)
            {
                System.out.println("Found event");
//                EventInstance instance = runtime.instantiate(def);
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

//        runtime.disconnect();


//        SoundThing st = new SoundThing();
//        st.setField(123);
//        st.memberFunction();

        System.out.flush();
        context.join();
    }
}