// -*- Mode: objc; Coding: utf-8; indent-tabs-mode: nil; -*-

#import <Cocoa/Cocoa.h>
#import "Sparkle/SUUpdater.h"
#import "PreferencesManager.h"

@interface Updater : NSObject {
  SUUpdater* suupdater_;

  IBOutlet PreferencesManager* preferencesManager_;
}

- (IBAction) checkForUpdates:(id)sender;
- (IBAction) checkForUpdatesInBackground:(id)sender;

@end
