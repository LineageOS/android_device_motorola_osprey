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

import java.util.List;

import android.app.KeyguardManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.os.Vibrator;
import android.provider.MediaStore;
import android.util.Log;

public class CameraActivationAction implements SensorAction {
    private static final String TAG = "CMActions";

    private static final int TURN_SCREEN_ON_WAKE_LOCK_MS = 500;

    private final Context mContext;
    private final KeyguardManager mKeyguardManager;
    private final PackageManager mPackageManager;
    private final PowerManager mPowerManager;

    public CameraActivationAction(Context context) {
        mContext = context;
        mKeyguardManager = (KeyguardManager) context.getSystemService(Context.KEYGUARD_SERVICE);
        mPowerManager = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
        mPackageManager = context.getPackageManager();
    }

    @Override
    public void action() {
        vibrate();
        turnScreenOn();
        if (mKeyguardManager.inKeyguardRestrictedInputMode()) {
            launchSecureCamera();
        } else {
            launchCamera();
        }
    }

    private void vibrate() {
        Vibrator v = (Vibrator) mContext.getSystemService(Context.VIBRATOR_SERVICE);
        v.vibrate(500);
    }

    private void turnScreenOn() {
        PowerManager.WakeLock wl = mPowerManager.newWakeLock(
            PowerManager.SCREEN_BRIGHT_WAKE_LOCK | PowerManager.ACQUIRE_CAUSES_WAKEUP, TAG);
        wl.acquire(TURN_SCREEN_ON_WAKE_LOCK_MS);
    }

    private void launchCamera() {
        Intent intent = createIntent(MediaStore.INTENT_ACTION_STILL_IMAGE_CAMERA);
        if (getBestActivityInfo(intent) != null) {
            // Only launch if we can succeed, but let the user pick the action
            mContext.startActivity(intent);
        }
    }

    private void launchSecureCamera() {
        // Keyguard won't allow a picker, try to pick the secure intent in the package
        // that would be the one used for a default action of launching the camera
        Intent normalIntent = createIntent(MediaStore.INTENT_ACTION_STILL_IMAGE_CAMERA);
        Intent secureIntent = createIntent(MediaStore.INTENT_ACTION_STILL_IMAGE_CAMERA_SECURE);
        ActivityInfo normalActivity = getBestActivityInfo(normalIntent);
        ActivityInfo secureActivity = getBestActivityInfo(secureIntent, normalActivity);
        if (secureActivity != null) {
            secureIntent.setComponent(componentName(secureActivity));
            mContext.startActivity(secureIntent);
        }
    }

    private Intent createIntent(String intentName) {
        Intent intent = new Intent(intentName);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.addFlags(Intent.FLAG_FROM_BACKGROUND);
        return intent;
    }

    private ActivityInfo getBestActivityInfo(Intent intent) {
        ResolveInfo resolveInfo = mPackageManager.resolveActivity(intent, 0);
        if (resolveInfo != null) {
            return resolveInfo.activityInfo;
        } else {
            // If the resolving failed, just find our own best match
            return getBestActivityInfo(intent, null);
        }
    }

    private ActivityInfo getBestActivityInfo(Intent intent, ActivityInfo match) {
        List <ResolveInfo> activities = mPackageManager.queryIntentActivities(intent, 0);
        ActivityInfo best = null;
        if (activities.size() > 0) {
            best = activities.get(0).activityInfo;
            if (match != null) {
                String packageName = match.applicationInfo.packageName;
                for (int i = activities.size()-1; i >= 0; i--) {
                    ActivityInfo activityInfo = activities.get(i).activityInfo;
                    if (packageName.equals(activityInfo.applicationInfo.packageName)) {
                        best = activityInfo;
                    }
                }
            }
        }
        return best;
    }

    private ComponentName componentName(ActivityInfo activity) {
        return new ComponentName(activity.applicationInfo.packageName, activity.name);
    }
}
