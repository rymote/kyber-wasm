#include <stdint.h>
#include <emscripten.h>
#include "../../../ref/kem.h"

/* ----------------------------------------------- */
/*                    Kyber 512                    */
/* ----------------------------------------------- */
EMSCRIPTEN_KEEPALIVE
int kyber512_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_kem_keypair(pk, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber512_keypair_seeded(uint8_t *pk, uint8_t *sk, const uint8_t *seed) {
    return crypto_kem_keypair_derand(pk, sk, seed);
}

EMSCRIPTEN_KEEPALIVE
int kyber512_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) {
    return crypto_kem_enc(ct, ss, pk);
}

EMSCRIPTEN_KEEPALIVE
int kyber512_enc_seeded(uint8_t *ct, uint8_t *ss, const uint8_t *pk, const uint8_t *seed) {
    return crypto_kem_enc_derand(ct, ss, pk, seed);
}

EMSCRIPTEN_KEEPALIVE
int kyber512_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) {
    return crypto_kem_dec(ss, ct, sk);
}

/* ----------------------------------------------- */
/*                    Kyber 768                    */
/* ----------------------------------------------- */
EMSCRIPTEN_KEEPALIVE
int kyber768_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_kem_keypair(pk, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_keypair_seeded(uint8_t *pk, uint8_t *sk, const uint8_t *seed) {
    return crypto_kem_keypair_derand(pk, sk, seed);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) {
    return crypto_kem_enc(ct, ss, pk);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_enc_seeded(uint8_t *ct, uint8_t *ss, const uint8_t *pk, const uint8_t *seed) {
    return crypto_kem_enc_derand(ct, ss, pk, seed);
}

EMSCRIPTEN_KEEPALIVE
int kyber768_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) {
    return crypto_kem_dec(ss, ct, sk);
}

/* ----------------------------------------------- */
/*                    Kyber 1024                   */
/* ----------------------------------------------- */
EMSCRIPTEN_KEEPALIVE
int kyber1024_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_kem_keypair(pk, sk);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_keypair_seeded(uint8_t *pk, uint8_t *sk, const uint8_t *seed) {
    return crypto_kem_keypair_derand(pk, sk, seed);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) {
    return crypto_kem_enc(ct, ss, pk);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_enc_seeded(uint8_t *ct, uint8_t *ss, const uint8_t *pk, const uint8_t *seed) {
    return crypto_kem_enc_derand(ct, ss, pk, seed);
}

EMSCRIPTEN_KEEPALIVE
int kyber1024_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) {
    return crypto_kem_dec(ss, ct, sk);
}