#!/usr/bin/env bash

die() {
  echo $1
  exit -1
}

nothing_to_install() {
  echo "Nothing to install!"
  exit 0
}

detect_message() {
  echo "$1 detected! Will use $2 for installing everything"
}

install_packages() {
  if [[ "$OSTYPE" == "linux-gnu" ]]; then
    test -e /etc/os-release && os_release='/etc/os-release' || os_release='/usr/lib/os-release'
    . "${os_release}"

    if [[ "$ID" == "debian" || "$ID_LIKE" == "debian" || "$ID_LIKE" == "ubuntu" ]]; then
      detect_message "Debian/Ubuntu or derivatives" "apt"
      if [[ -z $DEBIAN_PACKAGES  ]]; then nothing_to_install; fi
      sudo apt update
      sudo apt install -y $DEBIAN_PACKAGES
      return 0
    elif [[ "$ID" == "fedora" ]]; then
      detect_message "Fedora" "dnf"
      if [[ -z $FEDORA_PACKAGES ]]; then nothing_to_install; fi
      sudo dnf -y install $FEDORA_PACKAGES
      return 0
    elif [[ "$ID" == "arch" || "$ID_LIKE" == "arch" ]]; then
      if [[ -z $ARCH_PACKAGES ]]; then nothing_to_install; fi
      detect_message "Arch or arch-derivative" "pacman"
      sudo pacman --noconfirm -Syu $ARCH_PACKAGES
      return 0
    else
      die "You\'re running an unsupported distro! Please be welcome to ask us to bring support or make it supported yourself!"
    fi
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    if [[ $(type port) ]]; then
      detect_message "MacPorts" "that"
      if [[ -z $MACPORTS_PACKAGES ]]; then nothing_to_install; fi
      sudo port install $MACPORTS_PACKAGES
      return 0
    elif [[ $(type brew) ]]; then
      detect_message "Brew" "that"
      if [[ -z $BREW_PACKAGES ]]; then nothing_to_install; fi
      brew install $BREW_PACKAGES
      return 0
    else
      die "No package manager detected! Try installing Brew: brew.sh or MacPorts: macports.org"
    fi
  fi
}
