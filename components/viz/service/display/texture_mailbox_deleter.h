// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VIZ_SERVICE_DISPLAY_TEXTURE_MAILBOX_DELETER_H_
#define COMPONENTS_VIZ_SERVICE_DISPLAY_TEXTURE_MAILBOX_DELETER_H_

#include <memory>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "components/viz/service/viz_service_export.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace gpu {
struct SyncToken;
}

namespace viz {
class ContextProvider;
class SingleReleaseCallback;

class VIZ_SERVICE_EXPORT TextureMailboxDeleter {
 public:
  // task_runner corresponds with the thread the delete task should be posted
  // to. If null, the delete will happen on the calling thread.
  explicit TextureMailboxDeleter(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);
  ~TextureMailboxDeleter();

  // Returns a Callback that can be used as the ReleaseCallback for a
  // TextureMailbox attached to the |texture_id|. The ReleaseCallback can
  // be passed to other threads and will destroy the texture, once it is
  // run, on the impl thread. If the TextureMailboxDeleter is destroyed
  // due to the compositor shutting down, then the ReleaseCallback will
  // become a no-op and the texture will be deleted immediately on the
  // impl thread, along with dropping the reference to the ContextProvider.
  std::unique_ptr<SingleReleaseCallback> GetReleaseCallback(
      scoped_refptr<ContextProvider> context_provider,
      unsigned texture_id);

 private:
  // Runs the |impl_callback| to delete the texture and removes the callback
  // from the |impl_callbacks_| list.
  void RunDeleteTextureOnImplThread(SingleReleaseCallback* impl_callback,
                                    const gpu::SyncToken& sync_token,
                                    bool is_lost);

  scoped_refptr<base::SingleThreadTaskRunner> impl_task_runner_;
  std::vector<std::unique_ptr<SingleReleaseCallback>> impl_callbacks_;
  base::WeakPtrFactory<TextureMailboxDeleter> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(TextureMailboxDeleter);
};

}  // namespace viz

#endif  // COMPONENTS_VIZ_SERVICE_DISPLAY_TEXTURE_MAILBOX_DELETER_H_
