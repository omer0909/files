
create ros docker container
```sh
xhost local:root

XAUTH=/tmp/.docker.xauth

 
sudo docker run -it \
    --name=r1_noetic_from_file \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="$XAUTH:$XAUTH" \
    --net=host \
    --privileged \
    osrf/ros:noetic-desktop  \
    bash
 ```

docker container setup
```sh
sudo ./run_docker.bash
 ```

docker container'ları listeler
```sh
sudo docker images
 ```

docker container'ı siler
```sh
sudo docker rm -f <container_name_or_id>
 ```

çalışan container'ları listeler "-a" eklerseniz durdurulmuş olanları da listeler
```sh
sudo docker ps
 ```

container çalışmasını durdurur
```sh
sudo docker stop <container_name_or_id>
 ```

durdurulan container çalıştırılır
```sh
sudo docker start <container_name_or_id>
 ```

çalışan bir container'ın içine girer
```sh
sudo docker exec -it <container_name_or_id> bash
 ```

dosyaları bind eder
```sh
sudo sudo docker run -it -v $PWD/project:/project r1_noetic_from_file
 ```

docker image indirilir
```sh
sudo docker pull osrf/ros:humble-desktop
 ```
