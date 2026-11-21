# bwpo QMK userspace

This repository holds the bwpo keymaps of the Preonic rev3 and of the IDOBAO
ID75 v2. It is a [QMK userspace](https://docs.qmk.fm/newbs_external_userspace),
which QMK compiles together with a separate clone of
[qmk_firmware](https://github.com/qmk/qmk_firmware), without a fork of it.

## Contents

- [`keyboards/preonic/keymaps/bwpo`](keyboards/preonic/keymaps/bwpo/readme.md)
  holds the keymap of the Preonic rev3
- [`keyboards/idobao/id75/keymaps/bwpo`](keyboards/idobao/id75/keymaps/bwpo/readme.md)
  holds the keymap of the ID75 v2
- [`users/bwpo`](users/bwpo/readme.md) holds the code shared by the keymaps
  named `bwpo`
- `xkb` holds the `bwpo(ortho)` keyboard layout for Linux hosts. The readmes of
  the keymaps describe how to install it
- `qmk.json` lists the build targets, each made of a keyboard and a keymap

## Build with GitHub

`.github/workflows/build_binaries.yaml` compiles the build targets of `qmk.json`
on each push that changes the firmware, and publishes the firmware in the
`latest` release of this repository. Its `paths-ignore` list names the files
that do not change the firmware. The `qmk_repo` and `qmk_ref` parameters of its
`build` job set the QMK repository and branch that it compiles with.

## Build locally

`mise run compile` compiles the firmware in a container, without installing QMK
on the host. The [Tasks](#tasks) section describes it.

## Tasks

`mise.toml` and the `mise-tasks` folder define tasks that mise runs with the
tools of the `[tools]` section of `mise.toml`:

- `mise run compile` compiles the firmware of the build targets of `qmk.json` in
  the `ghcr.io/qmk/qmk_cli` container image, with podman, and copies it to the
  root of the repository. It uses the `qmk_firmware` clone next to this
  repository, and clones it with its submodules if it is missing. It shows the
  commit of this clone, and does not update it
- `mise run flash-preonic` flashes the Preonic with the firmware of the latest
  GitHub release. With `--local`, it flashes the firmware compiled locally. The
  [readme of the Preonic keymap](keyboards/preonic/keymaps/bwpo/readme.md#flashing)
  describes this task
- `mise run lint` checks that the Nushell scripts of the tasks parse

## Formatting

`dprint fmt` formats the C files with clang-format, according to
`.clang-format`, and the JSON, Markdown, TOML and YAML files with its own
plugins. mise installs dprint and clang-format from the `[tools]` section of
`mise.toml`. In the keymaps, `// clang-format off` and `// clang-format on`
surround the keymap arrays, whose columns are aligned by hand.
