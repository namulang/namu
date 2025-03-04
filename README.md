# Github Pages for Namu language

## How to update WASM file
* When you build wasm from the namu repository, two files, `namu.wasm` and `namu.js`, appear.
* At this time, simply upload the `namu.wasm` file as an asset to the release of the `namu` repository.

### Why?
The `namu.js` file created by this `emscripten` is written to basically search for wasm files in the local path and import them from an external source under certain conditions.

`namu.js` in the `play` folder of this `gh-pages` branch has been modified to always import the wasm file from the outside as an absolute path.
