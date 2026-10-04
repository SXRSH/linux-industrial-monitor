CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

APP := industrial_monitor

APP_SRC := \
	src/industrial_monitor.cpp \
	src/fault_detector.cpp \
	src/sensor_simulator.cpp

TEST := driver_test

TEST_SRC := tests/driver_test.cpp

DRIVER_DIR := driver

.PHONY: all app test driver clean install uninstall

all: app

app:
	$(CXX) $(CXXFLAGS) $(APP_SRC) -o $(APP)

test:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST)

driver:
	$(MAKE) -C $(DRIVER_DIR)

clean:
	rm -f $(APP)
	rm -f $(TEST)
	$(MAKE) -C $(DRIVER_DIR) clean

install: app driver
	sudo insmod $(DRIVER_DIR)/industrial_monitor_driver.ko

uninstall:
	sudo rmmod industrial_monitor_driver || true
