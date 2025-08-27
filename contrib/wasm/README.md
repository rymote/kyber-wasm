# @rymote/kyber-wasm

[![npm version](https://badge.fury.io/js/@rymote%2Fkyber-wasm.svg)](https://badge.fury.io/js/@rymote%2Fkyber-wasm)
[![License: CC0-1.0](https://img.shields.io/badge/License-CC0_1.0-lightgrey.svg)](http://creativecommons.org/publicdomain/zero/1.0/)

Kyber post-quantum cryptography compiled to WebAssembly for browser and Node.js environments.

Kyber is a key encapsulation mechanism (KEM) designed to be resistant to cryptanalytic attacks by both classical and quantum computers. It was selected by NIST for standardization as part of the Post-Quantum Cryptography standardization project.

## Features

- 🚀 **High Performance**: Compiled with Emscripten optimizations
- 🌐 **Universal**: Works in browsers, Node.js, and other JavaScript environments
- 🔒 **All Parameter Sets**: Supports Kyber512, Kyber768, and Kyber1024
- 📘 **TypeScript**: Full TypeScript definitions included
- 🛡️ **Secure**: Uses cryptographically secure random number generation
- 🧩 **Modular**: Import individual parameter sets or all together
- 📦 **Small**: Optimized WebAssembly bundles

## Installation

```bash
npm install @rymote/kyber-wasm
```

## Quick Start

### Basic Usage

```javascript
import { Kyber768 } from '@rymote/kyber-wasm';

async function example() {
  // Initialize the module
  const kyber = new Kyber768();
  await kyber.init();
  
  // Generate a key pair
  const { publicKey, secretKey } = kyber.keypair();
  
  // Encapsulate a shared secret
  const { ciphertext, sharedSecret } = kyber.encapsulate(publicKey);
  
  // Decapsulate the shared secret
  const decryptedSecret = kyber.decapsulate(ciphertext, secretKey);
  
  console.log('Shared secrets match:', 
    sharedSecret.every((byte, i) => byte === decryptedSecret[i])
  );
}

example();
```

### TypeScript

```typescript
import { Kyber512, KeyPair, EncapsulationResult } from '@rymote/kyber-wasm';

async function example(): Promise<void> {
  const kyber = new Kyber512();
  await kyber.init();
  
  const keyPair: KeyPair = kyber.keypair();
  const result: EncapsulationResult = kyber.encapsulate(keyPair.publicKey);
  const sharedSecret: Uint8Array = kyber.decapsulate(result.ciphertext, keyPair.secretKey);
}
```

## API Reference

### Parameter Sets

| Class | Security Level | Public Key | Secret Key | Ciphertext | Shared Secret |
|-------|----------------|------------|------------|------------|---------------|
| `Kyber512` | ~AES-128 | 800 bytes | 1632 bytes | 768 bytes | 32 bytes |
| `Kyber768` | ~AES-192 | 1184 bytes | 2400 bytes | 1088 bytes | 32 bytes |
| `Kyber1024` | ~AES-256 | 1568 bytes | 3168 bytes | 1568 bytes | 32 bytes |

### Methods

#### `init(): Promise<void>`
Initialize the WebAssembly module. Must be called before any cryptographic operations.

#### `keypair(): KeyPair`
Generate a new key pair.

**Returns:** `{ publicKey: Uint8Array, secretKey: Uint8Array }`

#### `encapsulate(publicKey: Uint8Array): EncapsulationResult`
Encapsulate a shared secret using the provided public key.

**Returns:** `{ ciphertext: Uint8Array, sharedSecret: Uint8Array }`

#### `decapsulate(ciphertext: Uint8Array, secretKey: Uint8Array): Uint8Array`
Decapsulate a shared secret using the provided ciphertext and secret key.

**Returns:** `Uint8Array` - The shared secret

### Import Options

```javascript
// Import specific parameter sets
import { Kyber512 } from '@rymote/kyber-wasm/kyber512';
import { Kyber768 } from '@rymote/kyber-wasm/kyber768';
import { Kyber1024 } from '@rymote/kyber-wasm/kyber1024';

// Import all parameter sets
import { Kyber512, Kyber768, Kyber1024 } from '@rymote/kyber-wasm';

// Import with types
import { Kyber768, KeyPair, EncapsulationResult } from '@rymote/kyber-wasm';
```

## Examples

### Browser (ES Modules)

```html
<!DOCTYPE html>
<html>
<head>
    <title>Kyber WASM Example</title>
</head>
<body>
    <script type="module">
        import { Kyber1024 } from 'https://unpkg.com/@rymote/kyber-wasm';
        
        async function demo() {
            const kyber = new Kyber1024();
            await kyber.init();
            
            const keyPair = kyber.keypair();
            console.log('Generated key pair:', {
                publicKeyLength: keyPair.publicKey.length,
                secretKeyLength: keyPair.secretKey.length
            });
            
            const { ciphertext, sharedSecret } = kyber.encapsulate(keyPair.publicKey);
            const decryptedSecret = kyber.decapsulate(ciphertext, keyPair.secretKey);
            
            console.log('KEM completed successfully!');
        }
        
        demo().catch(console.error);
    </script>
</body>
</html>
```

### Node.js

```javascript
import { Kyber512 } from '@rymote/kyber-wasm';

async function nodeExample() {
  const kyber = new Kyber512();
  await kyber.init();
  
  // Key generation
  console.time('Key Generation');
  const keyPair = kyber.keypair();
  console.timeEnd('Key Generation');
  
  // Encapsulation
  console.time('Encapsulation');
  const { ciphertext, sharedSecret } = kyber.encapsulate(keyPair.publicKey);
  console.timeEnd('Encapsulation');
  
  // Decapsulation
  console.time('Decapsulation');
  const decryptedSecret = kyber.decapsulate(ciphertext, keyPair.secretKey);
  console.timeEnd('Decapsulation');
  
  console.log('All operations completed successfully!');
}

nodeExample();
```

### Performance Testing

```javascript
import { Kyber768 } from '@rymote/kyber-wasm';

async function benchmark() {
  const kyber = new Kyber768();
  await kyber.init();
  
  const iterations = 100;
  console.log(`Running ${iterations} iterations...`);
  
  // Benchmark key generation
  console.time('Key Generation (100x)');
  for (let i = 0; i < iterations; i++) {
    kyber.keypair();
  }
  console.timeEnd('Key Generation (100x)');
  
  // Benchmark encapsulation/decapsulation
  const keyPair = kyber.keypair();
  
  console.time('Encapsulation (100x)');
  for (let i = 0; i < iterations; i++) {
    kyber.encapsulate(keyPair.publicKey);
  }
  console.timeEnd('Encapsulation (100x)');
}

benchmark();
```

## Security Considerations

- **Random Number Generation**: Uses `crypto.getRandomValues()` in browsers and `crypto.randomBytes()` in Node.js
- **Memory Safety**: All sensitive memory is properly zeroed and freed
- **Constant-Time**: Based on the reference implementation with constant-time operations where applicable
- **Side-Channel Resistance**: Includes basic protections against timing attacks

⚠️ **Important**: This implementation uses a Math.random() fallback if secure random number generation is unavailable. Ensure your environment supports proper cryptographic random number generation.

## Browser Support

- Chrome 57+ (WebAssembly support)
- Firefox 52+ (WebAssembly support)
- Safari 11+ (WebAssembly support)
- Edge 16+ (WebAssembly support)

## Node.js Support

- Node.js 14.0.0+ (WebAssembly and crypto support)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Funding

Support this project:

- [Patreon](https://patreon.com/rymote)
- [Open Collective](https://opencollective.com/rymote)

## License

This project is released into the public domain under CC0-1.0 license, following the original Kyber implementation.

## Acknowledgments

This WebAssembly port is based on the original [Kyber](https://github.com/pq-crystals/kyber) implementation by the CRYSTALS team. Special thanks to the original authors and the NIST Post-Quantum Cryptography project.

---

Built with ❤️ by [Rymote](https://rymote.io/)