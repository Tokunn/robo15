CROSS   := ~/Program/cross_gcc/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf

ifneq ($(CROSS),)
	CROSS_PREFIX	:= $(CROSS)-
endif

CXX		 = $(CROSS_PREFIX)g++
CXXFLAGS = -Wall -Wextra -O2 -g -MMD -MP
LDFLAGS	 =
LIBS	 = -L/usr/local/lib
INCLUDE	 = -I../include -I/usr/local/include
BIN_DIR  = ../bin/
TARGET 	 = $(BIN_DIR)$(shell basename `readlink -f ..`).out
OBJDIR	 = ./obj
ifeq "$(strip $(OBJDIR))" ""
	OBJDIR = .
endif
SOURCES	:= $(wildcard *.cpp)
OBJECTS	 = $(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
DEPENDS	 = $(OBJECTS:.o=.d)

all: $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o:%.cpp
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	$(RM) -r $(OBJECTS) $(DEPENDS) $(TARGET) $(BIN_DIR) `readlink -f $(OBJDIR)`

upload: $(BIN_DIR) $(TARGET)
	#scp $(TARGET) pi@192.168.1.7:~/
	#scp $(TARGET) alarm@172.16.14.178:~/
	scp $(TARGET) ubuntu@172.16.14.244:~/
	#scp $(TARGET) pi@172.16.14.120:~/


-include $(DEPENDS)
