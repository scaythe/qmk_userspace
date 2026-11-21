#!/usr/bin/env nu
#MISE description="Compile the firmware of the build targets of qmk.json in the QMK CLI container"

use lib/container.nu [run-qmk-container]

const qmk_firmware_url = "https://github.com/qmk/qmk_firmware.git"

def main [] {
  let qmk_firmware = $env.PWD | path dirname | path join "qmk_firmware"
  if not ($qmk_firmware | path exists) { clone-qmk-firmware $qmk_firmware }
  print-qmk-firmware-commit $qmk_firmware
  compile $qmk_firmware
}

def clone-qmk-firmware [path: string] {
  ^git clone --recurse-submodules $qmk_firmware_url $path
}

def print-qmk-firmware-commit [path: string] {
  let commit = ^git -C $path log -1 --format="%h %cs %s"
  print $"qmk_firmware: ($commit)"
}

# The :z option relabels the mounted folders so that SELinux lets the container
# read and write them. QMK_HOME and QMK_USERSPACE locate the folders without a
# QMK configuration file, which the container could not write as a user other
# than root.
def compile [qmk_firmware: string] {
  let options = [
    --volume $"($qmk_firmware):/qmk_firmware:z"
    --volume $"($env.PWD):/qmk_userspace:z"
    --env QMK_HOME=/qmk_firmware
    --env QMK_USERSPACE=/qmk_userspace
    --workdir /qmk_userspace
  ]
  run-qmk-container $options [qmk userspace-compile]
}
