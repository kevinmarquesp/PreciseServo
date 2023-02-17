LIB_NAME ?= PreciseServo
SRC ?=      src
DIST ?=     dist

BOARD ?=    arduino:avr:uno
PORT ?=     /dev/ttyUSB0
BAUDRATE ?= 9600

TESTS ?=     ./test
RUN_TESTS ?= ./run-tests.py

monitor:
	@cu -l ${PORT} -s ${BAUDRATE}

build:
	@rm -rf ${DIST}
	@mkdir ${DIST}
	@cp -r ${SRC} ${DIST}/${LIB_NAME}
	@cd ${DIST}; zip -r ${LIB_NAME}.zip ${LIB_NAME}

tests:
	@arduino-cli compile -u -b ${BOARD} -p ${PORT} ${TESTS}
	@clear
	@PORT=${PORT} BAUDRATE=${BAUDRATE} ${RUN_TESTS}
