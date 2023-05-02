
create ros docker container
```sh
xhost local:root

XAUTH=/tmp/.docker.xauth

 
docker run -it \
    --name=r1_noetic_from_file \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="$XAUTH:$XAUTH" \
    --net=host \
    --privileged \
    --runtime=nvidia \
    osrf/ros:noetic-desktop  \
    bash
 ```
docker container setup
# ./run_docker.bash

docker container'ları listeler
# docker images

docker container'ı siler
# docker rm -f <container_name_or_id>

çalışan container'ları listeler "-a" eklerseniz durdurulmuş olanları da listeler
# docker ps

container çalışmasını durdurur
# docker stop <container_name_or_id>

durdurulan container çalıştırılır
# docker start <container_name_or_id>

çalışan bir container'ın içine girer
# docker exec -it <container_name_or_id> bash

dosyaları bind eder
# sudo docker run -it -v $PWD/project:/project r1_noetic_from_file

docker image indirilir
# docker pull osrf/ros:humble-desktop
