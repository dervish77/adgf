#*
#*     Module Name:  timing.mk
#*
#*
#*	Make file definitions for timing builds within this project.
#*
#*
#*/


#------------------------------------------------------------------------
# used by build timing mechanism

BUILD_TIME_LOG_PREFIX ?= buildtimes/
BUILD_TIME_LOG_SUFFIX ?= .log
BUILD_ALL_SUMMARY ?= $(BUILD_TIME_LOG_PREFIX)all--summary$(BUILD_TIME_LOG_SUFFIX)
BUILD_ALL_SUMMARY_LINE_COUNT = 10

prefix := "-- -- "

# grab the time that these two lines are parsed
MAKE_START_SECONDS := $(shell date +"%s")
MAKE_START_TIME := $(shell date +"%b %e %T")

# use this in shell commands to display the time at execution
TIMESTAMP = `date +"%b %e %T"`
TIMESTAMP_SEC = `date +"%s"`

define header
@echo $(prefix) -----------------------------------------------
@echo $(prefix) Starting $@ target -- $(TIMESTAMP)
@echo $(TIMESTAMP_SEC) > .buildtime.$@.start
@echo
endef

define footer
@echo
@echo $(prefix) Finished $@ target -- $(TIMESTAMP)
@echo $(TIMESTAMP_SEC) > .buildtime.$@.stop
@ELAPSED_SECONDS=`expr \`cat .buildtime.$@.stop\` - \`cat .buildtime.$@.start\``; \
ELAPSED_MIN=`expr $$ELAPSED_SECONDS / 60`; \
ELAPSED_SEC=`expr $$ELAPSED_SECONDS % 60`; \
echo "${prefix} Elapsed time $@ target --  $$ELAPSED_SECONDS seconds ($$ELAPSED_MIN min $$ELAPSED_SEC sec)"; \
mkdir -p $(BUILD_TIME_LOG_PREFIX); \
echo $$ELAPSED_SECONDS >> $(BUILD_TIME_LOG_PREFIX)$@$(BUILD_TIME_LOG_SUFFIX); \
rm -f .buildtime.$@.start .buildtime.$@.stop
@echo $(prefix) -----------------------------------------------
endef


