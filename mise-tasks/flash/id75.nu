#!/usr/bin/env nu
#MISE description="Flash the ID75 with the firmware of the latest GitHub release, or with the local firmware"

use ../lib/firmware.nu [flash-local-firmware flash-latest-release]

const firmware = "ymdk_id75_rp2040_bwpo.uf2"
const bootloader_drive_label = "RPI-RP2"
const poll_interval = 500ms

def main [
  --local # Flash the local firmware instead of the latest release
  --yes (-y) # Flash without asking for confirmation
] {
  if $local {
    flash-local-firmware $firmware {|path| flash $path } --yes=$yes
  } else {
    flash-latest-release $firmware {|path| flash $path } --yes=$yes
  }
}

# The RP2040 bootloader flashes the UF2 file copied to its drive, then restarts
# the keyboard
def flash [path: string] {
  print "Put the ID75 in bootloader mode"
  let drive = wait-for-mounted-drive $bootloader_drive_label
  ^cp $path $drive
  ^sync
  print $"Firmware copied to ($drive)"
}

# Waits until the desktop mounts the drive with this label, then returns its
# mount point
def wait-for-mounted-drive [label: string] {
  loop {
    let result = ^findmnt --noheadings --output TARGET --source $"LABEL=($label)" | complete
    if $result.exit_code == 0 { return ($result.stdout | lines | first) }
    sleep $poll_interval
  }
}
