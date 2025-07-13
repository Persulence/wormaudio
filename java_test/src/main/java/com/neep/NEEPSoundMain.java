package com.neep;

import com.neep.neepsound.NEEPSoundContext;
import com.neep.neepsound.generated.*;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;

public class NEEPSoundMain
{
    private static NRuntime runtime;

    // TODO: put this in a class that will definitely be loaded when the library is used
    static
    {
        try
        {
            String os = System.getProperty("os.name").toLowerCase();
            String arch = System.getProperty("os.arch").toLowerCase();

            String[] libraries = {"neepsound", "neepsound-java"};

            for (String name : libraries)
            {
                String path = "/native/%s_%s_%s.slib".formatted(name, os, arch);

                URL resource = NEEPSoundMain.class.getResource(path);

                if (resource == null)
                    throw new UnsatisfiedLinkError("NEEPSound: Native support for system %s %s (%s) not found".formatted(os, arch, path));

                // Unpack the resource to a temporary file so that the system can load it
                File file = File.createTempFile("lib", ".slib");
                try (OutputStream output = new FileOutputStream(file))
                {
                    Files.copy(Path.of(resource.getPath()), output);
                }

                System.out.printf("NEEPSound: Unpacking library for %s %s (%s) %n", os, arch, path);

                System.load(file.getAbsolutePath());
            }
        }
        catch (UnsatisfiedLinkError | IOException e)
        {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }

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