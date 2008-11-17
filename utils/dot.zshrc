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

case ${UID} in
0)
    PROMPT="%B%{${fg[red]}%}%/#%{${reset_color}%}%b "
    PROMPT2="%B%{${fg[red]}%}%_#%{${reset_color}%}%b "
    SPROMPT="%B%{${fg[red]}%}%r is correct? [n,y,a,e]:%{${reset_color}%}%b "
    [ -n "${REMOTEHOST}${SSH_CONNECTION}" ] &&
        PROMPT="%{${fg[cyan]}%}$(echo ${HOST%%.*} | tr '[a-z]' '[A-Z]') ${PROMPT}"
    ;;
*)
#
# Color
#
DEFAULT=$'%{\e[1;0m%}'
RESET="%{${reset_color}%}"
#GREEN=$'%{\e[1;32m%}'
GREEN="%{${fg[green]}%}"
BLUE=$'%{\e[1;35m%}'
RED="%{${fg[red]}%}"
#
# Prompt
#
setopt prompt_subst
PROMPT='${RED}${USER}@${HOST} ${GREEN}%~${RESET}
${GREEN}%(5~,%-2~/.../%2~,%~)% ${RED} $ ${RESET}'
 
 
# PROMPT="%{${fg[red]}%}%/%%%{${reset_color}%} "
# PROMPT2="%{${fg[red]}%}%_%%%{${reset_color}%} "
# SPROMPT="%{${fg[red]}%}%r is correct? [n,y,a,e]:%{${reset_color}%} "
# [ -n "${REMOTEHOST}${SSH_CONNECTION}" ] &&
# PROMPT="%{${fg[cyan]}%}$(echo ${HOST%%.*} | tr '[a-z]' '[A-Z]') ${PROMPT}"
 
 
    ;;
esac

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



export PROMPT=$'%(?..%{\e[41;38m%}%B-%?-%b%{\e[0m%} )%(1j.%{\e[01;33m%}[%j] .)%{\e[01;36m%}%n@%m%{\e[0m%} %{\e[01;32m%}%2~%{\e[0m%} %B%#%b '
export RPROMPT=$'%{\e[01;31m%}[%!]%{\e[0m%}' # history # on right

