// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_TREE_TREE_VIEW_DRAWING_PROVIDER_H_
#define UI_VIEWS_CONTROLS_TREE_TREE_VIEW_DRAWING_PROVIDER_H_

#include "base/strings/string16.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/views/views_export.h"

namespace ui {
class TreeModelNode;
}

namespace views {

class TreeView;

// This class is responsible for customizing the appearance of a TreeView.
// Install an instance of it into a TreeView using
// |TreeView::SetDrawingProvider|.
class VIEWS_EXPORT TreeViewDrawingProvider {
 public:
  TreeViewDrawingProvider();
  virtual ~TreeViewDrawingProvider();

  // These methods return the colors that should be used to draw specific parts
  // of the node |node| in TreeView |tree_view|.
  virtual SkColor GetBackgroundColorForNode(TreeView* tree_view,
                                            ui::TreeModelNode* node);
  virtual SkColor GetTextColorForNode(TreeView* tree_view,
                                      ui::TreeModelNode* node);

  // The auxiliary text for a node is descriptive text drawn on the trailing end
  // of the node's row in the treeview.
  virtual base::string16 GetAuxiliaryTextForNode(TreeView* tree_view,
                                                 ui::TreeModelNode* node);
};

}  // namespace views

#endif  // UI_VIEWS_CONTROLS_TREE_TREE_VIEW_DISPLAY_PROVIDER_H_
