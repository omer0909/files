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
