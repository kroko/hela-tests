#!/usr/bin/env bash
# composed by kroko / WARP

PROJECT_NAME=HelloFBdev

# If you don't want to open Xcode - sure, you can build from terminal
PATH_PROJECT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PATH_XCODEPROJ=$PATH_PROJECT/$PROJECT_NAME.xcodeproj

xcrun xcodebuild -project "$PATH_XCODEPROJ" -target $PROJECT_NAME -configuration Release $@
xcrun xcodebuild -project "$PATH_XCODEPROJ" -target $PROJECT_NAME -configuration Debug $@