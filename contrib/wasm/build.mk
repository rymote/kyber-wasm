# WebAssembly build for Kyber - organized structure
EMCC ?= emcc
EMCFLAGS = -O3 -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -fomit-frame-pointer
WASMFLAGS = -s WASM=1 -s MODULARIZE=1 -s EXPORT_ES6=1 \
  -s EXPORTED_RUNTIME_METHODS='["cwrap","ccall","getValue","setValue","writeArrayToMemory"]' \
  -s EXPORTED_FUNCTIONS='["_malloc","_free","_kyber512_keypair","_kyber768_keypair","_kyber1024_keypair","_kyber512_enc","_kyber768_enc","_kyber1024_enc","_kyber512_dec","_kyber768_dec","_kyber1024_dec"]' \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s ENVIRONMENT=node,web

# Use reference implementation (no assembly code)
SRCDIR = ../../ref
SOURCES = $(SRCDIR)/kem.c $(SRCDIR)/indcpa.c $(SRCDIR)/polyvec.c $(SRCDIR)/poly.c \
  $(SRCDIR)/ntt.c $(SRCDIR)/cbd.c $(SRCDIR)/reduce.c $(SRCDIR)/verify.c \
  $(SRCDIR)/fips202.c $(SRCDIR)/symmetric-shake.c

WASM_SOURCES = src/randombytes_wasm.c src/kyber_wasm.c

# Output to dist directory
DIST = dist

.PHONY: all clean js ts

all: js ts

js: $(DIST)/kyber512.js $(DIST)/kyber768.js $(DIST)/kyber1024.js $(DIST)/index.js $(DIST)/example.js $(DIST)/debug_test.js

ts: $(DIST)/kyber.d.ts $(DIST)/package.json

$(DIST)/kyber512_wasm.js: $(SOURCES) $(WASM_SOURCES)
	mkdir -p $(DIST)
	$(EMCC) $(EMCFLAGS) $(WASMFLAGS) \
		-s EXPORT_NAME="Kyber512Module" \
		-DKYBER_K=2 -DKYBER_WASM \
		$(SOURCES) $(WASM_SOURCES) \
		-o $@

$(DIST)/kyber768_wasm.js: $(SOURCES) $(WASM_SOURCES)
	mkdir -p $(DIST)
	$(EMCC) $(EMCFLAGS) $(WASMFLAGS) \
		-s EXPORT_NAME="Kyber768Module" \
		-DKYBER_K=3 -DKYBER_WASM \
		$(SOURCES) $(WASM_SOURCES) \
		-o $@

$(DIST)/kyber1024_wasm.js: $(SOURCES) $(WASM_SOURCES)
	mkdir -p $(DIST)
	$(EMCC) $(EMCFLAGS) $(WASMFLAGS) \
		-s EXPORT_NAME="Kyber1024Module" \
		-DKYBER_K=4 -DKYBER_WASM \
		$(SOURCES) $(WASM_SOURCES) \
		-o $@

$(DIST)/kyber512.js: $(DIST)/kyber512_wasm.js src/kyber512.js.template
	mkdir -p $(DIST)
	cp src/kyber512.js.template $@

$(DIST)/kyber768.js: $(DIST)/kyber768_wasm.js src/kyber768.js.template  
	mkdir -p $(DIST)
	cp src/kyber768.js.template $@

$(DIST)/kyber1024.js: $(DIST)/kyber1024_wasm.js src/kyber1024.js.template
	mkdir -p $(DIST)
	cp src/kyber1024.js.template $@

$(DIST)/index.js: src/index.js.template
	mkdir -p $(DIST)
	cp src/index.js.template $@

$(DIST)/example.js: src/example.js.template
	mkdir -p $(DIST)
	cp src/example.js.template $@

$(DIST)/debug_test.js: src/debug_test.js.template $(DIST)/kyber512_wasm.js
	mkdir -p $(DIST)
	cp src/debug_test.js.template $@

$(DIST)/kyber.d.ts: src/kyber.d.ts.template
	mkdir -p $(DIST)
	cp src/kyber.d.ts.template $@

$(DIST)/package.json: src/package.json.template
	mkdir -p $(DIST)
	cp src/package.json.template $@

clean:
	rm -rf $(DIST)
