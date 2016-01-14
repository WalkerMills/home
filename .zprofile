if [[ -z $DISPLAY && $BITS -eq 64 ]]
then
    if [[ -z `process mpd` ]]
    then
        mpd
    fi
    
#    if [[ $XDG_VTNR -eq 1 ]]
#    then
#        exec startx
#    else
#        ~/bin/startt
#    fi
fi
