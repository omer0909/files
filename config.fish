# .config/fish/config.fish

if status is-interactive
    set fish_greeting
    source "$HOME/.cargo/env.fish"
    starship init fish | source
    function y
        set tmp (mktemp -t "yazi-cwd.XXXXXX")
        yazi $argv --cwd-file="$tmp"
        if set cwd (command cat -- "$tmp"); and [ -n "$cwd" ]; and [ "$cwd" != "$PWD" ]
            builtin cd -- "$cwd"
        end
        rm -f -- "$tmp"
    end
    bass source /opt/ros/jazzy/setup.bash

    alias global='source global/bin/activate.fish'
    alias ll='eza --git -alh -F --total-size'
    alias la='eza -A'
    alias l='eza -F -A'
end
