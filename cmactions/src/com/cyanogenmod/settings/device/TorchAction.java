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

import android.content.Context;
import android.hardware.TorchManager;
import android.os.Vibrator;
import android.util.Log;

public class TorchAction implements SensorAction {
    private static final String TAG = "CMActions";

    private static final int TURN_SCREEN_ON_WAKE_LOCK_MS = 500;

    private final TorchManager mTorchManager;
    private final Vibrator mVibrator;

    public TorchAction(Context context) {
        mTorchManager = (TorchManager) context.getSystemService(Context.TORCH_SERVICE);
        mVibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
    }

    @Override
    public void action() {
        mVibrator.vibrate(250);
        mTorchManager.toggleTorch();
    }
}
