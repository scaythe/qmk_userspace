#!/usr/bin/env nu
#MISE description="Compile the firmware of the build targets of qmk.json in the QMK CLI container"

const image = "ghcr.io/qmk/qmk_cli"
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
# read and write them
def compile [qmk_firmware: string] {
  (^podman run --rm
    --volume $"($qmk_firmware):/qmk_firmware:z"
    --volume $"($env.PWD):/qmk_userspace:z"
    --workdir /qmk_userspace
    $image
    sh -c "qmk config user.qmk_home=/qmk_firmware user.overlay_dir=/qmk_userspace > /dev/null && qmk userspace-compile")
}
