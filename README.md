## What is it?
`kbrd` is a Windows command-line tool to change color and brightness of keyboard based in chip ITE 8291 (rev 0.03).

## Compatibility
If your device's idVendor and idProduct is not `048d`, `6006`, but `048d`, `6004` or `ce00` - change `PRODUCT_ID` in `src/ite8291` to yours.

## Dependencies
* [`hidapi`](https://github.com/libusb/hidapi/tree/533dd9229a846d6ab00c4dced1cbddf66b576258) - tested on hidapi-0.14.0

# Features
* Monocolor mode
* Change brightness
