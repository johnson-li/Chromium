// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_AUDIO_MOCK_AUDIO_MANAGER_H_
#define MEDIA_AUDIO_MOCK_AUDIO_MANAGER_H_

#include <memory>
#include <string>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/sequenced_task_runner_helpers.h"
#include "base/single_thread_task_runner.h"
#include "media/audio/audio_manager.h"

namespace media {

// This class is a simple mock around AudioManager, used exclusively for tests,
// which avoids to use the actual (system and platform dependent) AudioManager.
// Some bots does not have input devices, thus using the actual AudioManager
// would causing failures on classes which expect that.
class MockAudioManager : public AudioManager {
 public:
  using GetDeviceDescriptionsCallback =
      base::RepeatingCallback<void(AudioDeviceDescriptions*)>;
  using GetAssociatedOutputDeviceIDCallback =
      base::RepeatingCallback<std::string(const std::string&)>;
  using MakeOutputStreamCallback =
      base::RepeatingCallback<media::AudioOutputStream*(
          const media::AudioParameters& params,
          const std::string& device_id)>;
  using MakeInputStreamCallback =
      base::RepeatingCallback<media::AudioInputStream*(
          const media::AudioParameters& params,
          const std::string& device_id)>;

  explicit MockAudioManager(std::unique_ptr<AudioThread> audio_thread);
  ~MockAudioManager() override;

  AudioOutputStream* MakeAudioOutputStream(
      const media::AudioParameters& params,
      const std::string& device_id,
      const LogCallback& log_callback) override;

  AudioOutputStream* MakeAudioOutputStreamProxy(
      const media::AudioParameters& params,
      const std::string& device_id) override;

  AudioInputStream* MakeAudioInputStream(
      const media::AudioParameters& params,
      const std::string& device_id,
      const LogCallback& log_callback) override;

  void AddOutputDeviceChangeListener(AudioDeviceListener* listener) override;
  void RemoveOutputDeviceChangeListener(AudioDeviceListener* listener) override;

  std::unique_ptr<AudioLog> CreateAudioLog(
      AudioLogFactory::AudioComponent component) override;

  void InitializeOutputDebugRecording() override;
  void EnableOutputDebugRecording(
      const base::FilePath& base_file_name) override;
  void DisableOutputDebugRecording() override;

  const char* GetName() override;

  // Setters to emulate desired in-test behavior.
  void SetMakeOutputStreamCB(MakeOutputStreamCallback cb);
  void SetMakeInputStreamCB(MakeInputStreamCallback cb);
  void SetInputStreamParameters(const AudioParameters& params);
  void SetOutputStreamParameters(const AudioParameters& params);
  void SetDefaultOutputStreamParameters(const AudioParameters& params);
  void SetHasInputDevices(bool has_input_devices);
  void SetHasOutputDevices(bool has_output_devices);
  void SetInputDeviceDescriptionsCallback(
      GetDeviceDescriptionsCallback callback);
  void SetOutputDeviceDescriptionsCallback(
      GetDeviceDescriptionsCallback callback);
  void SetAssociatedOutputDeviceIDCallback(
      GetAssociatedOutputDeviceIDCallback callback);

 protected:
  void ShutdownOnAudioThread() override;

  bool HasAudioOutputDevices() override;

  bool HasAudioInputDevices() override;

  void GetAudioInputDeviceDescriptions(
      media::AudioDeviceDescriptions* device_descriptions) override;

  void GetAudioOutputDeviceDescriptions(
      media::AudioDeviceDescriptions* device_descriptions) override;

  AudioParameters GetDefaultOutputStreamParameters() override;
  AudioParameters GetOutputStreamParameters(
      const std::string& device_id) override;
  AudioParameters GetInputStreamParameters(
      const std::string& device_id) override;
  std::string GetAssociatedOutputDeviceID(
      const std::string& input_device_id) override;

 private:
  AudioParameters input_params_;
  AudioParameters output_params_;
  AudioParameters default_output_params_;
  bool has_input_devices_ = true;
  bool has_output_devices_ = true;
  MakeOutputStreamCallback make_output_stream_cb_;
  MakeInputStreamCallback make_input_stream_cb_;
  GetDeviceDescriptionsCallback get_input_device_descriptions_cb_;
  GetDeviceDescriptionsCallback get_output_device_descriptions_cb_;
  GetAssociatedOutputDeviceIDCallback get_associated_output_device_id_cb_;

  DISALLOW_COPY_AND_ASSIGN(MockAudioManager);
};

}  // namespace media.

#endif  // MEDIA_AUDIO_MOCK_AUDIO_MANAGER_H_
