CC=clang
CXX=clang++
RM=rm -f
CPPFLAGS=-std=c++11 -g -I ../

SRCS=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

test.exe: $(OBJS)
	$(CXX) $(OBJS) -L ../ -lparlex -o test.exe

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend