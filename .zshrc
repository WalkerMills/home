# The following lines were added by compinstall

zstyle ':completion:*' auto-description '%d'
zstyle ':completion:*' completer _expand _complete _ignored _correct _approximate
zstyle ':completion:*' file-sort name
zstyle ':completion:*' format '%d'
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%s
zstyle ':completion:*' list-suffixes true
zstyle ':completion:*' matcher-list '' 'm:{[:lower:]}={[:upper:]} m:{[:lower:][:upper:]}={[:upper:][:lower:]}' 'r:|[._-]=** r:|=**' 'l:|=* r:|=*'
zstyle ':completion:*' menu select=0
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
zstyle ':completion:*' use-compctl true
zstyle ':completion:*' verbose true
zstyle :compinstall filename '/home/walker/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall
# Lines configured by zsh-newuser-install
HISTFILE=~/.zsh_history
HISTSIZE=1000
SAVEHIST=1500
setopt appendhistory autocd notify rmstarsilent extendedglob
unsetopt nomatch
bindkey -v
# End of lines configured by zsh-newuser-install
setopt completealiases
autoload -U promptinit colors
promptinit
colors

# emulate -L zsh

if [[ $BITS -eq 32 ]]
then
    CHROOT_STR="[32]"
else
    CHROOT_STR=""
fi

PROMPT="%{$fg[blue]%}%n%{$reset_color%}@%{$fg[blue]%}%m%{$reset_color%}$CHROOT_STR %{$fg[magenta]%}%d %{$reset_color%}
%# "
RPROMPT="%(?..[%{$fg[yellow]%}%?%{$reset_color%}])"

source /usr/share/doc/pkgfile/command-not-found.zsh

# create a zkbd compatible hash;
# to add other keys to this hash, see: man 5 terminfo
typeset -A key

key[Home]=${terminfo[khome]}
key[End]=${terminfo[kend]}
key[Insert]=${terminfo[kich1]}
key[Delete]=${terminfo[kdch1]}

# setup key accordingly
[[ -n "${key[Home]}"    ]]  && bindkey  "${key[Home]}"    beginning-of-line
[[ -n "${key[End]}"     ]]  && bindkey  "${key[End]}"     end-of-line
[[ -n "${key[Insert]}"  ]]  && bindkey  "${key[Insert]}"  overwrite-mode
[[ -n "${key[Delete]}"  ]]  && bindkey  "${key[Delete]}"  delete-char

# Finally, make sure the terminal is in application mode, when zle is
# active. Only then are the values from $terminfo valid.
if (( ${+terminfo[smkx]} )) && (( ${+terminfo[rmkx]} )); then
    function zle-line-init () {
        printf '%s' "${terminfo[smkx]}"
    }
    function zle-line-finish () {
        printf '%s' "${terminfo[rmkx]}"
    }
    zle -N zle-line-init
    zle -N zle-line-finish
fi

export PATH=/home/walker/bin:/usr/local/bin:/usr/local/sbin:/usr/sbin:/usr/bin:/sbin:/bin:/opt/android-sdk/tools:/opt/android-sdk/platform-tools

# Custom aliases/functions

# Development
alias gcc='gcc -Wall -Og -g -std=c11 -mtune=generic -march=native -pipe -fstack-protector --param=ssp-buffer-size=4 -Wno-sign-compare'
alias g++='g++ -Wall -Og -g -std=c++11 -mtune=generic -march=native -pipe -fstack-protector --param=ssp-buffer-size=4 -Wno-sign-compare -Wno-write-strings'
alias ghc='ghc --make -Wall -O'
#alias javac='javac -Xlint:all'

# Administration
alias modified='yaourt -Qii | sed -n "s/^MODIFIED\t//p"'
alias explicit='yaourt -Qet | grep -Ev ''(base|xorg)'

unattached() {
    for i in `tmux list-sessions | grep -v attached | cut -c 1`
    do
        tmux kill-session -t $i
    done
}

# Util
alias shred='shred -fuz'
alias ls='ls -l --color=auto --almost-all --human-readable --classify --group-directories-first --dereference-command-line-symlink-to-dir'
alias cp='cp --no-dereference --preserve=all --recursive --verbose' 
alias rm='rm --force --recursive'
alias mv='mv --verbose'
alias grep='grep --color=auto --no-messages --binary-files=without-match'
alias more='less'
alias mkdir='mkdir --parents --verbose'
alias find='find -O3'
alias cpr='rsync --partial --progress --archive --checksum --compress --copy-unsafe-links'

process () {
    count=`pgrep -c $@`
    if [[ $count -eq 0 ]]
    then
        echo "No matching processes"
    else
        ps wwup `pgrep $@`
    fi
}


# System control
alias reboot='systemctl reboot'
alias poweroff='systemctl poweroff'
alias suspend='systemctl suspend'

# Torrents
alias torstart='command mv ~/downloads/{*.torrent,torrent/torrents}'

# Shell functions
mirrors() {
    [ "$UID" != 0 ] && su=sudo
    
    country='US'
    url="https://www.archlinux.org/mirrorlist/?country=$country&protocol=ftp&protocol=http&ip_version=4&use_mirror_status=on"
    
    tmpfile=$(mktemp --suffix=-mirrorlist)
    
    wget -qO- "$url" | sed 's/^#Server/Server/g' > "$tmpfile"
    
    if [ -s "$tmpfile" ]
    then
        { echo " Backing up the original mirrorlist..."
        $su mv -i /etc/pacman.d/mirrorlist /etc/pacman.d/mirrorlist.orig; } && { echo " Rotating the new list into place..."
        $su mv -i "$tmpfile" /etc/pacman.d/mirrorlist; }
    else
        echo " Unable to update, could not download list."
    fi
    
    chmod +r /etc/pacman.d/mirrorlist
}

orphans() {
    if [[ ! -n $(yaourt -Qdtq) ]]
    then
        echo "no orphans to remove"
    else
        yaourt -Rs $(yaourt -Qdtq)
    fi
}

pkgcache() {
    cache=`yaourt -v 2>/dev/null | grep "Cache Dirs" | cut -d ':' -f 2 | sed 's/ //g'`

    for pkg in `comm -23 <(yaourt -Qq | sort) <(yaourt -Qmq | sort)`
    do
        if ! ls $cache/`yaourt -Q $pkg | sed 's/ /-/g'`* 2>/dev/null >&2
 	    then
            yaourt -Sw --noconfirm $pkg
        fi
    done
}

