CC=clang
CXX=clang++
RM=rm -f
CPPFLAGS=-std=c++11 -g

SRCS=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

parlex.a: $(OBJS)
	$(AR) -rvsc parlex.a $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend