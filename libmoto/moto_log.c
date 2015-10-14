/*
 * Copyright (C) 2015 The CyanogenMod Project
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

#include <string.h>
#include <android/log.h>
#include <sys/system_properties.h>

/* Fallback when there is neither log.tag.<tag> nor log.tag.DEFAULT.
 * this is compile-time defaulted to "info". The log startup code
 * looks at the build tags to see about whether it should be DEBUG...
 * -- just as is done in frameworks/base/core/jni/android_util_Log.cpp
 */
static int prio_fallback = ANDROID_LOG_INFO;

/*
 * public interface so native code can see "should i log this"
 * and behave similar to java Log.isLoggable() calls.
 *
 * NB: we have (level,tag) here to match the other __android_log entries.
 * The Java side uses (tag,level) for its ordering.
 * since the args are (int,char*) vs (char*,char*) we won't get strange
 * swapped-the-strings errors.
 */

#define	LOGGING_PREFIX	"log.tag."
#define	LOGGING_DEFAULT	"log.tag.DEFAULT"

int __android_log_loggable(int prio, const char *tag)
{
    int nprio;
    char keybuf[PROP_NAME_MAX];
    char results[PROP_VALUE_MAX];
    int n;

    /* we can NOT cache the log.tag.<tag> and log.tag.DEFAULT
     * values because either one can be changed dynamically.
     *
     * damn, says the performance compulsive.
     */

    n = 0;
    results[0] = '\0';
    if (tag) {
        memcpy (keybuf, LOGGING_PREFIX, strlen (LOGGING_PREFIX) + 1);
        /* watch out for buffer overflow */
        strncpy (keybuf + strlen (LOGGING_PREFIX), tag,
                sizeof (keybuf) - strlen (LOGGING_PREFIX));
        keybuf[sizeof (keybuf) - 1] = '\0';
        n = __system_property_get (keybuf, results);
    }
    if (n == 0) {
        /* nothing yet, look for the global */
        memcpy (keybuf, LOGGING_DEFAULT, sizeof (LOGGING_DEFAULT));
        n = __system_property_get (keybuf, results);
    }

    if (n == 0) {
        nprio = prio_fallback;
    } else {
        switch (results[0]) {
            case 'E':
                nprio = ANDROID_LOG_ERROR;
                break;
            case 'W':
                nprio = ANDROID_LOG_WARN;
                break;
            case 'I':
                nprio = ANDROID_LOG_INFO;
                break;
            case 'D':
                nprio = ANDROID_LOG_DEBUG;
                break;
            case 'V':
                nprio = ANDROID_LOG_VERBOSE;
                break;
            case 'S':
                nprio = ANDROID_LOG_SILENT;
                break;
            default:
                /* unspecified or invalid */
                nprio = prio_fallback;
                break;
        }
    }

    return ((prio >= nprio) ? 1 : 0);
}
