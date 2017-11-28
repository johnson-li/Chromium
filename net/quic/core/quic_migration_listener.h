// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// A listener that is triggered on server migration.
//
// Note: this listener is intended for late binding.

#ifndef NET_QUIC_CORE_QUIC_MIGRATION_LISTENER_H
#define NET_QUIC_CORE_QUIC_MIGRATION_LISTENER_H

#include "net/quic/platform/api/quic_socket_address.h"

namespace net {

    class QuicMigrationListener {
    public:
        QuicMigrationListener() {}

        virtual ~QuicMigrationListener() {}

        virtual void OnMigration(QuicSocketAddress& peer_address) = 0;
    };
}

#endif //NET_QUIC_CORE_QUIC_MIGRATION_LISTENER_H

