// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHARED_IMMERSIVE_CONTEXT_H_
#define ASH_SHARED_IMMERSIVE_CONTEXT_H_

#include "ash/ash_export.h"

namespace gfx {
class Rect;
}
namespace views {
class PointerWatcher;
class Widget;
}

namespace ash {

class ImmersiveFullscreenController;

// ImmersiveFullscreenController is used in four distinct environments: ash,
// mash, chrome in ash and chrome in mash. All of these have slightly different
// restrictions. ImmersiveContext enables ImmersiveFullscreenController to be
// used in these different environments. ImmersiveContext abstracts away all the
// windowing related calls so that ImmersiveFullscreenController does not
// depend upon aura, mus or ash.
//
// ImmersiveContext is a singleton.
class ASH_EXPORT ImmersiveContext {
 public:
  static ImmersiveContext* Get() { return instance_; }

  // Mirrors that of WmShell::InstallResizeHandleWindowTargeter(), see it
  // for details
  virtual void InstallResizeHandleWindowTargeter(
      ImmersiveFullscreenController* controller) = 0;

  // Used to setup state necessary for entering or existing immersive mode. It
  // is expected this interacts with the shelf, and installs any other necessary
  // state.
  virtual void OnEnteringOrExitingImmersive(
      ImmersiveFullscreenController* controller,
      bool entering) = 0;

  // Returns the bounds of the display the widget is on, in screen coordinates.
  virtual gfx::Rect GetDisplayBoundsInScreen(views::Widget* widget) = 0;

  // See WmShell::AddPointerWatcher for details.
  virtual void AddPointerWatcher(views::PointerWatcher* watcher,
                                 bool wants_moves) = 0;
  virtual void RemovePointerWatcher(views::PointerWatcher* watcher) = 0;

  // Returns true if any window has capture.
  virtual bool DoesAnyWindowHaveCapture() = 0;

  // See WmShell::IsMouseEventsEnabled() for details.
  virtual bool IsMouseEventsEnabled() = 0;

 protected:
  ImmersiveContext();
  virtual ~ImmersiveContext();

 private:
  static ImmersiveContext* instance_;
};

}  // namespace ash

#endif  // ASH_SHARED_IMMERSIVE_CONTEXT_H_