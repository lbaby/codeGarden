TOP_DIR		=.
C++		:=g++
CXXFLAGS	+= -I$(TOP_DIR)  -g   -fpic -Wall   -DDPRINT
LDFLAGS		+= -g  -L$(TOP_DIR) -llcpp  

%.d:%.cpp
	$(C++) $(CXXFLAGS) -M $< \
	|sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' >$@

%:%.o
	$(C++)  -o $@ $<  $(LDFLAGS)

BINSRCS	:=tarray.cpp ta2d.cpp tmt.cpp tll.cpp twrapper.cpp tsas.cpp tsall.cpp\
	trpn.cpp tqaa.cpp tqall.cpp tdq.cpp tlaa.cpp tlall.cpp tslaa.cpp\
	tslall.cpp tpoly.cpp tcht.cpp tcst.cpp tost.cpp tcw.cpp tgt.cpp tnt.cpp\
	tbt.cpp tpti.cpp tbst.cpp tavl.cpp tmwt.cpp tbtree.cpp tbt2.cpp tdic.cpp\
	tbh.cpp tlh.cpp tbq.cpp tsimu.cpp
	
LIBSRCS	:=  Hash.cpp Object.cpp  NullObject.cpp  Container.cpp NullIterator.cpp \
	  Association.cpp StackAsArray.cpp StackAsLinkedList.cpp ToolKits.cpp\
	  QueueAsArray.cpp QueueAsLinkedList.cpp Deque.cpp DequeAsArray.cpp\
	  DequeAsLinkedList.cpp ListAsArray.cpp ListAsLinkedList.cpp Term.cpp\
	  SortedListAsArray.cpp  SortedListAsLinkedList.cpp Polynomial.cpp \
	  HashTable.cpp ChainedHashTable.cpp ChainedScatterTable.cpp\
	  OpenScatterTable.cpp Tree.cpp  GeneralTree.cpp NaryTree.cpp BinaryTree.cpp\
	  BST.cpp AVLTree.cpp MWayTree.cpp BTree.cpp BinaryHeap.cpp LeftistHeap.cpp\
	  BinomialTree.cpp BinomialQueue.cpp RandomNumberGenerator.cpp  RandomVariable.cpp
	  
DEPENDS	:=$(BINSRCS:%.cpp=%.d) $(LIBSRCS:%.cpp=%.d)
OBJS	:=$(BINSRCS:%.cpp=%.o)
LIBOBJS	:=$(LIBSRCS:%.cpp=%.o)
BINS	:=$(BINSRCS:%.cpp=%)

ifeq ($(lib),so)
	LIBFILES	= liblcpp.so
	libcmd=$(C++)  -shared -o $@ $^ ; rm -f liblcpp.a
else
	LIBFILES = liblcpp.a
		libcmd=$(AR) rsv  $@ $^ ; rm -f liblcpp.so
endif



.PHONY:all clean
all:$(BINS) $(LIBFILES)

$(BINS):$(LIBFILES)

$(LIBFILES):$(LIBOBJS)
	$(libcmd)
clean:
	rm -f $(OBJS) $(BINS) $(LIBOBJS) $(LIBFILES) core.[0-9]*  


ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
