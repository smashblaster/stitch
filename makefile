# Uncomment lines below if you have problems with $PATH
#SHELL := /bin/bash
#PATH := /usr/local/bin:$(PATH)

env = nano

all:
	platformio -f -c vim run -e ${env}

clean:
	platformio -f -c vim run -e ${env} -t clean

program:
	platformio -f -c vim run -e ${env} -t program

test:
	platformio test

update:
	platformio -f -c vim update -e ${env}

upload:
	platformio -f -c vim run -e ${env} -t upload

uploadfs:
	platformio -f -c vim run -e ${env} -t uploadfs

watch:
	platformio device monitor
