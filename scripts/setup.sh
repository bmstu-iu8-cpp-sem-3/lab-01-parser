#!/usr/bin/env bash

DEBIAN_PACKAGES="clang cmake gcc g++ git libgtest-dev libgmock-dev python3 python3-pip"
FEDORA_PACKAGES="clang cmake gcc gcc-c++ git gtest gmock python3 python3-pip"
ARCH_PACKAGES="base-devel clang cmake gtest git python3 python-pip"
MACPORTS_PACKAGES="cmake gtest git"
BREW_PACKAGES="cmake googletest git"

die() {
  echo $1
  exit -1
}

detect_message() {
  echo "$1 detected! Will use $2 for installing everything"
}

install_packages() {
  if [[ "$OSTYPE" == "linux-gnu" ]]; then
    test -e /etc/os-release && os_release='/etc/os-release' || os_release='/usr/lib/os-release'
    . "${os_release}"


    cat << 'EOF' >> $HOME/.bashrc
# BMSTU lab environment setup script adding appropriate PATH variable for python packages, cpplint in this case
export PATH=$PATH:$HOME/.local/bin


EOF
    if [[ "$ID" == "debian" || "$ID_LIKE" == "debian" || "$ID_LIKE" == "ubuntu" ]]; then
      detect_message "Debian/Ubuntu or derivatives" "apt"
      sudo apt update
      sudo apt install -y $DEBIAN_PACKAGES
      return 0
    elif [[ "$ID" == "fedora" ]]; then
      detect_message "Fedora" "dnf"
      sudo dnf -y install $FEDORA_PACKAGES
      return 0
    elif [[ "$ID" == "arch" || "$ID_LIKE" == "arch" ]]; then
      detect_message "Arch or arch-derivative" "pacman"
      sudo pacman --noconfirm -Syu $ARCH_PACKAGES
      return 0
    else
      die "You\'re running an unsupported distro! Please be welcome to ask us to bring support or make it supported yourself!"
    fi
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    cat << 'EOF' >> $HOME/.zprofile
# BMSTU lab environment setup script adding appropriate PATH variable for python packages, cpplint in this case
for PYTHON_PATH in $HOME/Library/Python/*; do
  PATH_ADDITION=$PATH_ADDITION:$PYTHON_PATH
done
export PATH=$PATH:$PATH_ADDITION


EOF
    if [[ $(type port) ]]; then
      detect_message "MacPorts" "that"
      sudo port install $MACPORTS_PACKAGES
      return 0
    elif [[ $(type brew) ]]; then
      detect_message "Brew" "that"
      brew install $BREW_PACKAGES
      return 0
    else
      die "No package manager detected! Try installing Brew: brew.sh or MacPorts: macports.org"
    fi
  fi
}

install_packages || die "Failed to install packages!"

pip3 install --user cpplint
echo "Installation complete! Please restart your terminal before proceeding for PATH changes to apply"
