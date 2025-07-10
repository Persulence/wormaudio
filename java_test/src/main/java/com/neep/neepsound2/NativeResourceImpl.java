package com.neep.neepsound2;

import java.lang.ref.WeakReference;

public abstract class NativeResourceImpl extends WeakReference<NativeResourceHandle> implements NativeResourceHandle.NativeResource
{
    protected long cPtr;

    public NativeResourceImpl(NativeResourceHandle referent, long cPtr)
    {
        super(referent, NativeResourceHandle.REF_QUEUE);
        this.cPtr = cPtr;

        NativeResourceHandle.REF_LIST.add(this);
    }

    @Override
    public void dispose()
    {
        NativeResourceHandle.REF_LIST.remove(this);

        if (cPtr != 0)
            disposeInternal(cPtr);

        cPtr = 0;
    }

    protected abstract void disposeInternal(long cPtr);
}
