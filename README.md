# PRFX

Prounounced "Pr(e)f(i)x".

Command line tool to automatically add browser/web engine specific prefixes for common CSS modifiers transform and transition (i.e. `-webkit-`, `-moz-`, and `-ms-`).

Usage: `prfx style.css`, output file will be `prfxd_style.css` in same folder. If you honestly don't know how to move that file to how you need it (a.k.a. rename it) then you shouldn't even need this tool because you don't know what it does.

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
4. Copy to ```/usr/local/bin```: ```sudo cp prfx /usr/local/bin/```
5. Restart terminal session

## Update
#### Automagically
prfx has update checking built in. Simply run this in your terminal application of choice:
```bash
prfx -u
```
*or...*
```bash
prfx --update
```
If an update is available it will prompt to update, otherwise it will inform you no updates are available.

#### Manually
1. Pull changes: `git pull origin master`
2. Go to prfx directory: ```cd prfx```
3. Make ```build.sh``` runnable and build prfx: ```chmod a+x build.sh;./build.sh```
4. Copy to ```/usr/local/bin```: ```sudo cp prfx /usr/local/bin/```
5. Restart terminal session

## Uninstall
#### Automagically
Run this in **Terminal.app** or your favorite terminal application.
```bash
sudo rm /usr/local/bin/prfx
```

#### Manually
1. Go to /usr/local/bin
2. Remove prfx binary

## Feature Request/Bug Reporting
Open a [GitHub Issue](https://github.com/kylefrost/prfx/issues) if you wish to request a new feature or report a bug.<br>
_or..._<br>
Feel free to fork and submit a pull request with a new feature.

## Notes
1. Have fun
2. I don't remember what my second note was going to be
3. There is no number 3
4. Stay classy
5. Are you still reading these?
6. I guess I should put something meaningful here
7. `prfx` was built because I felt like it

## License
The MIT License. See [LICENSE](LICENSE).
