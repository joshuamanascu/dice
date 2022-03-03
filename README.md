# dice
Simple command line dice roller

## Installing

Compiled with gcc version 9.3.0 and GNU make 4.2.1. Anything relatively modern should work.

```
git clone https://github.com/joshuamanascu/dice.git
cd dice
make
cp dice ~/.local/bin/dice #If desired
```

## Usage

Arguments can be passed in the form AxBdC, where C are the number of sides to the dice, B is the number of dice to roll, and A is the number of times to repeat that roll. Various dice rolls can be added together separated by arithmetic symbols '+' and '-'. For example:

```
dice 3x2d9 + 3d4 - 5
dice "2xd5 - 11 + 7d3"
```
