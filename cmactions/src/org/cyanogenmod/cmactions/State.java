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

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

import android.content.Context;
import android.util.Log;

public class State {
    private static final String TAG = "CMActions";
    private static final boolean SAVE_STATE = true;
    private static final int DELAY_BETWEEN_DOZES_IN_MS = 1500;

    private Context mContext;

    private boolean mScreenIsOn;
    private boolean mIsFlatUp;
    private boolean mIsStowed;
    private long mLastDoze;
    private long mLastDeniedDoze;

    public State(Context context) {
        mContext = context;
    }

    public boolean getIsStowed() {
        return mIsStowed;
    }

    public void setScreenIsOn(boolean screenIsOn) {
        mScreenIsOn = screenIsOn;
        Log.d(TAG, "Screen is " + (screenIsOn ? "ON" : "OFF"));
        saveStateIfEnabled();
    }

    public boolean setIsFlatUp(boolean isFlatUp) {
        boolean lastIsFlatUp = mIsFlatUp;

        Log.d(TAG, "FlatUp is " + isFlatUp);
        mIsFlatUp = isFlatUp;
        saveStateIfEnabled();

        return lastIsFlatUp;
    }

    public boolean setIsStowed(boolean isStowed) {
        boolean lastIsStowed = mIsStowed;

        Log.d(TAG, "Stowed is " + (isStowed ? "STOWED" : "UNSTOWED"));
        mIsStowed = isStowed;
        saveStateIfEnabled();

        return lastIsStowed;
    }

    public synchronized boolean mayDoze() {
        long now = System.currentTimeMillis();
        if (now - mLastDoze > DELAY_BETWEEN_DOZES_IN_MS) {
            Log.d(TAG, "Allowing doze");
            mLastDoze = now;
            saveStateIfEnabled();
            return true;
        } else {
            Log.d(TAG, "Denying doze");
            mLastDeniedDoze = now;
            return false;
        }
    }

    private void saveStateIfEnabled() {
        if (SAVE_STATE) {
            saveState();
        }
    }

    private synchronized void saveState() {
        try {
            FileOutputStream out = mContext.openFileOutput("state.txt",
                Context.MODE_WORLD_READABLE);
            OutputStreamWriter writer = new OutputStreamWriter(out);

            writer.write("screenIsOn:     " + mScreenIsOn + "\n");
            writer.write("isFlatUp:       " + mIsFlatUp + "\n");
            writer.write("isStowed:       " + mIsStowed + "\n");
            writer.write("lastDoze:       " + mLastDoze + "\n");
            writer.write("lastDeniedDoze: " + mLastDeniedDoze + "\n");
            writer.write("now:            " + System.currentTimeMillis() + "\n");

            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
