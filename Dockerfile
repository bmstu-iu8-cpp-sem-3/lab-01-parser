# rusdevops/bootstrap-cpp image
FROM ubuntu:20.04
LABEL maintainer="rusdevops@gmail.com"
ENV DEBIAN_FRONTEND noninteractive
RUN apt -y update && \
    apt -y install software-properties-common curl llvm lcov gcovr cmake python3-pip clang && \
    add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt install -yq g++-7 && \
    pip3 install cpplint && \
    apt clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
