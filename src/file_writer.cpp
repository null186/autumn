//
// Created by J Chen on 2023/12/31.
//

#include "file_writer.h"

#include <sys/stat.h>

#include "inner_log.h"

namespace autumn {

FileWriter::FileWriter(size_t max_files, size_t max_file_size, std::string dir_path)
    : max_files_(max_files), max_file_size_(max_file_size), dir_path_(std::move(dir_path)) {
    file_queue_ = new FileQueue(max_files_, max_file_size_, dir_path_);
    if (!OpenOldFile()) {
        OpenNewFile();
    }
    assert(fp_ && "FileWriter fp_ is nullptr");
}

FileWriter::~FileWriter() {
    if (fp_) {
        fclose(fp_);
        fp_ = nullptr;
    }
    delete file_queue_;
    file_queue_ = nullptr;
}

uint64_t FileWriter::Write(const std::string& data) {
    if (size_ + data.size() > max_file_size_) {
        OpenNewFile();
    }

    size_t written = fwrite(data.c_str(), sizeof(char), data.size(), fp_);
    size_ += written;
    if (written == data.size()) {
        fflush(fp_);
    } else {
        ilog << "write to output file failed" << end_line;
    }

    return written;
}

time_t FileWriter::ModifyTime() {
    struct stat s {};
    if (stat(file_path_.c_str(), &s) == 0) {
        return s.st_mtime;
    }
    return 0;
}

inline std::string FileWriter::GetNextFileName() {
    if (index_ + 1 >= max_files_) {
        index_ = 0;
    }
    return FileInfo::prefix + std::to_string(index_++) + FileInfo::extension;
}

void FileWriter::OpenNewFile() {
    if (file_queue_ && !file_path_.empty()) {
        file_queue_->Enqueue({size_, index_, ModifyTime(), file_path_});
    }
    if (fp_) {
        fclose(fp_);
    }
    size_ = 0;
    const std::string& filename = GetNextFileName();
    file_path_ = dir_path_ + "/" + filename;
    fp_ = fopen(file_path_.c_str(), "ab+");
}

bool FileWriter::OpenOldFile() {
    FileInfo info;
    bool ret = file_queue_->PopBack(info);
    if (!ret) {
        return false;
    }

    size_ = info.size;
    index_ = info.index;
    file_path_ = info.path;
    if (info.size + 4096 < max_file_size_) {
        fp_ = fopen(file_path_.c_str(), "ab+");
        return true;
    }
    return false;
}

}  // namespace autumn
