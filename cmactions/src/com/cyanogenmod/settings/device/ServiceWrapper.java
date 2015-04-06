/*
 * Copyright (c) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.cyanogenmod.settings.device;

import android.content.Intent;
import android.os.Binder;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

public class ServiceWrapper extends android.app.Service {
    static final String TAG = "CMActions-ServiceWrapper";

    private final IBinder mBinder = new LocalBinder();
    private CMActionsService mCmActionsService;

    public interface ServiceCallback {
        void sendResults(int resultCode, Bundle b);
    }

    public class LocalBinder extends Binder {
        ServiceWrapper getService() {
            // Return this instance of the service so clients can call public
            // methods
            return ServiceWrapper.this;
        }
    }

    @Override
    public void onCreate() {
        Log.i(TAG, "onCreate");
        super.onCreate();
        mCmActionsService = new CMActionsService(this);
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.i(TAG, "onBind");
        return null;
    }

    public void setCallback(ServiceCallback callback) {
    }

    public void start() {
        Log.i(TAG, "start");
    }

    public void stop() {
    }
}
