// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_IOS_WEB_FAVICON_DRIVER_H_
#define COMPONENTS_FAVICON_IOS_WEB_FAVICON_DRIVER_H_

#include "base/macros.h"
#include "components/favicon/core/favicon_driver_impl.h"
#import "components/image_fetcher/ios/ios_image_data_fetcher_wrapper.h"
#include "ios/web/public/web_state/web_state_observer.h"
#include "ios/web/public/web_state/web_state_user_data.h"

namespace web {
class WebState;
}

namespace favicon {

// WebFaviconDriver is an implementation of FaviconDriver that listen to
// WebState events to start download of favicons and to get informed when the
// favicon download has completed.
class WebFaviconDriver : public web::WebStateObserver,
                         public web::WebStateUserData<WebFaviconDriver>,
                         public FaviconDriverImpl {
 public:
  ~WebFaviconDriver() override;

  static void CreateForWebState(web::WebState* web_state,
                                FaviconService* favicon_service,
                                history::HistoryService* history_service);

  // FaviconDriver implementation.
  gfx::Image GetFavicon() const override;
  bool FaviconIsValid() const override;
  GURL GetActiveURL() override;

  // FaviconHandler::Delegate implementation.
  int DownloadImage(const GURL& url,
                    int max_image_size,
                    ImageDownloadCallback callback) override;
  void DownloadManifest(const GURL& url,
                        ManifestDownloadCallback callback) override;
  bool IsOffTheRecord() override;
  void OnFaviconUpdated(
      const GURL& page_url,
      FaviconDriverObserver::NotificationIconType notification_icon_type,
      const GURL& icon_url,
      bool icon_url_changed,
      const gfx::Image& image) override;

 private:
  friend class web::WebStateUserData<WebFaviconDriver>;

  WebFaviconDriver(web::WebState* web_state,
                   FaviconService* favicon_service,
                   history::HistoryService* history_service);

  // web::WebStateObserver implementation.
  void DidStartNavigation(web::NavigationContext* navigation_context) override;
  void DidFinishNavigation(web::NavigationContext* navigation_context) override;
  void FaviconUrlUpdated(
      const std::vector<web::FaviconURL>& candidates) override;

  // Invoked when new favicon URL candidates are received.
  void FaviconUrlUpdatedInternal(
      const std::vector<favicon::FaviconURL>& candidates);

  // Image Fetcher used to fetch favicon.
  image_fetcher::IOSImageDataFetcherWrapper image_fetcher_;

  // Caches the favicon URLs candidates for same-document navigations.
  std::vector<favicon::FaviconURL> candidates_;

  DISALLOW_COPY_AND_ASSIGN(WebFaviconDriver);
};

}  // namespace favicon

#endif  // COMPONENTS_FAVICON_IOS_WEB_FAVICON_DRIVER_H_
