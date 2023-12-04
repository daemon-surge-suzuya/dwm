#!/bin/bash

# Path to the directory containing wallpapers
wallpaper_dir="$1"

# Check if the directory exists
if [ ! -d "$wallpaper_dir" ]; then
    dunstify "Error: Wallpaper directory not found."
    exit 1
fi

# List all image files in the wallpaper directory
wallpapers=$(find "$wallpaper_dir" -type f \( -iname "*.jpg" -o -iname "*.jpeg" -o -iname "*.png" -o -iname "*.gif" \))

# Use dmenu to let the user choose a wallpaper
chosen_wallpaper=$(echo "$wallpapers" | dmenu -fn "monospace:size=12" -nb "#222222" -nf "#bbbbbb" -sb "#9b99e8" -sf "#eeeeee" -l 10 -p "Select Wallpaper:")

# Check if the user selected a wallpaper
if [ -n "$chosen_wallpaper" ]; then
    # Use feh to set the chosen wallpaper
    feh --bg-fill "$chosen_wallpaper"
    dunstify "Wallpaper changed to: $chosen_wallpaper"
else
    dunstify "No wallpaper selected. Exiting."
fi

