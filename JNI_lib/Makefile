# Build path
TARGET=systime
BUILD_DIR=.
SOURCES=systime.cpp
GCC=g++
JAVA_HOME=/zserver/java/jdk-8u162-x64


all: $(BUILD_DIR)/lib$(TARGET).so
#######################################
# build the application
#######################################
# list of objects
OBJECTS = ${TARGET}.o


$(BUILD_DIR)/${TARGET}.o: ${TARGET}.cpp
	$(GCC) -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux $< -o $@

$(BUILD_DIR)/lib${TARGET}.so: $(OBJECTS)
	$(GCC) -shared -fPIC -lc  $< -o $@

$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)/*.o $(BUILD_DIR)/*.so

# *** EOF ***
