#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "../../../ref/randombytes.h"

#ifdef KYBER_WASM
#include <emscripten.h>

EM_JS(void, get_random_bytes_js, (uint8_t *out, size_t outlen), {
  // Create view using memory buffer - handle both old and new Emscripten versions
  var view;
  if (Module.HEAPU8) {
    view = new Uint8Array(Module.HEAPU8.buffer, out, outlen);
  } else if (Module.buffer) {
    view = new Uint8Array(Module.buffer, out, outlen);
  } else if (Module.memory && Module.memory.buffer) {
    view = new Uint8Array(Module.memory.buffer, out, outlen);
  } else {
    // Fallback: write bytes individually using setValue
    if (typeof crypto !== 'undefined' && crypto.getRandomValues) {
      var tempArray = new Uint8Array(outlen);
      crypto.getRandomValues(tempArray);
      for (var i = 0; i < outlen; i++) {
        Module.setValue(out + i, tempArray[i], 'i8');
      }
      return;
    }
    // Math.random fallback with setValue
    console.warn('Using Math.random() fallback - not cryptographically secure!');
    for (var i = 0; i < outlen; i++) {
      Module.setValue(out + i, Math.floor(Math.random() * 256), 'i8');
    }
    return;
  }
  
  // Try crypto.getRandomValues first (works in both browser and Node.js with webcrypto)
  if (typeof crypto !== 'undefined' && crypto.getRandomValues) {
    crypto.getRandomValues(view);
    return;
  }
  
  // Try globalThis.crypto
  if (typeof globalThis !== 'undefined' && globalThis.crypto && globalThis.crypto.getRandomValues) {
    globalThis.crypto.getRandomValues(view);
    return;
  }
  
  // Try window.crypto (browser)
  if (typeof window !== 'undefined' && window.crypto && window.crypto.getRandomValues) {
    window.crypto.getRandomValues(view);
    return;
  }
  
  // Fallback to Math.random (not cryptographically secure)
  console.warn('Using Math.random() fallback - not cryptographically secure!');
  for (var i = 0; i < outlen; i++) {
    view[i] = Math.floor(Math.random() * 256);
  }
});

void randombytes(uint8_t *out, size_t outlen) {
  get_random_bytes_js(out, outlen);
}

#endif
