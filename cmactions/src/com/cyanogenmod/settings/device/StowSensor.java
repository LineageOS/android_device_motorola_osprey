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

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.util.Log;

public class StowSensor implements ActionableSensor, SensorEventListener {
    private static final String TAG = "CMActions-StowSensor";

    private CMActionsSettings mCMActionsSettings;
    private SensorHelper mSensorHelper;
    private State mState;
    private SensorAction mSensorAction;

    private Sensor mSensor;
    private boolean mEnabled;

    public StowSensor(CMActionsSettings cmActionsSettings, SensorHelper sensorHelper, State state,
                SensorAction action) {
        mCMActionsSettings = cmActionsSettings;
        mSensorHelper = sensorHelper;
        mState = state;
        mSensorAction = action;

        mSensor = sensorHelper.getStowSensor();
    }

    @Override
    public void setScreenOn() {
        if (mEnabled) {
            Log.d(TAG, "Disabling");
            mSensorHelper.unregisterListener(this);
            mEnabled = false;
        }
    }

    @Override
    public void setScreenOff() {
        if (mCMActionsSettings.isPickUpEnabled() && !mEnabled) {
            Log.d(TAG, "Enabling");
            mSensorHelper.registerListener(mSensor, this);
            mEnabled = true;
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        boolean thisStowed = (event.values[0] != 0);
        Log.d(TAG, "event: " + thisStowed);
        if (mState.setIsStowed(thisStowed) && ! thisStowed) {
            mSensorAction.action();
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }
}
