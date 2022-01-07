## Download
1. Clone the __repo__
```sh
$ git clone https://github.com/michalspano/daily-dose-lang.git && cd daily-dose-lang
```
2. Install the __node dependency__ [here](#node-dependency)!
3. You are all set [docs](https://michalspano.github.io/daily-dose-lang/functions.html)!

## Advanced install (optional)

As a result, __global support__ is used (i.e., one can run the programmes with all required dependencies outside the __scope__ of the project). This step is optional, and it can be ignored if the __global support__ isn't required. Albeit, if you prefer, go to the project's __root__ and type:

```sh
$ ./install <config_path>
```

This _script_ is responsible for creating [alias][alias]es in the selected __config file__, such as `~/.bashrc`, `~/.zshrc`, etc.

__NOTE:__ this method is primarily compatible with __Unix__-like systems (e.g., macOS, Linux, etc.). Hence, additional (customized) options might be required for __Windows__ users. Consider [setting an alias in __Microsoft's Powershell__][PS1] (a viable option for __Windows users__).

\*`install` has been designed to recognize a valid installation, so no need to worry about duplicate insertions.

### Overriding the default name of an alias

Navigate to `daily-dose-lang/install` and under `Personal Adjustments`, feel
free to change any of the default names (i.e., the _key-words_ enclosed with double __quote marks__ `""`) such as:

```sh
alias ddol="change_this_alias"
```
__NOTE:__ be cautious to leave out any redundant whitespace which can result in an error.

In order to __disable__ an alias, simply remove it from the `config` file.

#### Node Dependency

1. __Listed__ by typing:
```sh
$ npm list
```

2. __Installed__ by typing:
```sh
$ npm install
```

In case you are experiencing difficulties with installing the __node dependency__, run the following command:
```sh
$ npm install -g google-translate-cli
```

__NOTE:__ the accuracy of the translations might not be as precise as desired and is planned to be improved in the following versions.

\* [Node dependency docs][NODE]

<!-- Links and refs -->
[NODE]: https://www.npmjs.com/package/google-translate-cli
[alias]: https://en.wikipedia.org/wiki/Alias_(command)
[PS1]: https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.utility/set-alias?view=powershell-7.2