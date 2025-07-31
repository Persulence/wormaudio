/*
 * Copyright (c)  2025 Thomas Paley-Menzies
 *
 * This file is part of the WormAudio project.
 *
 * WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
 *
 */

package com.wormaudio.wormaudio;

import com.wormaudio.WormAudioMain;
import com.wormaudio.wormaudio.generated.LoggerAdaptor;
import com.wormaudio.wormaudio.generated.MessageThreadManager;
import com.wormaudio.wormaudio.generated.WARuntime;
import com.wormaudio.wormaudio.generated.WormAudioInternal;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayDeque;
import java.util.Queue;

public class WormAudioContext extends MessageThreadManager
{
    public static Logger LOGGER = LoggerFactory.getLogger("WormAudio");

    public static @NotNull File extractResourceToTempFile(String path) throws IOException
    {
        URL resource = WormAudioMain.class.getResource(path);

        if (resource == null)
            throw new IOException("JAR resource %s not found".formatted(path));

        File file = File.createTempFile("lib", ".slib");
        file.deleteOnExit();
        try (OutputStream output = new FileOutputStream(file))
        {
            Files.copy(Path.of(resource.getPath()), output);
        }
        return file;
    }

    static
    {
        try
        {
            String os = System.getProperty("os.name").toLowerCase();
            String arch = System.getProperty("os.arch").toLowerCase();

//            String[] libraries = {"wormaudio", "wormaudio-java"};
            String[] libraries = {"wormaudio-java"};

            for (String name : libraries)
            {
                String path = "/native/%s_%s_%s.slib".formatted(name, os, arch);

                File file = extractResourceToTempFile(path);

                LOGGER.info("Unpacking native library for {} {} ({})", os, arch, path);

                System.load(file.getAbsolutePath());
            }
        }
        catch (UnsatisfiedLinkError | IOException e)
        {
            LOGGER.error("WormAudio: Native library faile to load}\n", e);
            System.exit(1);
        }
    }

    private static WormAudioContext INSTANCE = new WormAudioContext();

    private final LoggerAdaptor loggerAdaptor = new Slf4jLoggerAdaptor(LOGGER);
    @Nullable private WARuntime runtime;

    Thread messageThread = new Thread(MessageThreadManager::claimMessageThread, "JUCE Message Thread");

    private final Queue<Runnable> asyncQueue = new ArrayDeque<>();

    public static void deleteInstance()
    {
//        INSTANCE.loggerAdaptor.delete();
        INSTANCE.delete();
        INSTANCE = null; // A NullPointerException will be thrown instead of a segfault
    }
    private native void requestFlushAsync();

    public static native void nativeThing();

    public static WormAudioContext getInstance()
    {
        return INSTANCE;
    }

    private WormAudioContext()
    {
        WormAudioInternal.setLogger(loggerAdaptor);
    }

    @SuppressWarnings("unused")
    public void flushAsyncCallbacks()
    {
        synchronized (asyncQueue)
        {
            try
            {
                for (var callback : asyncQueue)
                {
                    callback.run();
                }
            }
            catch (Exception e)
            {
                LOGGER.error("Uncaught exception in message thread", e);
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

    public WARuntime getRuntime()
    {
        if (!messageThread.isAlive())
        {
            throw new IllegalStateException("Attempted to get WormAudio runtime while message thread is down.");
        }

        return runtime;
    }

    public void startMessageThread()
    {
        messageThread.start();

        callAsync(() -> runtime = new WARuntime());
    }

    public void stopMessageThread()
    {
        if (runtime != null)
        {
            runtime.disconnect();
            runtime.delete();
            runtime = null;
        }

        MessageThreadManager.requestMessageThreadStop();
    }

    public void join() throws InterruptedException
    {
        messageThread.join();
    }

    @Override
    public synchronized void delete()
    {
        super.delete();
        loggerAdaptor.delete();
    }

    public static class Slf4jLoggerAdaptor extends LoggerAdaptor
    {
        private final Logger logger;

        public Slf4jLoggerAdaptor(Logger logger)
        {
            this.logger = logger;
        }

        @Override
        public void logMessage(String message)
        {
            logger.info(message);
        }
    }
}
