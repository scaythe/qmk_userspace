# Shows the local firmware, the file of this name that mise run compile copies to
# the root of the repository, asks for confirmation unless --yes is given, then
# flashes it with the flash closure, which receives its path
export def flash-local-firmware [firmware: string, flash: closure, --yes] {
  let path = $env.PWD | path join $firmware
  if not ($path | path exists) {
    error make {msg: $"($firmware) is missing at the root of the repository: run mise run compile first"}
  }
  print-local-firmware $firmware $path
  if not $yes { confirm-flash }
  do $flash $path
}

# Shows the latest GitHub release, asks for confirmation unless --yes is given,
# then downloads the firmware file of this name from the release and flashes it
# with the flash closure, which receives its path
export def flash-latest-release [firmware: string, flash: closure, --yes] {
  print-latest-release
  if not $yes { confirm-flash }
  download-and-flash-latest-release $firmware $flash
}

def print-local-firmware [firmware: string, path: string] {
  let modified = ls $path | first | get modified | format date "%Y-%m-%d %H:%M"
  print $"Local firmware: ($firmware), modified on ($modified)"
}

def print-latest-release [] {
  let commit = ^gh api "repos/{owner}/{repo}/commits/latest" | from json
  let subject = $commit.commit.message | lines | first
  let published = ^gh release view latest --json publishedAt | from json | get publishedAt
    | into datetime | date to-timezone local | format date "%Y-%m-%d %H:%M"
  print $"Latest release: commit ($commit.sha | str substring 0..6) ($subject), published on ($published)"
}

def download-and-flash-latest-release [firmware: string, flash: closure] {
  let dir = mktemp --directory --tmpdir-path ($env.HOME | path join ".cache") "flash-firmware.XXXXXX"
  try {
    ^gh release download latest --pattern $firmware --dir $dir
    do $flash ($dir | path join $firmware)
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
