# libgithub

[![Build and Deploy](https://github.com/briandowns/libtrietree/actions/workflows/main.yml/badge.svg)](https://github.com/briandowns/libtrietree/actions/workflows/compile_example.yml/badge.svg)

libtrietree is a C library that implements a Trie tree. The library makes the assumption the data in use is ready to be stored. E.g. is lower case and doesn't contain non alphabetical characters.

## Usage

```c
node_t *root = trie_new();
```

## Build shared object

To build the shared object:

```sh
make install
```

## Example 

The example loads all words from the system dictionary, ignorning all words that non-alphabetical characters, searched for a few, deletes 1, and then searches for the deleted word.

Build the example:

```sh
make example
```


## Contributing

Please feel free to open a PR!

## Contact

Brian Downs [@bdowns328](http://twitter.com/bdowns328)

## License

BSD 2 Clause [License](/LICENSE).
