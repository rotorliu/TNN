// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef TNN_ARM_UTIL_H_
#define TNN_ARM_UTIL_H_

#include <string.h>
#include <cstdlib>
#include <sys/time.h>

#include "tnn/core/blob.h"
#include "tnn/core/macro.h"
#include "tnn/utils/bfp16.h"

namespace TNN_NS {
#if TNN_PROFILE
struct Timer {
public:
    void Start() {
        gettimeofday(&start, NULL);
    }
    float TimeEclapsed() {
        struct timeval end;
        gettimeofday(&end, NULL);
        float delta = (end.tv_sec - start.tv_sec) * 1000.f + (end.tv_usec - start.tv_usec) / 1000.f;
        gettimeofday(&start, NULL);
        return delta;
    }
private:
    struct timeval start;
};
#endif

char* GetBlobHandlePtr(BlobHandle handle);

template <typename Tin, typename Tout>
int PackC4(Tout *dst, const Tin *src, size_t hw, size_t channel);

int PackCAndQuant(int8_t *dst, const float *src, size_t hw, size_t channel, float *scale);

template <typename Tin, typename Tout>
int UnpackC4(Tout *dst, const Tin *src, size_t hw, size_t channel);

int UnpackC4WithStride(float *dst, const float *src, size_t ih, size_t iw, size_t c_step, size_t w_step, size_t depth);

int UnpackAndDequant(float *dst, const int8_t *src, size_t hw, size_t channel, float *scale);

template <typename T>
int ConvertWeightsC4ToC8(T *weight, int ic, int oc);

template <typename T>
int ConvertWeightsFromGOIHWToGOIHW16(T *src, T *dst, int group, int input_channel, int output_channel, int height,
                                     int width);

template <typename T>
int ConvertWeightsFromGIOHWToGOHWI16(T *src, T *dst, int group, int input_channel, int output_channel, int height,
                                     int width);

template <typename T>
int ConvertWeightsFromOI3HWToOHW12(T *src, T *dst, int input_channel, int output_channel, int height, int width);

int PackINT8Weight(int8_t *src, int8_t *dst, int group, int input_channel, int output_channel, int height, int width);
}  // namespace TNN_NS

#endif