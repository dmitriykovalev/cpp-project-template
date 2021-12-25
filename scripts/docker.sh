#!/bin/bash

set -ex

if [[ -f /.dockerenv ]]; then
  exit 1
fi

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly PROJECT_DIR="${SCRIPT_DIR}/.."

function docker_build {
  docker build --build-arg IMAGE="${DOCKER_IMAGE:-debian:bullseye}" \
               ${PROJECT_DIR}/docker "$@"
}

docker_build

docker run -it --rm -v ${PROJECT_DIR}:/workspace -w /workspace \
       "$(docker_build --quiet)" "$@"
