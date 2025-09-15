
## install ffmpeg
    linux:
        vcpkg  install ffmpeg[all]:x64-linux-release
    windows:
        vcpkg  install ffmpeg[all]:x64-windows


## depend libs
    pkg-config  --libs libavcodec libavformat libavutil
        
        -lm -lavformat -lxml2 -lbz2 -lmodplug -lopenmpt -lvorbisfile -lmpg123 -lsrt -lssl -lssh -lcrypto -lavcodec 
        -lvpx   -lpthread -lwebpmux -llzma -ldav1d -lsnappy -laom -lilbc
        -lmp3lame -lopenjp2 -lopus -lspeex -ltheoraenc -ltheoradec -lvorbisenc -lvorbis -logg -lwebp -lsharpyuv 
        -lopenh264 -lm -lz -lm -lswresample -lsoxr -lavutil -pthread -lm -lmfx -lstdc++ -ldl -lOpenCL -latomic 
