const image = "ghcr.io/qmk/qmk_cli"

# Runs a command in the QMK CLI container image, with podman, or with docker
# when podman is missing
export def run-qmk-container [options: list<string>, command: list<any>] {
  if (which podman | is-not-empty) { return (run-with-podman $options $command) }
  if (which docker | is-not-empty) { return (run-with-docker $options $command) }
  error make {msg: "podman or docker is required to run the QMK CLI container image"}
}

def run-with-podman [options: list<string>, command: list<any>] {
  ^podman run --rm ...$options $image ...$command
}

# Docker runs the container as the current user, so that the files that the
# container writes in the mounted folders belong to this user. Rootless podman
# already maps the root of the container to this user.
def run-with-docker [options: list<string>, command: list<any>] {
  ^docker run --rm --user $"(^id -u):(^id -g)" ...$options $image ...$command
}
