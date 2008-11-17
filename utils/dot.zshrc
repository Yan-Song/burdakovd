# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=10000
SAVEHIST=10000
setopt appendhistory autocd extendedglob notify
unsetopt beep nomatch
bindkey -e
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '/home/kreved/.zshrc'

autoload -Uz compinit
compinit -C
# End of lines added by compinstall

if [[ $EUID == 0 ]]
then
PROMPT=$'%{\e[1;31m%}%n %{\e[1;34m%}%~ #%{\e[0m%} ' # user dir % 
else 
PROMPT=$'%{\e[1;32m%}%n %{\e[1;34m%}%~ %#%{\e[0m%} ' # root dir #
fi
RPROMPT=$'%{\e[1;34m%}%T%{\e[0m%}' # right prompt with time

alias ls='ls --color=auto'
alias grep='grep --colour=auto'

bindkey "^[[A" history-beginning-search-backward
bindkey "^[[B" history-beginning-search-forward

zstyle ':completion:*' menu yes select

zstyle ':completion:*:default' list-colors ${(s.:.)LS_COLORS}

case $TERM in
  xterm*|rxvt)
    precmd () { print -Pn "\e]0;%n@%m: %~\a" }
    preexec () { print -Pn "\e]0;%n@%m: $1\a" }
    ;;
  screen)
    precmd () { print -Pn "\033k%~\033\\" }
    preexec () { print -Pn "\033k$1\033\\" }
    ;;
esac

PATH=~/bin:"${PATH}:/usr/sbin"

zmodload -a zsh/stat stat 
zmodload -a zsh/zpty zpty 
zmodload -a zsh/zprof zprof 
zmodload -ap zsh/mapfile mapfile


if [ -f /usr/bin/grc ]; then
  alias ping="grc --colour=auto ping"
  alias traceroute="grc --colour=auto traceroute"
  alias make="grc --colour=auto make"
  alias diff="grc --colour=auto diff"
  alias cvs="grc --colour=auto cvs"
  alias netstat="grc --colour=auto netstat"
fi



autoload promptinit
promptinit
prompt walters

