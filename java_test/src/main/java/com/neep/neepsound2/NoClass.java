package com.neep.neepsound2;

import com.neep.neepsound.NEEPSoundJNI;

import java.lang.ref.WeakReference;

public class NoClass implements NativeResource
{
    private final NativeNoClass impl;

    public NoClass()
    {
        this.impl = new NativeNoClass(this);
    }

    @Override
    public void dispose()
    {

    }

    private static class NativeNoClass extends WeakReference<NoClass> implements NativeResourceImpl
    {
        private final long cPtr;

        public NativeNoClass(NoClass noClass)
        {
            super(noClass, REF_QUEUE);
            REF_LIST.add(this);

            cPtr = NEEPSoundJNI.new_NoClass();
        }

        public void dispose()
        {
            NEEPSoundJNI.delete_NoClass(cPtr);
        }
    }
}
