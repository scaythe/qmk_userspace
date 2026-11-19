#!/usr/bin/env nu
#MISE description="Flash the Preonic with the firmware of the latest GitHub release"

const firmware = "preonic_rev3_bwpo.bin"
const box = "qmk"
const bootloader_delay = 5sec
const stm32_bootloader_usb_id = "0483:df11"
const dfu_alt_setting = 0
const flash_start_address = "0x8000000"

def main [] {
  print-latest-release
  if not (is-flash-confirmed) { cancel-flash }
  if not (box-exists) { create-box }
  flash-latest-release
}

def print-latest-release [] {
  let commit = ^gh api "repos/{owner}/{repo}/commits/latest" | from json
  let subject = $commit.commit.message | lines | first
  let published = ^gh release view latest --json publishedAt | from json | get publishedAt
    | into datetime | date to-timezone local | format date "%Y-%m-%d %H:%M"
  print $"Latest release: commit ($commit.sha | str substring 0..6) ($subject), published on ($published)"
}

def is-flash-confirmed [] {
  (input "Flash this firmware? [y/N] ") in ["y" "Y"]
}

def cancel-flash [] {
  print "Flash cancelled"
  exit 0
}

# --flexible accepts the rows of distrobox list that span several lines, with
# another number of fields than the header
def box-exists [] {
  $box in (^distrobox list --no-color | from csv --separator "|" --trim all --flexible | get NAME)
}

def create-box [] {
  ^distrobox assemble create --file distrobox.ini --name $box
}

def flash-latest-release [] {
  let dir = mktemp --directory --tmpdir-path ($env.HOME | path join ".cache") "flash-preonic.XXXXXX"
  try {
    download-and-flash $dir
  } finally {
    rm --recursive $dir
  }
}

def download-and-flash [dir: string] {
  ^gh release download latest --pattern $firmware --dir $dir
  print $"Put the Preonic in bootloader mode within ($bootloader_delay)"
  sleep $bootloader_delay
  (^distrobox enter $box -- dfu-util
    --alt $dfu_alt_setting
    --device $stm32_bootloader_usb_id
    --dfuse-address $"($flash_start_address):leave"
    --download ($dir | path join $firmware))
}
