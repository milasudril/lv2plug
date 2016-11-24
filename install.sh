#!/bin/bash

rm -r ~/.lv2/monosynth.ttl
mkdir -p ~/.lv2/monosynth.ttl
cp __targets/*.so ~/.lv2/monosynth.ttl
cp __targets/manifest.ttl ~/.lv2/monosynth.ttl
ls ~/.lv2/monosynth.ttl
cat ~/.lv2/monosynth.ttl/manifest.ttl