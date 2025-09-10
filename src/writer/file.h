//
// Created by J Chen on 2023/12/31.
//

#ifndef SRC_WRITER_FILE_H_
#define SRC_WRITER_FILE_H_

#include <list>
#include <mutex>

namespace autumn {

class LogFile {
 public:
  LogFile(size_t max_file_size, size_t index, std::string path,
          std::time_t mtime, size_t size)
      : max_file_size_(max_file_size),
        index_(index),
        path_(std::move(path)),
        mtime_(mtime),
        size_(size) {}
  LogFile(size_t max_file_size, size_t index, std::string path)
      : max_file_size_(max_file_size), index_(index), path_(std::move(path)) {}
  ~LogFile() = default;

 public:
  void Open();
  void Close();
  void Remove();
  std::time_t ModifyTime() const;
  size_t Index() const;
  bool CanWrite(size_t size) const;
  size_t Write(const std::string& data);

 private:
  const size_t max_file_size_;
  const size_t index_ = 0;
  std::string path_;
  std::time_t mtime_ = 0;
  FILE* fp_ = nullptr;
  size_t size_ = 0;
};

class LogDir {
 public:
  LogDir(size_t max_files, size_t max_file_size, std::string dir_path);
  ~LogDir();

  LogFile* GetLogFile(size_t size);

 private:
  void Init();
  void RollFile();

  const size_t max_files_;
  const size_t max_file_size_;
  const std::string dir_path_;
  std::list<LogFile*> list_;
};

class FileWriter {
 public:
  FileWriter(size_t max_files, size_t max_file_size, std::string dir_path);
  ~FileWriter();

  uint64_t Write(const std::string& data);

 private:
  std::mutex mutex_;
  LogDir* log_dir_ = nullptr;
};

}  // namespace autumn

#endif  // SRC_WRITER_FILE_H_
