package com.neep.neepsound2;

import com.neep.Main;
import com.neep.neepsound.NEEPSoundJNI;

public class NoClass implements NativeResourceHandle
{
    private final NoClassImpl impl;

    public NoClass()
    {
        this.impl = new NoClassImpl(this);
    }

    public void thing()
    {
//        NEEPSound.NoClass_thing(SWIGTYPE_p_NoClass
//        NEEPSoundJNI.NoClass_thing(impl.cPtr);
    }

    public void testGC()
    {
        Main.nc = null;
        System.gc();
    }

    private static class NoClassImpl extends NativeResourceImpl
    {
        public NoClassImpl(NoClass noClass)
        {
//            super(noClass, NEEPSoundJNI.new_NoClass());
            super(noClass, 0);
        }

        @Override
        protected void disposeInternal(long cPtr)
        {
//            NEEPSoundJNI.delete_NoClass(cPtr);
        }
    }
}
