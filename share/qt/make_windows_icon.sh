#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/bitcoinplanet.ico

convert ../../src/qt/res/icons/bitcoinplanet-16.png ../../src/qt/res/icons/bitcoinplanet-32.png ../../src/qt/res/icons/bitcoinplanet-48.png ${ICON_DST}
