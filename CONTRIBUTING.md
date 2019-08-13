### Getting Started

1. Fork [this repo on Github](https://github.com/reazen/relude-eon) and clone it locally
2. `npm install` to grab dependencies
3. `npm run cleanbuild && npm run test` to build and run tests
4. Make your changes (and add appropriate tests)
5. [Open a pull request](https://help.github.com/en/articles/about-pull-requests) with your changes

### Code style and conventions

We use [Relude](https://github.com/reazen/relude/) as our standard library, so try to avoid using `Belt` or `Pervasives` when working with lists, options, etc.

Also, please make sure that your code has been formatted with [`refmt`](https://reasonml.github.io/docs/en/editor-plugins).

### Tests

`relude-eon` doesn't quite have full test coverage, but if you want to help us get there, we'd be very grateful. :) Running `npm run test` (or `jest --coverage`) will run your tests and give you a coverage report. You can see the detailed report in `./coverage/lcov-report/index.html`, which will help you track down any uncovered functions or branches.

### Documentation

Currently documentation only exists in the `rei` files. While some modules are fully documented, others are very lacking. Any improvements or additions you wish to make are welcome, and please add interfaces and doc comments as appropriate when adding new features.
