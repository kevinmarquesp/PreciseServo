TESTS_FILE          ?= tests/tests.ino
ARDUINO_BOARD       ?= uno
ARDUINO_PORT        ?= /dev/ttyUSB0
AUNITER_BIN         ?= ~/.local/share/AUniter/auniter.sh
AUNITER_ARDUINO_CLI ?= ~/.local/bin/arduino-cli

PACKAGE_NAME ?= PreciseServo.zip
DIST_NAME ?= PreciseServo

test:
	@AUNITER_ARDUINO_CLI=$(AUNITER_ARDUINO_CLI) $(AUNITER_BIN) --cli test $(ARDUINO_BOARD):$(ARDUINO_PORT) $(TESTS_FILE)

build:
	@mkdir $(DIST_NAME) || rm -rf $(DIST_NAME)/*
	@cp -r src/* $(DIST_NAME)
	@cp LICENSE $(DIST_NAME)
	@cp -r examples $(DIST_NAME)
	@rm $(PACKAGE_NAME) || echo
	@zip -r $(PACKAGE_NAME) $(DIST_NAME)
	@rm -rf $(DIST_NAME)
