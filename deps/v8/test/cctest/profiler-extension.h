// Copyright 2013 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef V8_TEST_CCTEST_PROFILER_EXTENSION_H_
#define V8_TEST_CCTEST_PROFILER_EXTENSION_H_

// Tests of profiles generator and utilities.

#include "include/v8-extension.h"
#include "include/v8-profiler.h"

namespace v8 {

template <typename T>
class FunctionCallbackInfo;

namespace internal {

class CpuProfiler;

class ProfilerExtension : public v8::Extension {
 public:
  ProfilerExtension() : v8::Extension("v8/profiler", kSource) { }

  v8::Local<v8::FunctionTemplate> GetNativeFunctionTemplate(
      v8::Isolate* isolate, v8::Local<v8::String> name) override;

  static void set_profiler(v8::CpuProfiler* profiler) { profiler_ = profiler; }
  static void set_profiler(CpuProfiler* profiler) {
    profiler_ = reinterpret_cast<v8::CpuProfiler*>(profiler);
  }
  static v8::CpuProfiler* profiler() { return profiler_; }
  static v8::CpuProfile* last_profile;

 private:
  static void StartProfiling(const v8::FunctionCallbackInfo<v8::Value>& info);
  static void StopProfiling(const v8::FunctionCallbackInfo<v8::Value>& info);
  static void CollectSample(const v8::FunctionCallbackInfo<v8::Value>& info);

  static v8::CpuProfiler* profiler_;
  static const char* kSource;
};


}  // namespace internal
}  // namespace v8

#endif
