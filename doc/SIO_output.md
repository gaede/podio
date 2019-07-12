# Using SIO as persistency implementation


SIO (Simple Input/Output) is a simple binary file format used for LCIO.
It has recently been re-implemented and is available at

- [https://github.com/iLCSoft/SIO](https://github.com/iLCSoft/SIO)

It can be installed with the ususal sequence:

```
mkdir build 
cd build
cmake ..
make install
```


## Implementation of I/O using SIO

This is still somewhat experiemental **Work in Progress**...

Reading and writing is done with

```
podio::SIOReader
podio::SIOWriter
```

implementing similar interfaces as the `ROOTReader/ROOTWriter`.

For every data class we need to create a subclass of 
```
podio::SIOBlock
```
implementing the following two methods:

```cpp
// Read the particle data from the device
virtual void read( sio::read_device &device,
		     sio::version_type vers ) = 0 ;
 
// Write the particle data to the device
virtual void write( sio::write_device &device ) = 0 ;
 
```

In `SIOBlock.h` there is also a factory `SIOBlockFactory` defined that is used by
all subclasses to register themselves via the constructor and a global static instance.
This factory is then used by the `SIOWriter` and `SIOReader` classes to instantiate 
the needed `SIOBlock`s.

Currently the following examples are implemented

```
EventInfoBlock                  // simple POD data
ExampleMCBlock                  // simple POD data w/ reference vectors
ExampleWithStringBlock          // simple non-POD data (strings)
ExampleWithVectorMemberBlock    // simple vector members (i.e. POD like elements)

```




## Installation w/ SIO support

Installation is the same as w/o SIO, except that you have to specify the path to the SIO installation
to `cmake`:

```
mkdir build 
cd build
 cmake -D SIO_DIR=/Users/gaede/podio/sio/ -D CMAKE_INSTALL_PREFIX=/Users/gaede/podio/podio/install ..
make install
```

Then you can run the following examples:


```
../install/tests/write_sio

```

which creates `example.sio` that is read via


```
../install/tests/read_sio

```
