const poll_interval = 500ms

# Waits until a USB device with these IDs is connected, then returns its device
# file
export def wait-for-usb-device [vendor_id: string, product_id: string] {
  loop {
    let device = find-usb-device $vendor_id $product_id
    if $device != null { return $device }
    sleep $poll_interval
  }
}

# Returns the device file of a connected USB device with these IDs, or null when
# none is connected
def find-usb-device [vendor_id: string, product_id: string] {
  let devices = ls /sys/bus/usb/devices | get name | where {|dir| has-ids $dir $vendor_id $product_id }
  if ($devices | is-empty) { return null }
  read-device-file ($devices | first)
}

def has-ids [dir: string, vendor_id: string, product_id: string] {
  let vendor_file = $dir | path join idVendor
  if not ($vendor_file | path exists) { return false }
  let product = open ($dir | path join idProduct) | str trim
  (open $vendor_file | str trim) == $vendor_id and $product == $product_id
}

# The uevent file of a USB device gives the name of its device file under /dev
def read-device-file [dir: string] {
  let name = open ($dir | path join uevent) | lines | parse "{key}={value}" | where key == DEVNAME | get value | first
  $"/dev/($name)"
}
