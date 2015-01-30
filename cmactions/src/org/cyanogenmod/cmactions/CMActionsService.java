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

package org.cyanogenmod.cmactions;

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.os.PowerManager;
import android.provider.Settings;
import android.util.Log;

public class CMActionsService extends IntentService implements ScreenStateNotifier {
    private static final String TAG = "CMActions";

    private State mState;
    private SensorHelper mSensorHelper;
    private ScreenReceiver mScreenReceiver;

    private CameraActivationAction mCameraActivationAction;
    private DozePulseAction mDozePulseAction;

    private ActionableSensor mCameraActivationSensor;
    private ActionableSensor mFlatUpSensor;
    private ActionableSensor mIrGestureSensor;
    private ActionableSensor mStowSensor;

    private Context mContext;

    public CMActionsService(Context context) {
        super("CMActionService");
        mContext = context;

        Log.d(TAG, "Starting");

        mState = new State(context);
        mSensorHelper = new SensorHelper(context);
        mScreenReceiver = new ScreenReceiver(context, this);

        mCameraActivationAction = new CameraActivationAction(context);
        mDozePulseAction = new DozePulseAction(context, mState);

        mCameraActivationSensor = new CameraActivationSensor(mSensorHelper, mCameraActivationAction);
        mFlatUpSensor = new FlatUpSensor(mSensorHelper, mState, mDozePulseAction);
        mIrGestureSensor = new IrGestureSensor(mSensorHelper, mDozePulseAction);
        mStowSensor = new StowSensor(mSensorHelper, mState, mDozePulseAction);

        mCameraActivationSensor.enable();

        PowerManager powerManager = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
        if (powerManager.isInteractive()) {
            screenTurnedOn();
        } else {
            screenTurnedOff();
        }
    }

    @Override
    protected void onHandleIntent(Intent intent) {
    }

    @Override
    public void screenTurnedOn() {
        mState.setScreenIsOn(true);
        //mIrGestureSensor.disable();
        mFlatUpSensor.disable();
        mStowSensor.disable();
    }

    @Override
    public void screenTurnedOff() {
        mState.setScreenIsOn(false);
        if (isDozeEnabled()) {
            //mIrGestureSensor.enable();
            mFlatUpSensor.enable();
            mStowSensor.enable();
        }
    }

    private boolean isDozeEnabled() {
        return Settings.Secure.getInt(mContext.getContentResolver(),
            Settings.Secure.DOZE_ENABLED, 1) != 0;
    }
}
