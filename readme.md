<!--
                    ***

                ~/README.md
    https://github.com/michalspano/daily-dose-lang
                @michalspano

                    ***
-->

# Daily Dose of Languages - DD(o)L

<!-- GitHub Shields -->
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

A light-weight __CLI__ application with a great emphasis on performance, written in the `C` programming language and `POSIX sh`.

<!-- Formatting the icon with an HTML tag -->
<img src="docs/profile.png" width=250px height=250px></img>

## Description

__DD(o)L__ enables you to learn daily vocabulary inputs right from your __Terminal__ window, hence called a [__CLI__][CLI] application.
It contains several tweakable options to fit everyone's needs.

## Why a CLI app?

In general, pure GUI -based apps are substantially slower than CLI -based programs. This application, which was written in `C` and then built to a __Unix__ executable, can load and query thousands of words in a fraction of a second and places a strong emphasis on __overall performance__!

## Installing
1. Clone the __repo__
```sh
$ git clone https://github.com/michalspano/daily-dose-lang.git && cd daily-dose-lang
```
2. Install the __node dependency__ [here](#node-dependency)!
3. You are all set [docs](#functionalities)!

### Project structure

The following command lists the __structure__ of the project per the current version.

```sh
$ ./schema.sh
```

Overall, the `bin` folder contains strictly `executables`, `database` contains supported __word-lists__, `dist` stores locally parsed data from an __API__. We can find several `.sh`, `.h` and `.c` files in the root of the project. Lastly, `package.json` contains a `node dependency` that can be:

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

## Functionalities
__NOTE__: the following commands will be run from the directory's __root directory__.
All of the scripts, however, can be called __globally__ with the necessary dependencies. Consider the following example:

```
$ ./PATH/to/daily-dose-lang/foo
```

### Default (timed) run

The entries are __time limited__ by default, as the project's name implies, with `12h = 1 entry`.

```sh
./run.sh $WORDLIST
```

### Unlimited mode

There is no __time limit__, so you can retrieve as many entries as you want:

```sh
./run.sh $WORDLIST -ul, --unlimited-mode
```

\* `$WORDLIST` represents the source from `database` directory and will be used in the following examples for brevity.

#### Listing wordlists

There's a script that can list all supported __word-lists__ from 'database':\*

```sh
$ ./dict_list
```

\* By default, it will display the __keys__ of the supported inputs. They are, however, valid, because `run.sh` has a __parser__ that can comprehend such behavior.

In practice, given by a __pseudo-code__:

```text
FOR file IN DATABASE_DIR
    REMOVE file extension of $file, REMEMBER $file's base name
    IF $file matches $key
        APPEND the relative path to the script
        BREAK
    ELSE 
        RETAIN $key
```

You can optionally - if you prefer so - list the __relative paths__ of the inputs (respective to the root directory):

```sh
$ ./dict_list -f, --full
```

Alternatively, use the __help__ flag:

```sh
$ ./dict_list -h, --help
```

### Displaying entries

Displaying the __latest__ entry:

```sh
$./mount.sh
```

\* If the user is unable to retrieve a new entry owing to a __time limit__, `mount.sh` is automatically invoked (in the default behavior).


<!-- Links and Refs -->
[CLI]: https://en.wikipedia.org/wiki/Command-line_interface
[gblink]: https://github.com/michalspano/daily-dose-lang
[NODE]: https://www.npmjs.com/package/google-translate-cli

<!-- GitHub Shields -->
[contributors-shield]: https://img.shields.io/github/contributors/michalspano/daily-dose-lang.svg?style=for-the-badge
[contributors-url]: https://github.com/michalspano/daily-dose-lang/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/michalspano/daily-dose-lang.svg?style=for-the-badge
[forks-url]: https://github.com/michalspano/daily-dose-lang/network/members
[stars-shield]: https://img.shields.io/github/stars/michalspano/daily-dose-lang.svg?style=for-the-badge
[stars-url]: https://github.com/michalspano/daily-dose-lang/stargazers
[issues-shield]: https://img.shields.io/github/issues/michalspano/daily-dose-lang.svg?style=for-the-badge
[issues-url]: https://github.com/michalspano/daily-dose-lang/issues
[license-shield]: https://img.shields.io/github/license/michalspano/daily-dose-lang.svg?style=for-the-badge
[license-url]: https://github.com/michalspano/daily-dose-lang/blob/main/LICENSE