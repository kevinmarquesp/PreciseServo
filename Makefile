SRC ?= src
DIST ?= dist
LIB_NAME ?= PreciseServo

build:
	@rm -rf ${DIST}
	@mkdir ${DIST}
	@cp -r ${SRC} ${DIST}/${LIB_NAME}
	@cd ${DIST}; zip -r ${LIB_NAME}.zip ${LIB_NAME}
