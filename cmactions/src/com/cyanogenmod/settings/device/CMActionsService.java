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

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.os.PowerManager;
import android.provider.Settings;
import android.util.Log;

import java.util.List;
import java.util.LinkedList;

public class CMActionsService extends IntentService implements ScreenStateNotifier,
        UpdatedStateNotifier {
    private static final String TAG = "CMActions";

    private final Context mContext;

    private final CameraActivationAction mCameraActivationAction;
    private final DozePulseAction mDozePulseAction;
    private final PowerManager mPowerManager;
    private final ScreenReceiver mScreenReceiver;
    private final SensorHelper mSensorHelper;
    private final State mState;

    private final List<ActionableSensor> mActionableSensors = new LinkedList<ActionableSensor>();

    public CMActionsService(Context context) {
        super("CMActionService");
        mContext = context;

        Log.d(TAG, "Starting");

        mState = new State(context);
        CMActionsSettings cmActionsSettings = new CMActionsSettings(context, this);
        mSensorHelper = new SensorHelper(context);
        mScreenReceiver = new ScreenReceiver(context, this);

        mCameraActivationAction = new CameraActivationAction(context);
        mDozePulseAction = new DozePulseAction(context, mState);

        mActionableSensors.add(new CameraActivationSensor(cmActionsSettings, mSensorHelper, mCameraActivationAction));
        mActionableSensors.add(new FlatUpSensor(cmActionsSettings, mSensorHelper, mState, mDozePulseAction));
        // mActionableSensors.add(new IrGestureSensor(cmActionsSettings, mSensorHelper, mDozePulseAction, mIrGestureManager));
        mActionableSensors.add(new StowSensor(cmActionsSettings, mSensorHelper, mState, mDozePulseAction));

        mPowerManager = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
        updateState();
    }

    @Override
    protected void onHandleIntent(Intent intent) {
    }

    @Override
    public void screenTurnedOn() {
        mState.setScreenIsOn(true);
        for (ActionableSensor actionableSensor : mActionableSensors) {
            actionableSensor.setScreenOn();
        }
    }

    @Override
    public void screenTurnedOff() {
        mState.setScreenIsOn(false);
        for (ActionableSensor actionableSensor : mActionableSensors) {
            actionableSensor.setScreenOff();
        }
    }

    public void updateState() {
        if (mPowerManager.isInteractive()) {
            screenTurnedOn();
        } else {
            screenTurnedOff();
        }
    }
}
