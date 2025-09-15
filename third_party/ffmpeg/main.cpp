#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}



int main(int argc, char** argv) {
    std::cout << "FFmpeg version: " << av_version_info() << std::endl;

    const char* filename = (argc > 1) ? argv[1] : "test.mp4";
    std::cout << "filename: " << filename << std::endl;
    av_log_set_level(AV_LOG_INFO);
    avformat_network_init();

    AVFormatContext* fmt_ctx = nullptr;
    if (avformat_open_input(&fmt_ctx, filename, nullptr, nullptr) != 0) {
        std::cerr << "Failed to open input: " << filename << std::endl;
        return 1;
    }

    if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
        std::cerr << "Failed to find stream info\n";
        avformat_close_input(&fmt_ctx);
        return 1;
    }

    av_dump_format(fmt_ctx, 0, filename, 0);

    avformat_close_input(&fmt_ctx);
    avformat_network_deinit();
    return 0;
}
