#!/bin/bash
cat ./settings/tile_data_text.txt | tr -d '\n ' | xxd -r -p > ./settings/tile_data