#! /bin/bash

sudo apt update
sudo apt upgrade -y
sudo apt install gcc clang git build-essential tree vim python3-venv htop curl ffmpeg mediainfo tigervnc-viewer net-tools nvtop btop -y

curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

python3 -m venv ~/global

#for monster laptop
echo -e "deb https://deb.tuxedocomputers.com/ubuntu $(lsb_release -cs) main" | sudo tee -a /etc/apt/sources.list.d/tuxedocomputers.list
cd /etc/apt/trusted.gpg.d/
sudo wget https://deb.tuxedocomputers.com/0x54840598.pub.asc
sudo apt update
sudo apt install tuxedo-control-center
