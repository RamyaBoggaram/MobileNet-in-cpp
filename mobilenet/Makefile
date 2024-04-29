CC = g++
CFLAGS = -std=c++11 -Wall
#INCLUDES = -I/usr/local/include/opencv
INCLUDES = -I/usr/include/opencv4
LDFLAGS = -L/usr/local/lib
LIBS = -lopencv_imgcodecs -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d

SRCS = batchnormalLayer.cpp convLayer.cpp fcLayer.cpp globalpoolLayer.cpp layers_bn.cpp layers_ds.cpp main.cpp Network.cpp readdata.cpp reluLayer.cpp sigmoidLayer.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = mobilenet

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

