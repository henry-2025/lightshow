Projects I have for controlling various RGB LED sets
    - mono: hardware PWM controller for simple RGB LED strips
    - reactive: clone of audio-reactive controller for addressable LED strips

I have these in a common repo for development organization purposes. There is a common nix file that installs all of the dev dependencies and the controller program for the reactive strip. If you just want to develop the reactive controller, you might just want to clone the submodule branch.

To clone the full project:
```{shell}
git clone git@github.com:henry-2025/lightshow.git lightshow
cd lightshow
git submodule update --init --recursive

# and if you're a nix user, here is your dev environment
nix develop
```