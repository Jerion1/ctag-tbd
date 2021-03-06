# CTAG TBD Version Log

## V0.9.4a
   - New reverb plugin Progenitor Reverb (from freesound3), essentially Griesinger Lexicon 224 topology --> with love for all ambient musicians :)
   - Reverb time of Plate Reverb can now be controlled with CV
   - Flash write issue workaround, i.e. when TBD suffers a power loss during a flash write e.g. during storing of preset data, files can get corrupted; this could only be fixed with manually re-flashing the module; now, TBD tries to recover files from a backup directory in the default firmware. Note that any settings made by the user stored in that file will lost. You should always make sure, the power supply is stable and power is only disconnected when no flash writes are in progress (LED NOT BLUE!).
   - Several smaller bug fixes and optimizations

## V0.9.3
   - Significant refactoring reducing code bloat in sound processors, improved compilation speed of sound processors
   - Improved sound processor template generation
   - Minor bug fixes
      - Some plugins previously did not work correctly with negative CV mapped to pitch
   - Otherwise no new plugins
   
## V0.9.2b
   - Bug fix, calibration

## V0.9.2
- Added CDelay delay effect (adapted and modified version of Cocoa Delay by tesselode)
- Added option of soft clipping for outputs
- Optimized Moog filters
- Changed IDF settings for 
    - Flash speed (OTA updates now faster)
    - SPIRAM speed
- Fixed many compiler warnings
- Minor bug fixes and optimizations

## V0.9.1
- Added TBD03 emulation of TB303, essentially braids oscillator with various ladder filter models and some envelopes, filter model 1 is least computationally expensive and allows for TBD03 running on two channels
- Some minor bugs fixes and adaptations
- Updated IDF Release 4.1

## V0.9.0
- Added version log
- Added Poly Pad synth
- Several internal improvements such as ADC value constraints and better trig + ADC synchronisation
- Better ADSR envelope generator
- Bug fix in sine generator
- fast-math gcc flag added

## Pre V0.9.0
- No log present, see commit history