#!/bin/bash

OUTPUTFOLDERS=("ROOTfiles" "ROOTfilesCent10"
    "plotCrossSection" "plotEff" "plotFONLL" "plotFits" "plotRAA" "plotOthers")

for i in ${OUTPUTFOLDERS[@]}
do
    if [ ! -d "$i" ]; then
        mkdir "$i"
    fi
done