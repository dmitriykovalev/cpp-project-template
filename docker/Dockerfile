ARG IMAGE
FROM ${IMAGE}

RUN dpkg --add-architecture armhf
RUN dpkg --add-architecture arm64
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
  build-essential \
  crossbuild-essential-armhf \
  crossbuild-essential-arm64 \
  clang-tidy \
  zip \
  unzip \
  curl \
  wget \
  git \
  tree \
  vim \
  sudo \
  re2c \
  libssl-dev \
  ca-certificates \
  software-properties-common

ARG CMAKE_VERSION=3.22.1
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz && \
    echo "0e998229549d7b3f368703d20e248e7ee1f853910d42704aa87918c213ea82c0  cmake-${CMAKE_VERSION}.tar.gz" | sha256sum --check - && \
    tar -xzf cmake-${CMAKE_VERSION}.tar.gz && \
    cd cmake-${CMAKE_VERSION} && \
    ./bootstrap && make && make install

ARG NINJA_VERSION=1.10.2
RUN wget -O ninja-${NINJA_VERSION}.tar.gz https://github.com/ninja-build/ninja/archive/refs/tags/v${NINJA_VERSION}.tar.gz && \
    echo "ce35865411f0490368a8fc383f29071de6690cbadc27704734978221f25e2bed  ninja-${NINJA_VERSION}.tar.gz" | sha256sum --check - && \
    tar -xzf ninja-${NINJA_VERSION}.tar.gz && \
    cmake -S ninja-${NINJA_VERSION} -B ninja-build && \
    cmake --build ninja-build && \
    cp ninja-build/ninja /usr/local/bin
