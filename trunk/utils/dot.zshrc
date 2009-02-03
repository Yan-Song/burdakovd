# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=10000
SAVEHIST=10000
setopt appendhistory autocd extendedglob notify HIST_IGNORE_ALL_DUPS HIST_IGNORE_SPACE HIST_REDUCE_BLANKS
unsetopt beep nomatch

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
#export RPROMPT=$'%{\e[01;31m%}[%!]%{\e[0m%}'
export RPROMPT=$'%{\e[1;34m%}%T%{\e[0m%}'


export PYTHONSTARTUP=$HOME/bin/pycomplete.py


bindkey -e

bindkey ';5D' backward-word # ctrl+left
bindkey ';5C' forward-word #ctrl+right


autoload zkbd
[[ ! -d ~/.zkbd ]] && mkdir ~/.zkbd
[[ ! -f ~/.zkbd/$TERM-${DISPLAY:-$VENDOR-$OSTYPE} ]] && zkbd

source ~/.zkbd/$TERM-${DISPLAY:-$VENDOR-$OSTYPE}


#setup key accordingly
[[ -n "${key[Home]}"    ]]  && bindkey  "${key[Home]}"    beginning-of-line
[[ -n "${key[End]}"     ]]  && bindkey  "${key[End]}"     end-of-line
[[ -n "${key[Insert]}"  ]]  && bindkey  "${key[Insert]}"  overwrite-mode
[[ -n "${key[Delete]}"  ]]  && bindkey  "${key[Delete]}"  delete-char
[[ -n "${key[Up]}"      ]]  && bindkey  "${key[Up]}"      history-beginning-search-backward
[[ -n "${key[Down]}"    ]]  && bindkey  "${key[Down]}"    history-beginning-search-forward
[[ -n "${key[Left]}"    ]]  && bindkey  "${key[Left]}"    backward-char
[[ -n "${key[Right]}"   ]]  && bindkey  "${key[Right]}"   forward-char


alias -s {avi,mpeg,mpg,mov,m2v}=mplayer
alias -s {odt,doc,sxw,rtf}=openoffice.org
alias -s {ogg,mp3,wav,wma}=mplayer
alias -s pdf=xpdf
autoload -U pick-web-browser
alias -s {html,htm}=pick-web-browser
zmodload -a zsh/stat stat
zmodload -a zsh/zpty zpty
zmodload -a zsh/zprof zprof
zmodload -ap zsh/mapfile mapfile

zstyle ':completion::default' list-colors '${LS_COLORS}'
zstyle ':completion:*:default' list-colors 'no=00:fi=00:di=01;34:ln=01;36:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:ex=01;31:'
#zstyle ':completion:*' completer complete _list _oldlist _expand _ignored _match _correct _approximate _prefix
zstyle ':completion:*' insert-unambiguous true
zstyle ':completion:*' add-space true
zstyle ':completion:*:processes' command 'ps -xuf'
zstyle ':completion:*:processes-names' command 'ps xho command'
zstyle ':completion:*:processes' sort false
zstyle ':completion:*:cd:*' ignore-parents parent pwd
zstyle -e ':completion:*:approximate:*' max-errors 'reply=( $((($#PREFIX+$#SUFFIX)/3 )) numeric )'
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'
zstyle ':completion:*:functions' ignored-patterns '*'
zstyle ':completion:*' menu select=long-list select=0
zstyle ':completion:*' old-menu false
zstyle ':completion:*' original true


autoload -U incremental-complete-word
zle -N incremental-complete-word
autoload -U insert-files
zle -N insert-files
autoload -U predict-on
zle -N predict-on

export LS_COLORS='no=00;37:fi=00;37:di=01;36:ln=04;36:pi=33:so=01;35:do=01;35:bd=33;01:cd=33;01:or=31;01:su=37:sg=30:tw=30:ow=34:st=37:ex=01;31:'
zstyle ':completion:*:default' list-colors ${(s.:.)LS_COLORS} 

alias nn="ionice -c3 nice -19"

true

