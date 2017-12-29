#!/bin/bash

FILES=$1

nodemon --exec "./build-all.sh $FILES" --watch . -e cpp
