# Build environment for the Qt demo app: Ubuntu 24.04 + prebuilt Qt 6.12.0.
# Qt is downloaded as binaries with aqtinstall, nothing is built from source.

# Base image pinned by digest, so the image tag (hash of ci-docker/) always
# means the same base. To update: pull ubuntu:24.04 and paste its new digest.
ARG UBUNTU_IMAGE=ubuntu:24.04@sha256:2198e4c65076e9cb0b3d695219df667c0e3b0072da64ca3c2648aca17dcecaf5
ARG QT_VERSION=6.12.0

# ---- Stage 1: download Qt (pip and aqtinstall stay here) ----
FROM ${UBUNTU_IMAGE} AS qt-download

ARG QT_VERSION
ARG AQT_VERSION=3.3.0
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        ca-certificates \
        python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp
RUN pip3 install --no-cache-dir --break-system-packages aqtinstall==${AQT_VERSION} \
    && aqt install-qt linux desktop ${QT_VERSION} linux_gcc_64 -O /opt/Qt

# ---- Stage 2: the CI image ----
FROM ${UBUNTU_IMAGE}

ARG QT_VERSION

# "source" links the GHCR package to the repo, so CI can pull it with GITHUB_TOKEN
LABEL org.opencontainers.image.source="https://github.com/mateusz-fejcher7/qt-cicd-demo" \
      org.opencontainers.image.description="Ubuntu 24.04 with prebuilt Qt ${QT_VERSION} for CI builds" \
      org.opencontainers.image.licenses="LGPL-3.0-only AND GPL-3.0-only WITH Qt-GPL-exception-1.0"

# No interactive questions from apt
ENV DEBIAN_FRONTEND=noninteractive

# Build tools + the system libraries Qt needs on a bare Ubuntu
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        git \
        ca-certificates \
        libgl1-mesa-dev \
        libegl1 \
        libfontconfig1 \
        libdbus-1-3 \
        libglib2.0-0t64 \
        libxkbcommon0 \
        libxkbcommon-dev \
        libxkbcommon-x11-0 \
        libxcb-cursor0 \
        libxcb-icccm4 \
        libxcb-image0 \
        libxcb-keysyms1 \
        libxcb-render0 \
        libxcb-render-util0 \
        libxcb-shape0 \
        libxcb-util1 \
        libxcb-xkb1 \
        libwayland-cursor0 \
    && rm -rf /var/lib/apt/lists/*

# Only the Qt files, no download tools
COPY --from=qt-download /opt/Qt /opt/Qt

# Qt license notice, with the real Qt version filled in
COPY QT_LICENSE_NOTICE.md /opt/Qt/QT_LICENSE_NOTICE.md
RUN sed -i \
        -e "s|@QT_VERSION@|${QT_VERSION}|g" \
        -e "s|@QT_MINOR@|${QT_VERSION%.*}|g" \
        /opt/Qt/QT_LICENSE_NOTICE.md \
    && ! grep -q '@QT_' /opt/Qt/QT_LICENSE_NOTICE.md

# CMake finds Qt without -DCMAKE_PREFIX_PATH, apps run without a display
ENV CMAKE_PREFIX_PATH=/opt/Qt/${QT_VERSION}/gcc_64 \
    QT_QPA_PLATFORM=offscreen \
    LANG=C.UTF-8

WORKDIR /src
