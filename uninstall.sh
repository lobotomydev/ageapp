#!/bin/bash

EXECUTABLE_PATH="/usr/bin/ageapp"
DESKTOP_FILE_PATH="/usr/share/applications/ageapp.desktop"
ICON_PATH="/usr/share/icons/hicolor/128x128/apps/AgeAPP_ds.png"

check_files() {
  if [ ! -f "$EXECUTABLE_PATH" ] && [ ! -f "$DESKTOP_FILE_PATH" ] && [ ! -f "$ICON_PATH" ]; then
    echo "Files not found. AgeAPP is not installed or has already been uninstalled."
    exit 0
  fi
}

remove_files() {
  echo "Removing installed files..."

  sudo rm -f "$EXECUTABLE_PATH"
  if [ $? -eq 0 ]; then
    echo "Executable removed successfully."
  else
    echo "Error: Failed to remove executable. Administrator rights (sudo) may be required."
  fi

  sudo rm -f "$DESKTOP_FILE_PATH"
  if [ $? -eq 0 ]; then
    echo "Desktop file removed successfully."
  else
    echo "Error: Failed to remove desktop file."
  fi

  sudo rm -f "$ICON_PATH"
  if [ $? -eq 0 ]; then
    echo "Icon removed successfully."
  else
    echo "Error: Failed to remove icon."
  fi
}

check_files
remove_files