/*
 * Copyright (C) 2005 The Android Open Source Project
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

#ifndef ANDROID_HARDWARE_BINDER_DEBUG_H
#define ANDROID_HARDWARE_BINDER_DEBUG_H

#include <stdint.h>
#include <sys/types.h>

#include <hwbinder/libhidl_export.h>

// WARNING: this code is part of libhwbinder, a fork of libbinder. Generally,
// this means that it is only relevant to HIDL. Any AIDL- or libbinder-specific
// code should not try to use these things.

#ifndef ssize_t
#define ssize_t int64_t
#endif

namespace android {
namespace hardware {
// ---------------------------------------------------------------------------

extern "C" {

LIBHIDL_EXPORT const char* stringForIndent(int32_t indentLevel);

typedef void (*debugPrintFunc)(void* cookie, const char* txt);

LIBHIDL_EXPORT void printTypeCode(uint32_t typeCode,
    debugPrintFunc func = nullptr, void* cookie = nullptr);

LIBHIDL_EXPORT void printHexData(int32_t indent, const void *buf, size_t length,
    size_t bytesPerLine=16, int32_t singleLineBytesCutoff=16,
    size_t alignment=0, bool cArrayStyle=false,
    debugPrintFunc func = nullptr, void* cookie = nullptr);

LIBHIDL_EXPORT ssize_t getHWBinderKernelReferences(size_t count, uintptr_t* buf);

}

// ---------------------------------------------------------------------------
} // namespace hardware
} // namespace android

#endif // ANDROID_HARDWARE_BINDER_DEBUG_H
