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

# Build everything
all: app driver

# Build monitoring application
app:
	$(CXX) $(CXXFLAGS) $(APP_SRC) -o $(APP)

# Build test program
test:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST)

# Build kernel driver
driver:
	$(MAKE) -C $(DRIVER_DIR)

# Clean userspace and kernel build artifacts
clean:
	rm -f $(APP)
	rm -f $(TEST)
	$(MAKE) -C $(DRIVER_DIR) clean

# Build and load driver
install: all
	sudo insmod $(DRIVER_DIR)/industrial_monitor_driver.ko

# Unload driver
uninstall:
	sudo rmmod industrial_monitor_driver || true
