package com.neep;

import com.neep.neepsound.*;
import com.neep.neepsound2.CleanupThread;
import com.neep.neepsound2.NoClass;

import java.io.IOException;

public class Main
{
    public static NoClass nc;

    public static void main(String[] args)
    {
        NEEPSound.sanityCheck();
        Runtime.getRuntime().addShutdownHook(new Thread(() ->
        {
            System.gc();
            System.runFinalization();
        }));

        CleanupThread cleanupThread = new CleanupThread();
        cleanupThread.start();

        System.out.println("ullo my luv");
//        nc = new NoClass();
//        nc.thing();
//        nc = null;
//        NEEPSound.freeFunction();
//        System.gc();

        NRuntime runtime = new NRuntime();
        runtime.connectToDevice();

        String path = "test_system/test_system.proj";
        try
        {
            NSystem system = NSystem.load(path);
            NEventDef def = system.getEventDef("music");
            if (def != null)
            {
                System.out.println("Found event");
                EventInstance instance = runtime.instantiate(def);
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

        runtime.disconnect();


//        SoundThing st = new SoundThing();
//        st.setField(123);
//        st.memberFunction();

        System.out.flush();
        cleanupThread.finish();
    }
}