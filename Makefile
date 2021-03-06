include outfiles.local

OUTFILES = out/obli out/oblid
SHRINK_EXECUTABLES = out/oblid

all: start
	make next
dist: start
	make dnext GOLDFLAGS="-ldflags=\"-s -w\""

start:
	mkdir -p out
	python3 gen_outfiles.py

next: $(CLIENT_IGNFILES) $(OUTFILES) trackd
dnext: next shrink

out/%.o: %.c
	$(CC) $(LIB_INCFLAGS) -c -o$@ $^
out/libobli.a: $(LIB_TARGETS)
	ar -rc $@ $^

out/obli: out/libobli.a $(CLIENT_TARGETS)
	$(CC) $(CLIENT_INCFLAGS) $(LIB_INCFLAGS) $^ -o $@ -lgit2

out/oblid: $(DAEMON_TARGETS)
	cd daemon && \
	go build $(GOLDFLAGS) -o ../$@

shrink: $(SHRINK_EXECUTABLES)
	upx --brute $^

trackd: out/oblid
	-DPATH=${HOME}/.oblip/bin/oblid && \
	[ ! -f $$DPATH ] && \
	ln -s ${PWD}/out/oblid $$DPATH

clean:
	rm -rf out