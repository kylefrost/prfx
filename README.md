# PRFX

Prounounced "Pr(e)f(i)x".

Command line tool to automatically add browser/web engine specific prefixes for common CSS modifiers transform and transition (i.e. `-webkit-`, `-moz-`, and `-ms-`).

Usage: `prfx style.css`, output file will be `prfxd_style.css` in same folder. If you honestly don't know how to move that file to how you need it (a.k.a. rename it) then you shouldn't even need this tool because you don't know what the actual fuck it does.

## Install
#### Automagically
Run this in **Terminal.app** or your favorite terminal application.
```bash
ruby -e "$(curl -fsSL https://raw.github.com/kylefrost/prfx/master/install)"
```

#### Manually
1. Clone the repo using ```git clone https://github.com/kylefrost/prfx.git```
2. Go to prfx directory: ```cd prfx```
3. Make ```build.sh``` runnable and build prfx: ```chmod a+x build.sh;./build.sh```
4. Copy to ```/usr/local/bin```: ```sudo cp /usr/local/bin/```
5. Restart terminal session

## How to Uninstall
#### Automagically
Run this in **Terminal.app** or your favorite terminal application.
```bash
sudo rm /usr/local/bin/prfx
```

#### Manually
1. Go to /usr/local/bin
2. Remove prfx binary

## Feature Request/Bug Reporting
Open a [GitHub Issue](https://github.com/kylefrost/prfx/issues) if you wish to request a new feature or report a bug.
_or..._
Feel free to fork and submit a pull request with a new feature.

## Notes
1. Have fun
2. I don't remember what my second note was going to be
3. I wrote this in a day, if it fucks up it's not my fault
4. Stay classy

## License
The MIT License. See [LICENSE](LICENSE).
