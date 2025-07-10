package com.neep;

import com.neep.neepsound.NEventDef;
import com.neep.neepsound.NSystem;
import com.neep.neepsound2.CleanupThread;
import com.neep.neepsound2.NoClass;

public class Main
{
    public static NoClass nc;

    public static void main(String[] args)
    {
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

        NSystem system = new NSystem();
        NEventDef def = system.getEventDef("ooer");

//        SoundThing st = new SoundThing();
//        st.setField(123);
//        st.memberFunction();

        System.out.flush();
        cleanupThread.finish();
    }
}