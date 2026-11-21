#!/usr/bin/env nu
#MISE description="Flash the ID75 with the firmware of the latest GitHub release, or with the local firmware"

use ../lib/firmware.nu [flash-local-firmware flash-latest-release]
use ../lib/usb.nu [wait-for-usb-device]
use ../lib/container.nu [run-in-qmk-container]

const firmware = "idobao_id75_v2_bwpo.hex"
const mcu = "atmega32u4"
const atmel_dfu_vendor_id = "03eb"
const atmega32u4_bootloader_product_id = "2ff4"

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

def flash [path: string] {
  print "Put the ID75 in bootloader mode"
  let device = wait-for-usb-device $atmel_dfu_vendor_id $atmega32u4_bootloader_product_id
  run-dfu-programmer $device $path
}

# The flash commands are those of the atmel-dfu bootloader in QMK, for
# dfu-programmer 1.x
def run-dfu-programmer [device: string, path: string] {
  run-in-qmk-container $device $path {|container_path|
    [sh -c $"dfu-programmer ($mcu) erase && dfu-programmer ($mcu) flash ($container_path) && dfu-programmer ($mcu) reset"]
  }
}
