#!/bin/bash

# Directory containing the snapshot files
SNAPSHOT_DIR="$(pwd)/archive"

# Dataset to which snapshots will be applied
TARGET_DATASET="mypool/dataset"

# Mount point for the ZFS dataset
MOUNT_POINT="/mnt/zfs_dataset"

# Create a temporary directory for the merged stream
MERGE_DIR="/tmp/zfs_merge"
mkdir -p "$MERGE_DIR"

# Create a temporary disk image file
TEMP_DISK="/tmp/tempdisk.img"
DISK_SIZE="1G"  # Change this size as needed
echo "Creating a temporary disk image of size $DISK_SIZE at $TEMP_DISK..."
sudo dd if=/dev/zero of="$TEMP_DISK" bs=1M count=1024

# Force detach loop device if it's already in use
if losetup /dev/loop0 >/dev/null 2>&1; then
    echo "Forcibly detaching /dev/loop0..."
    sudo fuser -k /dev/loop0 2>/dev/null
    sudo losetup -d /dev/loop0
fi

# Verify if the loop device is still in use
if losetup /dev/loop0 >/dev/null 2>&1; then
    echo "Loop device /dev/loop0 is still busy. Please ensure it's not in use."
    exit 1
fi

# Set up the loop device
echo "Setting up loop device /dev/loop0..."
sudo losetup /dev/loop0 "$TEMP_DISK"

# Destroy the ZFS pool if it already exists to start fresh
if zpool list mypool >/dev/null 2>&1; then
    echo "Destroying existing ZFS pool 'mypool'..."
    sudo zpool destroy mypool
fi

# Create the ZFS pool using the loop device
echo "Creating ZFS pool 'mypool' using /dev/loop0..."
if ! sudo zpool create mypool /dev/loop0; then
    echo "Failed to create ZFS pool 'mypool'."
    exit 1
fi
echo "ZFS pool 'mypool' created successfully."

# Get a sorted list of snapshot files
SNAPSHOTS=($(ls "$SNAPSHOT_DIR"/logseq*-i 2>/dev/null | sort -V))

# Check if any snapshots were found
if [ ${#SNAPSHOTS[@]} -eq 0 ]; then
    echo "No snapshot files found in $SNAPSHOT_DIR"
    exit 1
fi

# Create the target dataset if it doesn't exist
echo "Creating dataset $TARGET_DATASET..."
if ! sudo zfs create "$TARGET_DATASET"; then
    echo "Failed to create dataset $TARGET_DATASET."
    exit 1
fi

# Apply the first snapshot as a full snapshot
echo "Applying the first snapshot ${SNAPSHOTS[0]} to $TARGET_DATASET..."
if ! sudo zfs receive -F "$TARGET_DATASET" < "${SNAPSHOTS[0]}"; then
    echo "Failed to apply the first snapshot."
    exit 1
fi

# Iterate over the remaining snapshots and apply incrementally
for SNAPSHOT in "${SNAPSHOTS[@]:1}"; do
    echo "Applying incremental snapshot $SNAPSHOT to $TARGET_DATASET..."
    if ! sudo zfs receive -F "$TARGET_DATASET" < "$SNAPSHOT"; then
        echo "Failed to apply incremental snapshot $SNAPSHOT."
        exit 1
    fi
done

# Create the mount point if it doesn't exist
if [ ! -d "$MOUNT_POINT" ]; then
    echo "Creating mount point $MOUNT_POINT..."
    sudo mkdir -p "$MOUNT_POINT"
fi

# Mount the ZFS dataset
echo "Mounting $TARGET_DATASET to $MOUNT_POINT..."
if ! sudo zfs set mountpoint="$MOUNT_POINT" "$TARGET_DATASET"; then
    echo "Failed to set mountpoint for $TARGET_DATASET."
    exit 1
fi

# Verify that the dataset is mounted
if mountpoint -q "$MOUNT_POINT"; then
    echo "$TARGET_DATASET is successfully mounted at $MOUNT_POINT."
    echo "You can now browse the filesystem at $MOUNT_POINT."
else
    echo "Failed to mount $TARGET_DATASET."
    exit 1
fi

# Clean up function to unmount and destroy resources
cleanup() {
    echo "Cleaning up..."
    sudo zfs unmount "$TARGET_DATASET"
    sudo zpool destroy mypool
    sudo losetup -d /dev/loop0
    sudo rm -rf "$MERGE_DIR"
    sudo rm "$TEMP_DISK"
    sudo rmdir "$MOUNT_POINT"
    echo "Cleanup completed."
}

# Set up trap for cleanup on exit
trap cleanup EXIT

echo "Script completed successfully. Don't forget to unmount the dataset and clean up when done."

