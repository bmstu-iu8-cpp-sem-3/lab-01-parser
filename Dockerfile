FROM ubuntu:21.04
LABEL version="0.1"
LABEL maintainer="rusdevops@gmail.com"
ENV DEBIAN_FRONTEND noninteractive
RUN apt -y update && \
    apt -y install clang g++ cmake libgtest-dev libgmock-dev git \
    python3 python3-pip gcovr lcov doxygen && \
    python3 -m pip install cpplint requests gitpython && \
    apt clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
