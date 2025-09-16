//
// Created by J Chen on 2023/12/31.
//

#ifndef SRC_WRITER_FILE_H_
#define SRC_WRITER_FILE_H_

#include <filesystem>

#include <list>
#include <mutex>

namespace autumn {

namespace fs = std::filesystem;

class LogFile {
 public:
  struct Meta {
    const size_t index_;
    const size_t max_size_;
    const fs::file_time_type mtime_;
    const fs::path path_;
  };

  LogFile(const Meta& info) : meta_(info) {}
  virtual ~LogFile() = default;

  virtual bool Open() = 0;
  virtual void Close() = 0;
  virtual void Remove() = 0;
  virtual bool CanWrite(size_t size) const = 0;
  virtual size_t Write(const std::string& data) = 0;
  virtual size_t Write(const std::vector<char>& data) = 0;

  size_t index() const { return meta_.index_; }
  size_t max_size() const { return meta_.max_size_; }
  const fs::file_time_type& mtime() const { return meta_.mtime_; }
  const fs::path& path() const { return meta_.path_; }

 private:
  const Meta meta_;
};

class MmapFile final : public LogFile {
 public:
  MmapFile(const Meta& meta, size_t size) : LogFile(meta), size_(size) {}
  ~MmapFile() override = default;

  bool Open() override;
  void Close() override;
  void Remove() override;
  bool CanWrite(size_t size) const override;
  size_t Write(const std::string& data) override;
  size_t Write(const std::vector<char>& data) override;

 private:
  int fd_ = -1;
  char* data_ = nullptr;
  size_t size_ = 0;

  void Reset();
};

class Normalile final : public LogFile {
 public:
  Normalile(const Meta& meta, size_t size) : LogFile(meta), size_(size) {}
  ~Normalile() override = default;

  bool Open() override;
  void Close() override;
  void Remove() override;
  bool CanWrite(size_t size) const override;
  size_t Write(const std::string& data) override;
  size_t Write(const std::vector<char>& data) override;

 private:
  FILE* fp_ = nullptr;
  size_t size_ = 0;
};

class LogDir {
 public:
  LogDir(size_t max_files, size_t max_file_size, fs::path dir_path);
  ~LogDir();

  void Init();
  LogFile* GetLogFile(size_t size);

 private:
  const size_t max_files_;
  const size_t max_file_size_;
  const fs::path dir_path_;
  std::list<std::unique_ptr<LogFile>> list_;

  void RollFile();
  fs::path GenPath(size_t index) const;
};

class FileWriter {
 public:
  FileWriter(size_t max_files, size_t max_file_size, std::string dir_path);
  ~FileWriter() = default;

  uint64_t Write(const std::string& data);

 private:
  std::mutex mutex_;
  std::unique_ptr<LogDir> log_dir_;
};

}  // namespace autumn

#endif  // SRC_WRITER_FILE_H_
