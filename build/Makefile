MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
CFLAGS        = -pipe -g -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -std=gnu++11 -Wall -W -fPIC $(DEFINES)
INCPATH       = -I../src -I. -isystem /usr/include/x86_64-linux-gnu -I/Qt/5.12.5/gcc_64/mkspecs/linux-g++
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS) -L/usr/lib/x86_64-linux-gnu/ -lcurl   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../src/anprcloudrequest.cpp \
		../src/anprcloudservice.cpp \
		../src/anprcloudserviceexception.cpp \
		../src/binaryimage.cpp \
		../src/multipartbuilder.cpp \
		../example/main.cpp 
OBJECTS       = anprcloudrequest.o \
		anprcloudservice.o \
		anprcloudserviceexception.o \
		binaryimage.o \
		multipartbuilder.o \
		main.o
		
DIST          = 
DESTDIR       = 
TARGET        = ANPRCloudService


first: all
####### Build rules

ANPRCloudService:  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

all: Makefile ANPRCloudService

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


check: first

benchmark: first
compiler_clean: 

####### Compile

anprcloudrequest.o: ../src/anprcloudrequest.cpp ../src/anprcloudrequest.h \
		../src/binaryimage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o anprcloudrequest.o ../src/anprcloudrequest.cpp

anprcloudservice.o: ../src/anprcloudservice.cpp ../src/curltools.hpp \
		../src/json.hpp \
		../src/anprcloudservice.h \
		../src/anprcloudresult.h \
		../src/anprcloudserviceexception.h \
		../src/anprcloudrequest.h \
		../src/binaryimage.h \
		../src/multipartbuilder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o anprcloudservice.o ../src/anprcloudservice.cpp

anprcloudserviceexception.o: ../src/anprcloudserviceexception.cpp ../src/anprcloudserviceexception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o anprcloudserviceexception.o ../src/anprcloudserviceexception.cpp

binaryimage.o: ../src/binaryimage.cpp ../src/binaryimage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o binaryimage.o ../src/binaryimage.cpp

main.o: ../example/main.cpp ../src/anprcloudservice.h \
		../src/anprcloudresult.h \
		../src/json.hpp \
		../src/anprcloudserviceexception.h \
		../src/anprcloudrequest.h \
		../src/binaryimage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../example/main.cpp

multipartbuilder.o: ../src/multipartbuilder.cpp ../src/multipartbuilder.h \
		../src/binaryimage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o multipartbuilder.o ../src/multipartbuilder.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

