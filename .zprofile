if [[ -z $DISPLAY && $BITS -eq 64 ]]
then
    if ! pulseaudio --check
    then
        pulseaudio --start &
    fi

    mpd
    
#    if [[ $XDG_VTNR -eq 1 ]]
#    then
#        exec startx
#    else
#        ~/bin/startt
#    fi
fi