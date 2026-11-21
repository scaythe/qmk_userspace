#!/usr/bin/env nu
#MISE description="Flash the Preonic with the firmware of the latest GitHub release, or with the local firmware"

const firmware = "preonic_rev3_bwpo.bin"
const box = "qmk"
const bootloader_delay = 5sec
const stm32_bootloader_usb_id = "0483:df11"
const dfu_alt_setting = 0
const flash_start_address = "0x8000000"

def main [
  --local # Flash the firmware that qmk compile copied to the root of the repository
] {
  if $local {
    flash-local-firmware
  } else {
    flash-latest-release
  }
}

def flash-local-firmware [] {
  let path = $env.PWD | path join $firmware
  if not ($path | path exists) {
    error make {msg: $"($firmware) is missing at the root of the repository: compile the firmware first"}
  }
  print-local-firmware $path
  confirm-flash
  flash $path
}

def print-local-firmware [path: string] {
  let modified = ls $path | first | get modified | format date "%Y-%m-%d %H:%M"
  print $"Local firmware: ($firmware), modified on ($modified)"
}

def flash-latest-release [] {
  print-latest-release
  confirm-flash
  download-and-flash-latest-release
}

def print-latest-release [] {
  let commit = ^gh api "repos/{owner}/{repo}/commits/latest" | from json
  let subject = $commit.commit.message | lines | first
  let published = ^gh release view latest --json publishedAt | from json | get publishedAt
    | into datetime | date to-timezone local | format date "%Y-%m-%d %H:%M"
  print $"Latest release: commit ($commit.sha | str substring 0..6) ($subject), published on ($published)"
}

def download-and-flash-latest-release [] {
  let dir = mktemp --directory --tmpdir-path ($env.HOME | path join ".cache") "flash-preonic.XXXXXX"
  try {
    ^gh release download latest --pattern $firmware --dir $dir
    flash ($dir | path join $firmware)
  } finally {
    rm --recursive $dir
  }
}

def confirm-flash [] {
  if (input "Flash this firmware? [y/N] ") not-in ["y" "Y"] {
    print "Flash cancelled"
    exit 0
  }
}

def flash [path: string] {
  if not (box-exists) { create-box }
  print $"Put the Preonic in bootloader mode within ($bootloader_delay)"
  sleep $bootloader_delay
  (^distrobox enter $box -- dfu-util
    --alt $dfu_alt_setting
    --device $stm32_bootloader_usb_id
    --dfuse-address $"($flash_start_address):leave"
    --download $path)
}

# --flexible accepts the rows of distrobox list that span several lines, with
# another number of fields than the header
def box-exists [] {
  $box in (^distrobox list --no-color | from csv --separator "|" --trim all --flexible | get NAME)
}

def create-box [] {
  ^distrobox assemble create --file distrobox.ini --name $box
}
