TARGET  := opencv_capture_fps_test
SRCS    := main.cpp 
OBJS    := ${SRCS:.cpp=.o} 

CCFLAGS = -I/usr/include/opencv -I/usr/include/opencv2
LDFLAGS = 
LIBS    = -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc

.PHONY: all clean distclean 
all:: ${TARGET} 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS}

${OBJS}: %.o: %.cpp
	${CC} ${CCFLAGS} -o $@ -c $< 

clean:: 
	-rm -f *~ *.o ${TARGET} 

distclean:: clean
