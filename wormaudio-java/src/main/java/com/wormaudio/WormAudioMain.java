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