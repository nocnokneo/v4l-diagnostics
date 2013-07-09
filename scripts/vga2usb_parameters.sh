#!/bin/bash

# Halt on errors
set -e

module=${1:-vga2usb}

if [ ! -d /sys/module/${module} ]; then
    echo "/sys/module/${module} does not exist" 1>&2
    exit 1
fi

echo "Parameters for currently loaded ${module} module:"
for param in /sys/module/${module}/parameters/*; do
    echo "  $(basename ${param}): $(cat ${param})"
done
