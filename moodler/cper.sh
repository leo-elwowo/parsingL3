#!/bin/bash
rm makefile
rm -r src/
rm ../moodler.zip
cp ../makefile makefile
cp -r ../src/ ./src
zip -r ../moodler.zip .