# st - simple terminal
# See LICENSE file for copyright and license details.

include config.mk

CURRENT_DIR = $(shell pwd)
SRC = st.c
OBJ = ${SRC:.c=.o}
SERVICE = st_service.c
all: options st st_service

options:
	@echo st build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

config.h:
	cp config.def.h config.h

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

st: ${OBJ}
	@echo compiling Suckless Terminal
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}
st_service:
	@echo compiling Suckless Terminal service
	@echo CC -o $@
	@${CC} -o $@ ${SERVICE}
clean:
	@echo cleaning
	@rm -f config.h st st_service ${OBJ} st-${VERSION}.tar.gz
	@./clean

dist: clean
	@echo creating dist tarball
	@mkdir -p st-${VERSION}
	@cp -R LICENSE Makefile README config.mk config.def.h st.info st.1 arg.h ${SRC} st-${VERSION}
	@tar -cf st-${VERSION}.tar st-${VERSION}
	@gzip st-${VERSION}.tar
	@rm -rf st-${VERSION}

install: all
	@cp -f ${CURRENT_DIR}/st ${DESTDIR}${PREFIX}/bin/st
	@cp -f ${CURRENT_DIR}/st_service ${DEST_SERVICEDIR}${PREFIX}/bin/st_service
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < st.1 > ${DESTDIR}${MANPREFIX}/man1/st.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/st.1
	@echo Please see the README file regarding the terminfo entry of st.
	@tic -sx st.info

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/st
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/st.1

.PHONY: all options clean dist install uninstall
