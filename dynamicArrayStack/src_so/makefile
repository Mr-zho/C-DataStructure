OBJS=$(patsubst %.c, %.o, $(wildcard ./*.c))
TARGET=libMyDYArray.so

PATHS=/usr/lib/

$(TARGET):$(OBJS)
	$(CC) -shared -fPIC $^ -o $@
	cp $(TARGET) $(PATHS)

%.o:%.c
	$(CC) -c $^ -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

show:
	@echo $(RM)
	@echo $(OBJS)
