#!/usr/bin/env bash

DEBIAN_PACKAGES="python3 python3-pip"
FEDORA_PACKAGES="python3 python3-pip"
ARCH_PACKAGES="python3 python-pip"

. scripts/setup.sh

install_packages || die "Failed to install packages!"

pip3 install cpplint

