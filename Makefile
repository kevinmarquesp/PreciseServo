TESTS_FILE          ?= tests/tests.ino
ARDUINO_BOARD       ?= uno
ARDUINO_PORT        ?= /dev/ttyUSB0
AUNITER_BIN         ?= ~/.local/share/AUniter/auniter.sh
AUNITER_ARDUINO_CLI ?= /bin/arduino-cli

test:
	@echo "==== Testing $(TESTS_FILE)"
	@AUNITER_ARDUINO_CLI=$(AUNITER_ARDUINO_CLI) $(AUNITER_BIN) --cli test $(ARDUINO_BOARD):$(ARDUINO_PORT) $(TESTS_FILE)
