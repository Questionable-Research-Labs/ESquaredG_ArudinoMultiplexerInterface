# ESquaredG NodeMCU Code

> This is the code to controls the multiplexers and handle things like the sync signal.


## [PlatformIO](https://platformio.org/)
To Upload:
`pio run -t upload`
To view serial:
`pio run -t monitor`

Or you can just use the VSCode Extension and use the GUI.

## Setup
The frequency for each probe is 700Hz, with 20 probes plus a synchronization signal it means that it has to update at 14.7KHz (700Hz\*21). This is a delta time of just 6.8\*10<sup>-5</sup>s, aka every 68 microseconds.