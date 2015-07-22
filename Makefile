CC=clang
CXX=clang++
RM=rm -f
CPPFLAGS=-std=c++11 -g

SRCS=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

libparlex.a: $(OBJS)
	$(AR) -rvsc libparlex.a $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend