#!/usr/bin/env nu
#MISE description="Flash the Preonic with the firmware of the latest GitHub release, or with the local firmware"

use ../lib/firmware.nu [flash-local-firmware flash-latest-release]
use ../lib/usb.nu [wait-for-usb-device]
use ../lib/container.nu [run-in-qmk-container]

const firmware = "preonic_rev3_bwpo.bin"
const stm32_vendor_id = "0483"
const stm32_bootloader_product_id = "df11"
const dfu_alt_setting = 0
const flash_start_address = "0x8000000"

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
  print "Put the Preonic in bootloader mode"
  let device = wait-for-usb-device $stm32_vendor_id $stm32_bootloader_product_id
  run-dfu-util $device $path
}

def run-dfu-util [device: string, path: string] {
  run-in-qmk-container $device $path {|container_path|
    [
      dfu-util
      --alt $dfu_alt_setting
      --device $"($stm32_vendor_id):($stm32_bootloader_product_id)"
      --dfuse-address $"($flash_start_address):leave"
      --download $container_path
    ]
  }
}
