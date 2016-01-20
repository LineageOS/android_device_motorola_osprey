#!/bin/sh

set -e

export DEVICE=osprey
export VENDOR=motorola
./../../$VENDOR/msm8916-common/extract-files.sh $@
