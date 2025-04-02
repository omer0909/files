#! /bin/bash

sudo apt update
sudo apt upgrade -y
sudo apt install gcc clang git build-essential tree vim python3-venv htop curl ffmpeg mediainfo tigervnc-viewer net-tools nvtop btop -y

curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

sudo snap install yazi --classic
sudo snap install drawio
cargo install eza

python3 -m venv ~/global

#for monster laptop
echo -e "deb https://deb.tuxedocomputers.com/ubuntu $(lsb_release -cs) main" | sudo tee -a /etc/apt/sources.list.d/tuxedocomputers.list
cd /etc/apt/trusted.gpg.d/
sudo wget https://deb.tuxedocomputers.com/0x54840598.pub.asc
sudo apt update
sudo apt install tuxedo-control-center


################# .bashrc ####################

alias ll='eza --git -alh -F --total-size'
alias la='eza -A'
alias l='eza -F -A'

function y() {
	local tmp="$(mktemp -t "yazi-cwd.XXXXXX")" cwd
	yazi "$@" --cwd-file="$tmp"
	if cwd="$(command cat -- "$tmp")" && [ -n "$cwd" ] && [ "$cwd" != "$PWD" ]; then
		builtin cd -- "$cwd"
	fi
	rm -f -- "$tmp"
}

PS1='\[\033[01;34m\]\w\[\033[00m\]\n\[\e[1;97;46m\]->\[\e[0m\] '
