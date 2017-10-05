#!/bin/bash

if lsusb | grep -qE "(6615:0084|6615:0085|6615:0086|6615:0087|6615:0088|6615:0c20|2621:2201|2621:4501)" ; then
  /usr/bin/eta-register &
fi
EOF
