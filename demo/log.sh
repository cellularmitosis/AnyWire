#!/bin/bash
set -e -o pipefail
./logger.py /dev/tty.usb* | tee log-$(date +%s).csv
