#include <stdint.h>
#include <emscripten.h>
#include "../../../ref/kem.h"

// Export functions for each Kyber variant
EMSCRIPTEN_KEEPALIVE
int kyber512_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_kem_keypair(pk, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber512_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) {
    return crypto_kem_enc(ct, ss, pk);
}

EMSCRIPTEN_KEEPALIVE
int kyber512_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) {
    return crypto_kem_dec(ss, ct, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_kem_keypair(pk, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) {
    return crypto_kem_enc(ct, ss, pk);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) {
    return crypto_kem_dec(ss, ct, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_kem_keypair(pk, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) {
    return crypto_kem_enc(ct, ss, pk);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) {
    return crypto_kem_dec(ss, ct, sk);
}
